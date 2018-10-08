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
   m_Colour = 0xea6e02; //ffa500 = orange, ea6e02 = burnt orange
   m_IsActive = false;
   m_Duration = 500; //0.5ms
   m_MaxSize = 5.0f; //pixels in each direction from position
}
bool Explosion::IsActive()
{
  return m_IsActive;
}
void Explosion::SetActive(unsigned long currentTime, int strip, float pos)
{
  m_IsActive = true;
  m_StartedAt = currentTime;
  m_Strip = strip;      
  m_Position = pos;

  //calculate constants
  m_const_p = m_StartedAt;
  m_const_q = m_StartedAt + m_Duration;
  m_tMaxSize = m_const_p + m_Duration/2;
  m_const_a = m_MaxSize/((m_tMaxSize - m_const_p)*(m_tMaxSize - m_const_q));
}
void Explosion::Update(unsigned long t)
{
  if (t - m_StartedAt < m_Duration)
  {        
    float CurrentSize = m_const_a * (t - m_const_p) * (t - m_const_q);
    float m_Head = m_Position + CurrentSize;
    float m_Tail = m_Position - CurrentSize;
     if (t > m_tMaxSize)
      {
        m_Colour = 0x000000;  //000000 = black
      }
      else if (t <= m_tMaxSize)
      {
        m_Colour = 0xea6e02;
      }
  }
}

int Explosion::GetColour()
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
