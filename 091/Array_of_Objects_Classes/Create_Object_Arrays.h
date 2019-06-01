/*
 * Create_Object_Arrays.h 
 * for Array_of_Objects_Classes.ino
 * 
 * Created by Carl Turner on 1/06/19
 * 
 * Dynamically allocate an array of objects whose constructors require parameters.
 *  
 */
#ifndef Create_Object_Arrays_h
#define Create_Object_Arrays_h

#include <Adafruit_DotStar.h>
#include <SPI.h>

//forward declare a function that returns a pointer of desired type
Adafruit_DotStar* createLedStrips(int NumStrips);

#endif

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
