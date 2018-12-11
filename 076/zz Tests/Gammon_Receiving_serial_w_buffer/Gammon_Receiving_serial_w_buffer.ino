/*
Example of processing incoming serial data without blocking.

Author:   Nick Gammon
Date:     13 November 2011. 
Modified: 31 August 2013.

Released for public use.
*/

// how much serial data we expect before a newline
const unsigned int MAX_INPUT = 5;

void setup ()
  {
  Serial.begin (115200);
  } // end of setup

// here to process incoming serial data after a terminator received
void process_data (const char * data)
  {
  // for now just display it
  // (but you could compare it to some value, convert to an integer, etc.)
  Serial.print("Got it: "); Serial.println (data);
  }  // end of process_data
  
void processIncomingByte (const byte inByte)
  {
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;

  switch (inByte)
    {

    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte
      
      // terminator reached! process input_line here ...
      process_data (input_line);
      
      // reset buffer for next time
      input_pos = 0;  
      break;

    case '\r':   // discard carriage return
      break;

    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (MAX_INPUT - 1))
        input_line [input_pos++] = inByte;
      break;

    }  // end of switch
   
  } // end of processIncomingByte  

void loop()
  {
  // if serial data available, process it
  while (Serial.available () > 0)
    processIncomingByte (Serial.read ());
    
  // do other stuff here like testing digital input (button presses) ...

  }  // end of loop
