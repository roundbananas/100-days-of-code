/*
 * 
 * Carl Turner 24 October 2018
 * roundbananas.com
 * 
 */

/*Radio pin assignments
 * the way the radio libaries are setup means you need to connect the following way (different for Arduino Uno/Mega)
 * Uno    Mega  Radio Pin
 * 9      40    CE
 * 10     53    SCN
 * 11     51    MO
 * 12     50    MI
 * 13     52    SCK
 * 
 * Connect the radio to 3.3V, not 5V.
 */ 

/***CONFIGURATION FOR EACH ARDUINO MODULE*****/
bool Transmitter = false; //set to false for programming the Receiver

 /*-------------------IMPORT LIBRARIES-------------------*/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "DataStructs.h"

/*-------------------DECLARE CONSTANTS & PINS-------------------*/

//Transmitter
const int xPin = A0; //variable for joystick input (rudder)
const int yPin = A1; //variable for joystick input (speed)
/*the joystick range is 0 to 900, with 450 in the middle-ish. Create a window of +/-5 around the
* middle to allow for the dodgy joystick. Within this window we'll set speed and direction to 0.
*/
const int xlimit1 = 445; 
const int xlimit2 = 455;
const int ylimit1 = 445; 
const int ylimit2 = 455;

//Receiver
const int motorPin = 3; 

//Radios
int msg[1]; //for debugging
RF24 radio(9,10); //Arduino UNO
//RF24 radio(40,53); //Arduino MEGA
const uint64_t pipe = 0xE8E8F0F0E1LL;
//0xE8E8F0F0E1LL

 /*-------------------STRUCTURES-------------------*/
HumansOrders humansOrders;

HumansOrders GetOrders()
{
  int   y = analogRead(yPin);
  Serial.println(   );
  Serial.print("y = ");
  Serial.println(y);
  int   x = analogRead(xPin);
  Serial.print("x = ");
  Serial.println(x);
  humansOrders.throttleSpeed = y;
  humansOrders.turnPosition = x; 
  return (HumansOrders) {0, 1}; //0 and 1 refer to the indices of elements in the struct
}

void setup() {
 Serial.begin(9600);
 
  if (Transmitter)
  {
    radio.begin();
    radio.openWritingPipe(pipe);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
  }
  else
  {
    radio.begin();
    radio.openReadingPipe(1,pipe);
    radio.startListening(); 
    pinMode(motorPin, OUTPUT);
  }
 
}

void loop() {
  if (Transmitter)
  {
  humansOrders = GetOrders();
  radio.write( &humansOrders, sizeof(humansOrders) );
  }
  else
  {
    if (radio.available())
    {
      Serial.println("radio available");
      while (true)
      {
        radio.read( &humansOrders, sizeof(humansOrders) );
        Serial.println(   );
        Serial.println("Human's Orders are: ");
        Serial.print("      Throttle speed / Turn Position: ");
        Serial.print(humansOrders.throttleSpeed);
        Serial.print(" / ");
        Serial.println(humansOrders.turnPosition);

        analogWrite(motorPin, humansOrders.throttleSpeed);
        delay(100);
      }
    }
    else{Serial.println("No radio available");} 
  }
  delay(1000);
}
