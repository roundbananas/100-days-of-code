#include "Arduino.h"
#include <Adafruit_DotStar.h>

const int m_NumStrips = 1;

int m_StripLengths[m_NumStrips];
int m_DataPins[m_NumStrips];
int m_ClockPins[m_NumStrips];
uint8_t m_StripColourCodes [m_NumStrips];


//declare a pointer of desired type, with null value
Adafruit_DotStar *m_Leds = nullptr;

//forward declare a function that returns a pointer of desired type
Adafruit_DotStar* createLedStrips(int NumStrips);

//define the function that returns a pointer of desired type
Adafruit_DotStar* createLedStrips(int NumStrips)
{
  //dynamically allocate an array of size m_NumStrips, with elements of type Adafruit_DotStar
  //AND at this same time, 
  //assign values to each element of the array (in this case this means call the Adafruit_DotStar constructor function for each element, since each element is of type Adafruit_DotStar) 

  /*DOESN"T WORK COS allocating an array expects the SIZE OF ARRAY. So how to give the constructor for each element the variables it needs to satisfy constructor parameters?*/
  /*   Adafruit_DotStar *ledStrips = new Adafruit_DotStar[SIZE OF ARRAY];*/
 
  for (int i = 0; i < NumStrips; i++)
  Adafruit_DotStar *ledStrips = new Adafruit_DotStar[i]{m_StripLengths[i], m_DataPins[i], m_ClockPins[i], m_StripColourCodes[i]};

  
  return ledStrips;
}

m_Leds = createLedStrips(m_NumStrips);

void setup()
{

}

void loop()
{
  
}
