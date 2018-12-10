/*
 * Created by Carl Turner 18 Nov 2018
 * roundbananas.com
 * 
 * This is a test program to establish serial communication between Arduino Mega and ESP8266. 
 * I want to use lots of pins on the Mega, but outsource the processor-intensive led refreshing
 * to the ESP. 
 * 
 * On MEGA
 * 1. calculate pixel movement on MEGA
 * 2. send pixel movement to ESP
 * 
 * ON ESP8266
 * 1. receive data
 * 2. set pixel colours on strip
 * 3. refresh strip (render)
  */

/*******
 * NOTE for NodeMCU or WEMOS mini ESP8266 module.
 * Pin assignments are confusing.
 * Pin label on board - Pin number you need to give assign it in software
 * TX (10)  - 1  
 * RX (9)   - 3
 * 
 * D0       - 16
 * D1       - 5
 * D2       - 4
 * D3       - 0              
 * D4       - 2
 * 
 * D5       - 14
 * D6       - 12
 * D7       - 13
 * D8       - 15
 * 
 * A0       - 0 (analog)
 ******/

/*** SELECT BOARD TO UPLOAD TO ****/
bool Mega = false; //false means we're uploading to ESP8266

  /*****
   * MEGA Objects and Variables
   *****/

uint16_t head = 0, tail = -2;
uint16_t NUMPixels = 25;

  /*****
   * ESP Objects and Variables
   *****/
#include <Adafruit_DotStar.h>
#include <SPI.h>  

int _DataPin = 0;
int _ClockPin = 2;
uint16_t _NUMPixels = 25; //MUST BE SAME DECLARED IN MEGA CODE

Adafruit_DotStar strip1 = Adafruit_DotStar(_NUMPixels, _DataPin, _ClockPin, DOTSTAR_BRG);

uint16_t _head, _tail, _stripNumber;
uint32_t _color1 = 0xFF0000; 

uint16_t _receivedArray[2] = {0,0};  //where we'll put the values we receive
int  _serialCount = 0;      //a count of how many values we've received
bool _messageComplete = false;


void setup()
{
  Serial.begin(9600);
  
  if (Mega)
  {
    Serial.println("SETUP - Mega");
  }
  else
  {
    Serial.println("SETUP - ESP");

    pinMode(_DataPin, OUTPUT);
    pinMode(_ClockPin, OUTPUT);
  
    strip1.begin(); // Initialize pins for output
    strip1.show();  // Turn all LEDs off ASAP
  }
}

void loop()
{
  if (Mega)
  {
    //calculate pixel movement
    if(++head >= NUMPixels) head = 0;  // Increment head index. Reset if head has gone off end of strip
    if(++tail >= NUMPixels) tail = 0; // Increment, reset tail index if it's off end of strip
  
    //send updated head, tail and strip number to ESP
    Serial.print(head);
    Serial.print(",");
    Serial.print(tail);
    Serial.println('\n');
  }
  else //ESP
  {  
    refresh:     
    //receive data from Mega
    if (_messageComplete)
    {      
      //set pixel colors on strip
      strip1.setPixelColor(_receivedArray[0], _color1);
      strip1.setPixelColor(_receivedArray[1], 0);
   
      //refresh strip
      strip1.show();
      _messageComplete = false;
    }
    else
    {
      while (Serial.available() > 0)
      {
        //add latest value from serial to array
        _receivedArray[_serialCount] = Serial.parseInt();
        _serialCount++;
        _receivedArray[_serialCount] = Serial.parseInt();
        _serialCount++;
        
        if (_serialCount > 1)     // it's the end of the message
        {
          _messageComplete = true;
          _serialCount = 0;
         goto refresh;
        }
       }
    }  
  }
}
