//
//  Bullet.cpp
//
//  Created by Carl Turner on 17/9/18.
//
#include "Bullet.h"

Bullet::Bullet()
{
  

}

void Bullet::spawn()
{
  m_HeadAPos = 0;
  m_HeadBPos = 0;
  m_TrailLength = 5;
  m_AIsInFlight = false;
  m_BIsInFlight = false;
  m_Speed = 0;
  Serial.print ("SPAWN BULLET. HeadA / HeadB / length / inflight?: ");
  Serial.print (m_HeadAPos); Serial.print (" / ");
  Serial.print (m_HeadBPos); Serial.print (" / ");
  Serial.print (m_TrailLength); Serial.print (" / ");
  Serial.println (m_AIsInFlight);Serial.print (" ");
}

int Bullet::getBulletSpeed()
{
    return m_Speed;
}

void Bullet::updateBullet(int num_Pixels)
{
  if(m_BIsInFlight)
  {
     m_HeadBPos++;
     
     if(m_HeadBPos > num_Pixels + m_TrailLength)
      {
        m_BIsInFlight = false;
      }
  }
  if(m_HeadAPos > num_Pixels)
  {
    m_BIsInFlight = true;
    
    if(m_HeadAPos > num_Pixels + m_TrailLength)
    {
      m_AIsInFlight = false;
    }
  }
  
  m_HeadAPos++;
  
  Serial.println("IN Update Bullet");
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
  Serial.println ("* BULLET: SHOOTING *");
  Serial.print ("shoot in Flight? "); Serial.println (m_AIsInFlight);
  m_AIsInFlight = true;
  Serial.print ("shoot in Flight? "); Serial.println (m_AIsInFlight);
  m_Speed = bulletSpeed;
  
  m_ColourR[0] = colourArray[0];
  m_ColourG[0] = colourArray[1];
  m_ColourB[0] = colourArray[2];

  double factor = 0.15; //0.15 seems to work well for the second light, if the lead one is 255 brightness.

  //set colour values for the trail
  for (int i = 1 ; i < m_TrailLength; i++)
  {
    m_ColourR[i] = factor * colourArray[0];
    m_ColourG[i] = factor * colourArray[1];
    m_ColourB[i] = factor * colourArray[2];
    factor *= 0.9;
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
