//
//  Explosion.cpp
//
//  Created by Carl Turner on 27/9/18.
//

#include "Explosion.h"
#include "Arduino.h"


Explosion::Explosion()
{
  //initialise colour, speed or duration, maybe a random variable
 
}
void Explosion::Spawn()
{
   m_Colour[0] = 0;
   m_Colour[1] = 255;
   m_Colour[2] = 0;
   m_Active = false;

   m_Duration = 5000; //5ms
   m_Size = 6.0f; //pixels in each direction from position
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
  if (t - m_StartedAt < m_Duration)
  {
    int CurrentSize = -((t - m_StartedAt) - m_Duration/2) + m_Size;
    m_Head = m_Position + CurrentSize;
    m_Tail = m_Position - CurrentSize;
  }
  
}

int* Explosion::GetColour()
{
  return m_Colour;
}
float Explosion::GetPosition()
{
  return m_Position;
}
 int Explosion::GetStrip()
 {
  return m_Strip;
 }

float Explosion::GetHead()
{
  return m_Head;
}
float Explosion::GetTail()
{
  return m_Tail;
}
