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
        for (int i=0; i< m_NumBullets; i++)
        
        for (int j = 0; j < m_NumPlayers; j++)
        {
          if (i == m_Players[j].getBulletIndex() && m_Players[j].getHasFired()) //m_Bullets[i].AIsInFlight()
          {
            m_Bullets[i].updateBullet(m_stripLengthArray[0]); //NEED TO FIX STRIP LENGTH ARRAY INDEX IF STRIPS ARE OF DIFFERENT LENGTHS
        //     Serial.println ("Update: in flight ");
          }
           if (!m_Players[j].getHasFired() ) //If player hasn't fired, we can't refer to the bullets because they haven't been associated with the player yet.
          {
          //  m_mode = Modes::IDLE_MODE;
       //     Serial.println ("Update: not in flight ");
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
