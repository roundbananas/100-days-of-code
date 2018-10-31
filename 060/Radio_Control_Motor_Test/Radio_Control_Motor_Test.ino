/*
 * 
 * Carl Turner 26 October 2018
 * roundbananas.com
 * 
 */

/*Radio pin assignments
 * the way the radio libaries are setup means you need to connect the following way (different for Arduino Uno/Mega)
 * Uno    Mega  Radio Pin
 * 7      40    CE
 * 8      53    SCN    **CHECK CONNECTIONS ARE GOOD, NOT DODGY JUMPERS***
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
RF24 radio(7,8); //Arduino UNO
//RF24 radio(40,53); //Arduino MEGA
const uint64_t pipe = 0xE8E8F0F0E1LL; //can have multiple pipes, but the message must be sent from same pipe that it's received on. ie pipe value must be same for TX and RX

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
  return (HumansOrders) {humansOrders.throttleSpeed, humansOrders.turnPosition};
}

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 50; // send at specified intervals

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
          Serial.print(humansOrders.throttleSpeed);
          Serial.print(" / ");
          Serial.println(humansOrders.turnPosition);
          Serial.println("");
  if (Transmitter)
  {
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) 
    {
      humansOrders = GetOrders();
      Serial.println(" ");
        if(radio.write( &humansOrders, sizeof(humansOrders) ))
        {
          //Serial.print("Orders Sent: ");
        }
        else
        {
          Serial.println("Orders not sent ");
        }
      prevMillis = millis();
    }
  }
  else //Receiver
  {
    if (radio.available())
    {
      while (radio.available())
      {
         // Serial.println(" ");
          Serial.println("Orders Read");
          radio.read((int*)&humansOrders, sizeof(humansOrders)); //not the read() function was a bool in an older library version. Now it's a void type.
        // ADDED (int*) above in read() function. Does it have any effect?
        }
    }   
    if (currentMillis - prevMillis >= txIntervalMillis) 
    {
       int value = map(humansOrders.throttleSpeed, 0, 1023, 0, 255);
          analogWrite(motorPin, value);
          Serial.println(value);
    }
  }
}
