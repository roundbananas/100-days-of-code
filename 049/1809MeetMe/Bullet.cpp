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
  m_HeadAPos = 0.0f;
  m_HeadBPos = 25.0f;
  m_TrailLength = 5.0f;
  m_AIsInFlight = false;
  m_BIsInFlight = false;
  m_Speed = 0.0f;
  Serial.print ("SPAWN BULLET. HeadA / HeadB / length / inflight?: ");
  Serial.print (m_HeadAPos); Serial.print (" / ");
  Serial.print (m_HeadBPos); Serial.print (" / ");
  Serial.print (m_TrailLength); Serial.print (" / ");
  Serial.println (m_AIsInFlight);Serial.print (" ");
}

void Bullet::shoot(float bulletSpeed, int* colourArray, float speedFactor)
{
 // Serial.println ("* BULLET: SHOOTING *");
  m_AIsInFlight = true;
  m_Speed = bulletSpeed * speedFactor;
  
  m_ColourR[0] = colourArray[0];
  m_ColourG[0] = colourArray[1];
  m_ColourB[0] = colourArray[2];
/*
  double factor = 0.15; //0.15 seems to work well for the second light, if the lead one is 255 brightness.

  //set colour values for the trail
  for (int i = 1 ; i < m_TrailLength; i++)
  {
    m_ColourR[i] = factor * colourArray[0];
    m_ColourG[i] = factor * colourArray[1];
    m_ColourB[i] = factor * colourArray[2];
    factor *= 0.9;
  }
  */
}

void Bullet::updateBullet(int num_Pixels, unsigned long dt)
{
  //equation of motion, assuming zero acceleration. (Would be cool to add acceleration as they come to crash)
  // position = previous_position + speed*dt
  if(m_BIsInFlight)
  {
     m_HeadBPos -= m_Speed;
     
     if(m_HeadBPos < 0 - m_TrailLength)
      {
        m_BIsInFlight = false;
      }
  }
  if (m_AIsInFlight)
  {
    if(m_HeadAPos >= num_Pixels - 1)
    {
      m_BIsInFlight = true;
      
      if(m_HeadAPos > num_Pixels + m_TrailLength)
      {
        m_AIsInFlight = false;
      }
    }
  }
 
  m_HeadAPos += m_Speed;
}

float Bullet::getHeadAPos()
{
     return m_HeadAPos; 
}
float Bullet::getTailAPos()
{
    return m_HeadAPos - m_TrailLength;
}

float Bullet::getHeadBPos()
{
     return m_HeadBPos; 
}
float Bullet::getTailBPos()
{
    return m_HeadBPos + m_TrailLength;
}

float Bullet::getTrailLength()
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
void Bullet::StopA()
{
  m_AIsInFlight = false;
}
void Bullet::StopB()
{
  m_BIsInFlight = false;
}
float Bullet::getBulletSpeed()
{
    return m_Speed;
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
