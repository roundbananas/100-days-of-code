/*
*     Created by Carl Turner on 23/1/19.
*     
*     Basic test setup for serial communication between two arduinos
*     This code below:
*     1. receives data from another arduino,
*     2. checks if the data is a number,
*/

// current partial number
unsigned int currentValue;

void setup() {
   //I want to do it fast, so choose a fast baud rate.
   Serial.begin(250000);
}

void loop() {
  //I used Serial.print to send data from the other Arduino.
  //This sends numbers an ASCII character for each digit.
  //This means the integer 123 is sent as the 49, 50 and 51 
  //(representing the digits 1, 2 and 3 respectively).
  //See https://www.arduino.cc/en/Reference/ASCIIchart
  //So, we need to process the ASCII characters as they
  //are received to interpret them appropriately.

 /*Get the number of bytes (characters) available 
  * for reading from the serial port. This is data that's already
  * arrived and stored in the serial receive buffer (which holds 64 bytes).
  */  
 if (Serial.available ()>0)
  {
     //Get the next byte of incoming serial data available.
     byte incomingByte = Serial.read();

      //is the byte a number? 
      if (isdigit (incomingByte))
      {
         /*if it is a number it will be a number between 
          * 48 (representing 0) and 57 (representing 9).
          * We subtract 48 (= ASCII '0') to convert it 
          * to the digit it supposed to be.
          * 
          * And we add the latest digit to the currentValue
          * we're holding.
          * Eg:
          * if a value of 123 was sent by the other Arduino, 
          * we would receive (read) 49, 50 then 51.
          * The currentValue was initialised to 0. So it 
          * would be 0. 
          * Then in the next loop iterations: 
          * 0*10 + (49 - 48) = 1
          * 1*10 + (50 - 48) = 12
          * 12*10 + (51 - 48) = 123
          * 
          * then we'd receive an \r and \n, indicating the end
          * of the number.
          */
         currentValue *= 10;
         currentValue += incomingByte - '0';
      }  // end of digit
      else if (incomingByte == '\r' || incomingByte == '\n')
      {
        //do nothing
      }
      else
      {
        //
        Serial.println(currentValue);
        currentValue = 0;
      }
  }
}
