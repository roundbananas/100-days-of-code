//
//  Bullet.cpp
//
//  Created by Carl Turner on 17/9/18.
//
#include "Arduino.h"
#include "Bullet.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>  

void Bullet::setBulletSpeed(int bulletSpeed)
{
    m_Speed = bulletSpeed;
}
void Bullet::spawn(int pixels, int dataPin, int clockPin, int head, int tail, int headColour[])
{

  m_NumPixels = pixels;
  m_DataPin = dataPin;
  m_ClockPin = clockPin;

  m_ledStrip = Adafruit_DotStar(m_NumPixels, m_DataPin, m_ClockPin, DOTSTAR_BRG);
  m_ledStrip.begin();
  m_ledStrip.show(); //turn all LEDs off

  m_Head = head;
  m_Tail = tail;

  m_RedValues[0] = headColour[0];
  m_GreenValues[0] = headColour[1];
  m_BlueValues[0] = headColour[2];

  for (int i = (m_Head - m_Tail) - 1; i > 1; i--)
  {
    double factor = (0.15 * i/(m_Head - m_Tail)); //0.15 seems to work well for the second light, if the lead one is 255 brightness.
    m_RedValues[i] = factor * headColour[0];
    m_GreenValues[i] = factor * headColour[1];
    m_BlueValues[i] = factor * headColour[2];
  }
}

void Bullet::updateBullet(unsigned long dt)
{
    for(int i = m_Head; i > m_Tail; i--)
    {  
      m_ledStrip.setPixelColor(i, m_RedValues[i], m_GreenValues[i], m_BlueValues[i]);
    }
      m_ledStrip.show();  

    if(dt > m_Speed)
    {
      head++;
      tail++;
    }
}

int Bullet::getHead()
{
     return m_Head; 
}
int Bullet::getTail()
{
    return m_Tail;
}
