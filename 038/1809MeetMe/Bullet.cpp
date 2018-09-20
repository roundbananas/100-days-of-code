//
//  Bullet.cpp
//
//  Created by Carl Turner on 17/9/18.
//
#include "Bullet.h"

Bullet::Bullet()
{
  m_AIsInFlight = false;
  m_BIsInFlight = false;
}

void Bullet::spawn(int head, int trailLength)
{
  m_HeadAPos = head;
  m_HeadBPos = head;
  m_TrailLength = trailLength;
}

void Bullet::setBulletSpeed(int bulletSpeed)
{
    m_Speed = bulletSpeed;
}

void Bullet::updateBullet(int num_Pixels)
{
  if(m_BIsInFlight)
  {
     m_HeadBPos++;
  }
  if(m_HeadAPos > num_Pixels)
  {
    m_BIsInFlight = true;
  }  
  if(m_HeadAPos > num_Pixels + m_TrailLength)
  {
    m_AIsInFlight = false;
  }
  if(m_HeadBPos > num_Pixels + m_TrailLength)
  {
    m_BIsInFlight = false;
  }
  
  m_HeadAPos++;
}

int Bullet::getHeadAPos()
{
     return m_HeadAPos; 
}
int Bullet::getTailAPos()
{
    return m_HeadAPos - m_TrailLength;
}

int Bullet::getHeadBPos()
{
     return m_HeadBPos; 
}
int Bullet::getTailBPos()
{
    return m_HeadBPos - m_TrailLength;
}

int Bullet::getTrailLength()
{
  return m_TrailLength;
}

bool Bullet::AIsInFlight()
{
  return m_AIsInFlight;
}
bool Bullet::BIsInFlight()
{
  return m_BIsInFlight;
}

void Bullet::shoot(int bulletSpeed, int* colourArray)
{
  m_AIsInFlight = true;
  m_Speed = bulletSpeed;
  
  m_ColourR[0] = colourArray[0];
  m_ColourG[0] = colourArray[1];
  m_ColourB[0] = colourArray[2];

  //set colour values for the trail
  for (int i = (m_HeadAPos + m_TrailLength) - 1; i >= 0; i--)
  {
    double factor = (0.15 * i/(m_HeadAPos + m_TrailLength)); //0.15 seems to work well for the second light, if the lead one is 255 brightness.
    m_ColourR[i] = factor * colourArray[0];
    m_ColourG[i] = factor * colourArray[1];
    m_ColourB[i] = factor * colourArray[2];
  }
}

int Bullet::getColourR(int index)
{
  int r = m_ColourR[index];
  return r;
}
int Bullet::getColourG(int index)
{
  int g = m_ColourG[index];
  return g;
}
int Bullet::getColourB(int index)
{
  int b = m_ColourB[index];
  return b;
}
