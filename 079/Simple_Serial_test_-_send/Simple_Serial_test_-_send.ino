/*
*     Created by Carl Turner on 23/1/19.
*     
*     Basic test setup for serial communication between two arduinos
*     This code below sends a marker character, followed by an integer.
*/

//What are we going to send?
unsigned int value = 0;

void setup() {
  //I want to do it fast, so choose a fast baud rate.
  Serial.begin(250000);
}

void loop() {
  //Serial.print sends data to the serial port as ASCII text.
  //Numbers are sent using an ASCII character for each digit.
  //This means the integer 123 is sent as the 49, 50 and 51 
  //(representing the digits 1, 2 and 3 respectively).
  //See https://www.arduino.cc/en/Reference/ASCIIchart
  
  Serial.print('A');      
  Serial.println(value); //each 
  value++;
  delay(1000);
}
