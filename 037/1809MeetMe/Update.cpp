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
    for (int i = 0; i < m_NumPlayers; i++)
    {
      m_Bullets[m_Players[i].getBulletIndex()].updateBullet(dt);
    }

    //Handle collisions etc

    
  }
  

  if((m_mode == Modes::COUNTDOWN))
  {
    bool countDownStarted = false;
    int countDown = 3000; //3 second countdown
    unsigned long countDownStartedAt;
    if(!countDownStarted)
    {
      countDownStartedAt = t;
      countDownStarted = true;
    }
    if (countDownStarted)
    {
      if ((t - countDownStartedAt) < 1000)
      {
        //PRINT TO SCREEN: 3
      }
      else if ((t - countDownStartedAt) < 2000)
      {
        //PRINT TO SCREEN: 2
      }
      else if ((t - countDownStartedAt) < countDown)
      {
        //PRINT TO SCREEN: 1
      }
      else if ((t - countDownStartedAt) > countDown)
      {
        //PRINT TO SCREEN: GO!
        m_mode = Modes::PLAYING;
      }
    }
  }
}
