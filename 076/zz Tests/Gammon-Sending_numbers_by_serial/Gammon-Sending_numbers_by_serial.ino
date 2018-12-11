// Example of sending numbers by Serial
// Author: Nick Gammon
// Date: 31 March 2012
//http://gammon.com.au/serial

const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';

void setup ()
  { 
  srand (42);
  Serial.begin (115200);
  } // end of setup
  
void loop ()
  {
  Serial.println ("Starting ...");
  for (int i = 0; i < 10; i++)
    {
    Serial.print (startOfNumberDelimiter);    
    Serial.print (rand ());    // send the number
    Serial.print (endOfNumberDelimiter);  
    Serial.println ();
    }  // end of for

  //delay (5000);
  }  // end of loop
