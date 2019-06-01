/*
 * Array_of_Objects_Classes.ino
 * 
 * Created by Carl Turner on 1/06/19
 * 
 * Dynamically allocate an array of objects whose constructors require parameters.
 *  
 */

#include "Arduino.h"
#include "Variables.h" //contains declaractions of main variables, and initialises them
#include "Create_Object_Arrays.h"  //contains functions that initialise dynamically allocated objects
//Meanwhile, this file - Array_of_Objects_Classes.ino - contains the main program, the action!

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
  delay(1);
}
