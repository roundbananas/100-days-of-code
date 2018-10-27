/*
 * 
 * Carl Turner 27 October 2018
 * roundbananas.com
 * 
 */

 /***CONFIGURATION FOR EACH ARDUINO MODULE*****/
bool Transmitter = true; //set to false for programming the Receiver

/*-------------------IMPORT LIBRARIES-------------------*/
#include "Radio.h"
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

//Radio pipe addresses
uint64_t pipe = 0xE8E8F0F0E1LL; //, 0xF0F0F0F0F0, 0xF0F0F0F0AA, 0xF0F0F0F066, 0xF0F0F0F0F0, 0xF0F0F0F0F0 };

//variable to track timing
unsigned long currentMillis;
unsigned long prevMillis;

/*-------------------CREATE OBJECTS-------------------*/
Radio radio(7, 8, pipe);

/*-------------------DATA STRUCTURES-------------------*/
HumansOrders humansOrders;

/*-------------------FUNCTIONS-------------------*/
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

void setup() {
 Serial.begin(9600);
 radio.Begin();
  if (Transmitter)
  { 
    radio.OpenWritingPipe();
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
  }
  else
  {
    radio.OpenReadingPipe(1); 
    pinMode(motorPin, OUTPUT);
  }
}
void loop() {
  if (Transmitter)
  {
    currentMillis = millis();
    if (currentMillis - prevMillis >= radio.GetInterval()) 
    {
      humansOrders = GetOrders();
      Serial.println(" ");
      if(radio.Write(&humansOrders, sizeof(humansOrders)))
        {
          Serial.print("Orders Sent: ");
          Serial.print(humansOrders.throttleSpeed);
          Serial.print(" / ");
          Serial.println(humansOrders.turnPosition);
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
      if (radio.Available())
      {
        while (radio.Available())
        {
            Serial.println(" ");
            Serial.println("radio available");
            radio.Read(&humansOrders, sizeof(humansOrders)); //not the read() function was a bool in an older library version. Now it's a void type.
            Serial.println("Orders received: ");
            Serial.print(humansOrders.throttleSpeed);
            Serial.print(" / ");
            Serial.println(humansOrders.turnPosition);
            
            int value = map(humansOrders.throttleSpeed, 0, 1023, 0, 255);
            analogWrite(motorPin, value);
          }
      }    
    }
}
