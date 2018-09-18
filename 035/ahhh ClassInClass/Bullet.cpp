//
//  Bullet.cpp
//
//  Created by Carl Turner on 17/9/18.
//
#include "Bullet.h"

Bullet::Bullet(int pixels, int dataPin, int clockPin)
{
    m_NumPixels = pixels;
  m_DataPin = dataPin;
  m_ClockPin = clockPin;
  
    m_ledStrip = Adafruit_DotStar(m_NumPixels, m_DataPin, m_ClockPin, DOTSTAR_BRG);

}
void Bullet::spawn(int pixels, int dataPin, int clockPin)
{

  m_NumPixels = pixels;
  m_DataPin = dataPin;
  m_ClockPin = clockPin;
}
