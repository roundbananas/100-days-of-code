// Example of receiving numbers by Serial
// Author: Nick Gammon
// Date: 31 March 2012
//http://gammon.com.au/serial

const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';

void setup ()
  { 
  Serial.begin (115200);
  Serial.println ("Starting ...");
  } // end of setup
  
void processNumber (const long n)
  {
  Serial.println (n);
  }  // end of processNumber
  
void processInput ()
  {
  static long receivedNumber = 0;
  static boolean negative = false;
  
  byte c = Serial.read ();
  
  switch (c)
    {
      
    case endOfNumberDelimiter:  
      if (negative) 
        processNumber (- receivedNumber); 
      else
        processNumber (receivedNumber); 

    // fall through to start a new number
    case startOfNumberDelimiter: 
      receivedNumber = 0; 
      negative = false;
      break;
      
    case '0' ... '9': 
      receivedNumber *= 10;
      receivedNumber += c - '0';
      break;
      
    case '-':
      negative = true;
      break;
      
    } // end of switch  
  }  // end of processInput
  
void loop ()
  {
  
  while (Serial.available ())
    processInput ();
    
  // do other stuff here
  } // end of loop
