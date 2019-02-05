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
  m_HeadAPos = -1.0f;
  m_HeadBPos = 130.0f;
  m_TrailLength = 5.0f;
  m_AIsInFlight = false;
  m_BIsInFlight = false;
  m_Speed = 0.0f;
  
}

void Bullet::shoot(float bulletSpeed, long colour)
{
  m_AIsInFlight = true;

  /*
   * Option 1: Boost using simple linear relationship.
   * It's not so noticeable at low speeds, and is very fast at full speed.
   */
   //m_Speed = bulletSpeed * m_BulletSpeedFactor;

  /*
   * Option 2: Boost using parabolic relationship
   * x = a(y-k)^2 + h, where h and k = 0
   * So, x = ay^2, or y = sqrt(x/a)
   * a = 5 reduces the boost effect at high speeds, 
   * while making the effect more significant at low speeds.
   * Experiment with curves here: https://www.desmos.com/calculator/hguanwbkbu
   */
    m_Speed = sqrt(bulletSpeed * m_BulletSpeedFactor/5);
   
  m_Colour = colour;

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

void Bullet::updateBullet(int num_Pixels, float bulletSpeed, unsigned long t)
{
  //what's the instantaneous speed of the bullet?
   if(!m_Boosting)
  {
    m_Speed = bulletSpeed * m_BulletSpeedFactor;
  }
  else if (m_Boosting && ((t - m_BoostStartedAt) >= m_BoostDuration))  //just finished boosting
  {
    m_Boosting = false;
    m_Speed = bulletSpeed * m_BulletSpeedFactor;
  }
  else
  {
    m_Speed = bulletSpeed * m_BulletSpeedFactor * m_BoostFactor;
  }
    
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

bool Bullet::getIsBoosting()
{
  return m_Boosting;
}

void Bullet::setBoosting(unsigned long startedAt)
{
  m_Boosting = true;
  m_BoostsRemaining--;
  m_BoostStartedAt = startedAt;
}

int Bullet::getBoostsRemaining()
{
  return m_BoostsRemaining;
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
long Bullet::getColour(int index)
{
  //do something with index
  return m_Colour;
}
