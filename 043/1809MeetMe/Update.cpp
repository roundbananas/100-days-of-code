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
   //Update the bullet positions     
   for (int i = 0; i< m_NumBullets; i++)
   { 
      for (int j = 0; j < m_NumPlayers; j++)
      {
        if (i == m_Players[j].getBulletIndex() && m_Players[j].getHasFired()) //m_Bullets[i].AIsInFlight()
        {
          m_Bullets[i].updateBullet(m_stripLengthArray[0], dt); //NEED TO FIX STRIP LENGTH ARRAY INDEX IF STRIPS ARE OF DIFFERENT LENGTHS  
        }
         if (!m_Players[j].getHasFired() ) //If player hasn't fired, we can't refer to the bullets because they haven't been associated with the player yet.
        {
        }    
      }
   }

   //update explosions
   for (int i = 0; i < m_NumExplosions; i++)
   {
    if (m_Explosions[i].IsActive())
    {
      m_Explosions[i].Update(t);
    }
   }
   
    //Handle collisions etc
    int explodeOnStrip; //which led strip is the explosion happening on?
    float explodePosition;  //where on the led strip is the explosion happening?
    for (int i = 0; i < m_NumBullets; i++)
    {
      for (int j = 0; j < m_NumBullets; j++)
      {
        if (i == j)
        {
          //the bullet can't collide with itself. Do nothing
        }
        else 
        {
          if ((m_Bullets[i].getHeadAPos() + m_Bullets[j].getHeadBPos() >= 2 * m_stripLengthArray[0]) || (m_Bullets[i].getHeadBPos() + m_Bullets[j].getHeadAPos() >= 2 * m_stripLengthArray[0])) //Assumes all strips are same length. //Need to initialise both head A and B to 0, otherwise this check will perform erratically
          {
            //get strip and position
            if (m_Bullets[i].BIsInFlight()) //bullet i has crossed the peak. It's extremely unlikely, near impossible that both bullets will meet at the exact middle so there'll only ever be one bullet with B in flight. Even with 100 strips, one bullet will always be first to cross the peak and trigger BIsInFlight.
            {
              m_Bullets[j].Stop();  //toggle AIsInFlight to false so bullet j doesn't get rendered anymore
              explodePosition = m_Bullets[j].getHeadAPos();
              explodeOnStrip = getExplodeStrip(j);
              m_Explosions[m_CurrentExplosion].SetActive(t, explodeOnStrip, explodePosition);
            }
            else //bullet j has BinFlight (ie it's cross over to another player's strip)
            {
              m_Bullets[i].Stop();
              explodePosition = m_Bullets[i].getHeadAPos();
              explodeOnStrip = getExplodeStrip(i);
              m_Explosions[m_CurrentExplosion].SetActive(t, explodeOnStrip, explodePosition);
            }
            m_CurrentExplosion++;
          }//end if
        }//end else
      }//end for
    }//end for and END COLLISIONS
    
  } //end PLAYING mode

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
  } //end COUNTDOWN mode
}
