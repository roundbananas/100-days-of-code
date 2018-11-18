/*
 * Test sketch for connecting Arduino to Wemos-style D1-mini ESP8266, using serial.
 * Sketch adapted from: http://www.martyncurrey.com/arduino-to-esp8266-serial-commincation/
 * 
 */
// Basic serial communication with ESP8266
// Uses serial monitor for communication with ESP8266
//
//  Pins
//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to Logic Level Converter then to ESP8266 RX
//  Connect GND from the Arduino to GND on the ESP8266
//  
//  ???Pull ESP8266 CH_PD HIGH
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the ESP8266
//
 
#include <SoftwareSerial.h>
SoftwareSerial ESPserial(2, 3); // RX | TX
 
void setup() 
{
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    ESPserial.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");    
}
 
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( ESPserial.available() )   {  Serial.write( ESPserial.read() );  }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  ESPserial.write( Serial.read() );  }
}
