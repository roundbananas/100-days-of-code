//
//  Update.cpp
//
//  Created by Carl Turner on 20/9/18.
//
#include "Engine.h"

void Engine::m_Update(unsigned long dt, unsigned long t)
{
  if(m_mode == Modes::PLAYING)
  {
    //if it's time to update bullet
        for (int i = 0; i < m_NumPlayers; i++)
        {
          
          //if the player's bullet is in flight, update it
          if (m_Bullets[m_Players[i].getBulletIndex()].AIsInFlight())
          {
            m_Bullets[m_Players[i].getBulletIndex()].updateBullet(m_stripLengthArray[i]);
             Serial.println ("Update: in flight ");
          }
           if (!m_Bullets[m_Players[i].getBulletIndex()].AIsInFlight())
          {
          //  m_mode = Modes::IDLE_MODE;
            Serial.println ("Update: not in flight ");
          }    
        }
    //Handle collisions etc
  }
  

  if((m_mode == Modes::COUNTDOWN))
  {
    int countDown = 3000; //3 second countdown
    
    if(!m_countDownStarted)
    {
      m_countDownStartedAt = t;
      m_countDownStarted = true;
    }
    //MOVE THE FOLLOWING STUFF TO RENDER()
    if (m_countDownStarted)
    {
      if ((t - m_countDownStartedAt) < 1000)
      {
        //PRINT TO SCREEN: 3
      }
      else if (((t - m_countDownStartedAt) > 1000) && ((t - m_countDownStartedAt) < 2000))
      {
        //PRINT TO SCREEN: 2
      }
      else if ((t - m_countDownStartedAt) > 2000 && (t - m_countDownStartedAt) < countDown)
      {
        //PRINT TO SCREEN: 1
      }
      else if ((t - m_countDownStartedAt) > countDown)
      {
        //PRINT TO SCREEN: GO!
        m_mode = Modes::PLAYING;
        m_countDownStarted = false;
      }
    }
  }
}
