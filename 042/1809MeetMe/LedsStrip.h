//
//  LedsStrip.h
//
//  Created by Carl Turner on 18/9/18.
//
#ifndef LedsStrip_h
#define LedsStrip_h

//#include "Arduino.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>

class LedsStrip
{
  private:
  int m_stripLength; 
    int m_stripDataPin;
    int m_stripClockPin;

Public:
LedsStrip(int pixels, int dataPin, int clockPin);



#endif
