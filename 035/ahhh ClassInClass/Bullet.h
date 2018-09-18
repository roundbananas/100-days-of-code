//
//  Bullet.h
//
//  Created by Carl Turner on 17/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#ifndef Bullet_h
#define Bullet_h

#include "Arduino.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>  

class Bullet
{
  private:
    //for use by constructor
    int m_NumPixels;
    int m_DataPin;
    int m_ClockPin;

    Adafruit_DotStar m_ledStrip;


  public:
    Bullet(int pixels, int dataPin, int clockPin);
    void spawn(int pixels, int dataPin, int clockPin);

};

#endif
