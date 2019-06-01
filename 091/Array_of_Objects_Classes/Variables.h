/*
 * Variables.h
 * for Array_of_Objects_Classes.ino
 * 
 * Created by Carl Turner on 1/06/19
 * 
 * Dynamically allocate an array of objects whose constructors require parameters.
 *  
 */
#ifndef Variables_h
#define Variables_h

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

#endif
