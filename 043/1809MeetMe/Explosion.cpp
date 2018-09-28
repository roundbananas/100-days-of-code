//
//  Explosion.cpp
//
//  Created by Carl Turner on 27/9/18.
//

#include "Explosion.h"

Explosion::Explosion()
{
  //initialise colour, speed or duration, maybe a random variable
   m_Colour[0] = 255;
   m_Colour[1] = 255;
   m_Colour[2] = 255;
   m_Active = false;
}
bool Explosion::IsActive()
{
  return m_Active;
}
void Explosion::SetActive(unsigned long currentTime, int strip, float pos)
{
  m_Active = true;
  m_StartedAt = currentTime;
  m_Strip = strip;      
  m_Position = pos;
}
void Explosion::Update(unsigned long t)
{
  //this needs to update position.
  //I might need multiple positions
}

int* Explosion::GetColour()
{
  return m_Colour[3];
}
float Explosion::GetPosition()
{
  return m_Position;
}
 int Explosion::GetStrip()
 {
  return m_Strip;
 }
