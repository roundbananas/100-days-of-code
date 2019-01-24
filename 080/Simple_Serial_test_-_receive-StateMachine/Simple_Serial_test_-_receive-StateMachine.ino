/*
*     Created by Carl Turner on 23/1/19.
*     
*     Basic test setup for serial communication between two arduinos, 
*     and update two seven segment displays with received data.
*     This code below:
*     1. receives data from another arduino,
*     2. processes the data,
*     3. updates two displays (accounting them being single digit).
*/

#include "SevSeg.h"

/*
 * Variables to handle incoming serial data
 */
// variable to hold partial number, incoming through serial
unsigned int currentValue = 0;

// Use a state-machine to manage two separate displays
typedef enum {  NONE, DISPLAY1, DISPLAY2} states;

// current state-machine state
states state;

/*
 * Displays
 */
//declare two seven segment displays
SevSeg display1;
SevSeg display2;

  //Common to both displays
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  byte hardwareConfig = COMMON_ANODE; 
  byte numDigits = 1; 

  //Different for each display
  byte display1_digitPins[1] = {2};
  byte display1_segmentPins[8] = {3, 4, 5, 6, 7, 8, 9, 1}; //NOTE pin 1 is not connected. We don't need DP.
  
  byte display2_digitPins[1] = {10};
  byte display2_segmentPins[8] = {11, 12, 13, A0, A1, A2, A3, 1}; //NOTE pin 1 is not connected. We don't need DP.

//single digit display can display up to value of 9. 
bool MaxedOut_Display1;
bool MaxedOut_Display2;

void setup() {
  //I want to do it fast, so choose a fast baud rate.
  Serial.begin(250000);
   
  state = NONE;

  display1.begin(hardwareConfig, numDigits, display1_digitPins, display1_segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  display1.setBrightness(90);

  display2.begin(hardwareConfig, numDigits, display2_digitPins, display2_segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  display2.setBrightness(90);

  MaxedOut_Display1 = false;
  MaxedOut_Display2 = false; 
}

void loop() {
    while (Serial.available ())
      processIncomingByte (Serial.read ());
    
    display1.refreshDisplay();
    display2.refreshDisplay();
}

/*
 * Helper functions
 */

void processIncomingByte(const byte c)
 {
      //is the next incoming byte a number? 
      if (isdigit (c))
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
         currentValue += c - '0';
      }  // end if isdigit
      else 
      {
        //it's not a number, so we've got all the digits we need.
        //we'll update the number being displayed, for the appropriate display.
        handlePreviousState();

        //Update the state if we need to. 
        //If the incoming byte was a carriage return ('\r') or end of line ('\n'), 
        //we'll just change the state to NONE.
        
        // The Serial.print function which sends the data from the other Arduino
        // sends a \r character automatically after the sent value. 
        // Serial.println also sends a \n character.

        switch (c)
        {
          case 'A':
            state = DISPLAY1;
            break;
          case 'B':
            state = DISPLAY2;
            break;
          default:
            state = NONE;
            break;  
        } //end of switch
      } //end of else
 }// end of processIncomingByte

void handlePreviousState()
{

  //handle maxing out
  if(MaxedOut_Display1)
  {
      if (currentValue <= 9)
        MaxedOut_Display1 = false;
  }
  else if (currentValue > 9)
  {
    currentValue = 9;
    MaxedOut_Display1 = true;
  }
  
  //Update the value being displayed, for the appropriate display
  switch (state)
  {
   case DISPLAY1:
    display1.setNumber(currentValue, 1);
    break;
  case DISPLAY2:
    display2.setNumber(currentValue, 1);
    break;
  } //end switch

  //now we've update the value we can reset the currentValue, ready to handle new serial data
  currentValue = 0;
} //end handlePreviousState
