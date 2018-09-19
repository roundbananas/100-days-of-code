//
//  Bullet.cpp
//
//  Created by Carl Turner on 17/9/18.
//
#include "Bullet.h"

Bullet::Bullet()
{
}

void Bullet::spawn(int head, int tail)
{
  m_Head = head;
  m_Tail = tail;
}

void Bullet::setBulletSpeed(int bulletSpeed)
{
    m_Speed = bulletSpeed;
}

void Bullet::updateBullet(unsigned long dt)
{
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

bool Bullet::isInFlight()
{
  return m_IsInFlight;
}

void Bullet::shoot(int bulletSpeed, int* colourArray)
{
  m_IsInFlight = true;
  m_Speed = bulletSpeed;
  
  m_RedValues[0] = colourArray[0];
  m_GreenValues[0] = colourArray[1];
  m_BlueValues[0] = colourArray[2];

  for (int i = (m_Head - m_Tail) - 1; i >= 0; i--)
  {
    double factor = (0.15 * i/(m_Head - m_Tail)); //0.15 seems to work well for the second light, if the lead one is 255 brightness.
    m_RedValues[i] = factor * colourArray[0];
    m_GreenValues[i] = factor * colourArray[1];
    m_BlueValues[i] = factor * colourArray[2];
  }
}

void Bullet::setColour(int r, int g, int b)
{
   //set the colours and intensities
  m_RedValues[0] = r;
  m_GreenValues[0] = g;
  m_BlueValues[0] = b;

  for (int i = (m_Head - m_Tail) - 1; i >= 0; i--)
  {
    double factor = (0.15 * i/(m_Head - m_Tail)); //0.15 seems to work well for the second light, if the lead one is 255 brightness.
    m_RedValues[i] = factor * r;
    m_GreenValues[i] = factor * g;
    m_BlueValues[i] = factor * b;
  }
}
