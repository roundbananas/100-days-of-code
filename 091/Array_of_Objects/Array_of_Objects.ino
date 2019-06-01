/*
 * Array_of_Objects.ino
 * 
 * Created by Carl Turner on 1/06/19
 * 
 * Dynamically allocate an array of objects whose constructors require parameters.
 *  
 */
 
#include "Arduino.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>

/******** CONSTANTS *********/
//The Adafruit_DotStar constructor is of format: Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR)
//We'll use arrays to hold variables the parameters required by the constructor.
const int m_NumStrips = 2;
const int m_NumPixels = 90;

int m_StripLengths[m_NumStrips] = {m_NumPixels, m_NumPixels};
int m_DataPins[m_NumStrips] = {7, 8};
int m_ClockPins[m_NumStrips] = {9, 10};
uint8_t m_StripColourCodes [m_NumStrips] = {DOTSTAR_BGR, DOTSTAR_BGR};

/******** VARIABLES *********/
uint32_t m_StripColors[m_NumStrips] = {0xFF0000, 0xFF0000};

//declare a pointer of desired type, with null value
Adafruit_DotStar *m_Leds = nullptr;

//forward declare a function that returns a pointer of desired type
Adafruit_DotStar* createLedStrips(int NumStrips);

//define the function that returns a pointer of desired type
Adafruit_DotStar* createLedStrips(int NumStrips)
{
  //dynamically allocate an array of size m_NumStrips, with elements of type Adafruit_DotStar
  //--> ie we want to create an array of objects that represent LED strips.
  //AND at the same time, 
  //assign values to each element of the array (in this case this means call the Adafruit_DotStar constructor function for each element, since each element is of type Adafruit_DotStar)
  //-->The object's Constructor function is called in the following line, so we have to give it some values (otherwise the program won't compile).
  //Initialising with 0s seems to work. 
  Adafruit_DotStar *ledStrips = new Adafruit_DotStar[NumStrips](0,0,0,0);

  /*Now we have our array of Adafruit_DotStar objects, we can initialise each object by
  *calling the constructor, using the correct variables we want for each strip.
  *Having our variables stored in arrays means we only need two lines of code to do this.
  */
  for (int i = 0; i < NumStrips; i++)
  ledStrips[i] = Adafruit_DotStar(m_StripLengths[i], m_DataPins[i], m_ClockPins[i], m_StripColourCodes[i]);

  //finally, this function we're in returns a pointer - the address of the first LED strip object in our array.
  return ledStrips;
}


void setup()
{
  /*We initialised m_Leds as a null pointer. We assign the a value to it now, 
  *which is the address of the first LED strip object in our array of LED strips.
  *This let's us refer to, and do stuff with, the LED strips.
  */
  m_Leds = createLedStrips(m_NumStrips);

  //Now we just use the LED strips as normal, except each strip is an element in the an array.
  for (int i = 0; i < m_NumStrips; i++)
  {
    m_Leds[i].begin();
    m_Leds[i].show();
  }
}

//The main loop adapts the 'strandtest' example code included with the Adafruit_DotStar library.
/*Note if the absolute value of the initial tail variable == number of leds in strip, 
*then you'll see the lights go by once only (because of the maths, how the tail and head are 
*reset to 0 below).*/
int head = 0, tail = -2;
  
void loop()
{
  for (int i = 0; i < m_NumStrips; i++)
  {
    m_Leds[i].setPixelColor(head, m_StripColors[i]);
    m_Leds[i].setPixelColor(tail, 0);
    m_Leds[i].show();
  }
  if(++head >= m_NumPixels) 
     { 
      head = 0;
      for (int i = 0; i < m_NumStrips; i++)
      {
      if((m_StripColors[i] >>=8) == 0) m_StripColors[i] = 0xFF0000;
      }
     }
  if(++tail >= m_NumPixels) tail = 0;
  delay(20);
}
