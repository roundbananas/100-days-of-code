/*
*     Created by Carl Turner on 23/1/19.
*     
*     Basic test setup for serial communication between two arduinos, 
*     and update a 4-digit seven segment display with received data.
*     This code below:
*     1. receives data from another arduino,
*     2. processes the data,
*     3. updates the display.
*     4. the sender code on the other arduino sends a 'B' character every
*        few seconds, which this program interprets as an instruction to
*        turn off the display.
*/

#include "SevSeg.h"

/*
 * Variables to handle incoming serial data
 */
// variable to hold partial number, incoming through serial
unsigned int currentValue = 574;

// Use a state-machine to manage two separate displays
typedef enum {  NONE, DISPLAY_ON, DISPLAY_OFF} states;

// current state-machine state
states state;

/*
 * Displays
 */
//declare two seven segment displays
SevSeg display1;

  //Common to both displays
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  byte hardwareConfig = COMMON_CATHODE; 
  byte numDigits = 4; 

  //Different for each display
  byte display1_digitPins[] = {5, 6, 7, 8};
  byte display1_segmentPins[8] = {2, 3, 4, 12, 11, 10, 9, 1}; //NOTE pin 1 is not connected. We don't need DP.
  
void setup() {
  //I want to do it fast, so choose a fast baud rate.
  Serial.begin(250000);
   
  state = NONE;

  display1.begin(hardwareConfig, numDigits, display1_digitPins, display1_segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  display1.setBrightness(90);

 // display2.begin(hardwareConfig, numDigits, display2_digitPins, display2_segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
 // display2.setBrightness(90);


}

void loop() {
    while (Serial.available ())
      processIncomingByte (Serial.read ());
          
    switch (state)
  {
     case DISPLAY_ON:
      display1.refreshDisplay();
      break;
     case DISPLAY_OFF:
      display1.blank(); //don't display anything
      break;
      case NONE:
      display1.refreshDisplay();
      break;
  } //end switch
    
}// end loop

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
            state = DISPLAY_ON;
            break;
          case 'B': 
            state = DISPLAY_OFF;
            break;
          default:
            state = NONE;
            break;  
        } //end of switch
      } //end of else
 }// end of processIncomingByte

void handlePreviousState()
{
  //Update the value being displayed
  switch (state)
  {
   case DISPLAY_ON:
    display1.setNumber(currentValue, 0);
    break;
  case DISPLAY_OFF:
    display1.blank();
    break;
  } //end switch
  //now we've update the value we can reset the currentValue, ready to handle new serial data
  currentValue = 0;
} //end handlePreviousState
