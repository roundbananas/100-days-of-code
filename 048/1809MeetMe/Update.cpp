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
      for (int i = 0; i < m_NumPlayers; i++)
      {
        if (m_Players[i].getHasFired())
        {
          m_Bullets[i].updateBullet(m_stripLengthArray[i], dt); 
        }
        else if (!m_Players[i].getHasFired()) //If player hasn't fired, we can't refer to the bullets because they haven't been associated with the player yet.
        {
          //Could blink their trigger button or something
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
    //1. Loop through each bullet and check against each other bullet to see if they've collided. 
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
          //don't need to check if j partB in flight, cos it'll get checked anyway since we're looping through each bullet for each bullet
          if (m_Bullets[i].BIsInFlight()) 
            {
              //2. A collision occurs if bullet i partB has passed bullet j PartA.
              if (!m_Players[j].isExploding() && (m_Bullets[i].getHeadBPos() <= m_Bullets[j].getHeadAPos()))
              {
                //3. Get the strip and position of the collision.
                /*   We know that It's extremely unlikely, near impossible that both bullets will meet at the exact middle, 
                 *   so we assume there'll only ever be one bullet with partB in flight. 
                 *   And the collision will be on one of the strips that has a bullet PartB in flight.
                 *   ie, not that player's strip.
                 *   (Even with 100 strips, one bullet will almost always be first to cross the peak).
                 */
                  //whose bullet is this?
                 
                  m_Players[j].setIsExploding();
                  m_Players[j].setHasFired(); //to stop them firing after they're dead, if they haven't fired yet
                  m_Bullets[j].StopA();  //make sure bullet j partA is no longer rendered
                  //don't turn off bullet i because we still want it to render on every other strip. 
                  //We'll make sure it doesn't render on the strip with the explosion in render()
                  explodePosition = m_Bullets[j].getHeadAPos();
                  m_Explosions[m_CurrentExplosion].SetActive(t, j, explodePosition);                  
                  m_CurrentExplosion++;
              }//end if
              
            }//end if b in flight
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
