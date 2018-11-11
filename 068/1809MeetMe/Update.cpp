//
//  Update.cpp
//
//  Created by Carl Turner on 20/9/18.
//
#include "Engine.h"

void Engine::m_Update(unsigned long dt, unsigned long t)
{
/*
   * LEVELLING UP MODE
   */
  if(m_mode == Modes::LEVELLING_UP)
  {     
    if ((t - m_ModeStartedAt) > m_TimeoutLevelUp)
    {
      m_ScoreDisplay.setNumber(m_ScoreController.GetCurrentScore());
      m_CurrentRoundDisplay.setNumber(m_Level);
      m_BestRoundsDisplay.setNumber(m_BestRounds);
      m_mode = Modes::COUNTDOWN;
    }
  }//end Levelling_Up mode
  
  /*
   * PLAYING MODE
   */
  if(m_mode == Modes::PLAYING)
  {           
   //Update the bullet positions     
      for (int i = 0; i < m_NumPlayers; i++)
      {
        if (!m_Players[i].isExploding() && m_Players[i].getHasFired())
        {
          m_PlayerButtonLeds[i].SetMode(0); //turn off their button led
          m_Bullets[i].updateBullet(m_stripLengthArray[i], m_SlidePots[i].updateSlidePot(), dt); 
        }
        else if (!m_Players[i].isExploding() && !m_Players[i].getHasFired()) //If player hasn't fired, we can't refer to the bullets because they haven't been associated with the player yet.
        {
            m_PlayerButtonLeds[i].SetMode(1); //set the button led on
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
        //don't need to check if j partB in flight, cos it'll get checked anyway since we're looping through each bullet for each bullet
        else if (m_Bullets[i].BIsInFlight())  
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

                  m_Bullets[j].StopA();  //make sure bullet j partA is no longer rendered
                  m_Players[j].setIsExploding();
                  m_Players[j].setHasFired(); //to stop them firing after they're dead, if they haven't fired yet
                  //don't turn off bullet i because we still want it to render on every other strip. 
                  //We'll make sure it doesn't render on the strip with the explosion in render()
                  explodePosition = m_Bullets[j].getHeadAPos();
                  m_Explosions[m_CurrentExplosion].SetActive(t, j, explodePosition);                  
                  m_CurrentExplosion++;
                  m_LastExplosionStartedAt = t;
                  //Update Score
                  int scoreValue = (int)(explodePosition + 0.0); //typecast float to int
                  m_ScoreController.AddScore(scoreValue, m_stripLengthArray[j]);

              }//end if
              
            }//end else if b in flight
           
      }//end for
    }//end for and END COLLISIONS 

    if (m_ScoreController.GetTargetReached())
    {
      if(m_BestRounds == 0)
      {
        m_BestRounds = m_Level;
      }
      else if(m_Level < m_BestRounds)
      {
        m_BestRounds = m_Level;
        m_NewBestRounds = true; //this is to tell us to throw a party when a new record is set. See Game_Over mode loop below.
      }
       m_mode = Modes::GAME_OVER;
    }
    else if (m_mode == Modes::PLAYING && ((m_CurrentExplosion >= m_NumExplosions - 1) && (t - m_LastExplosionStartedAt > 300))) //wait before changing modes, to help let people make transition
    {
       loadLevel();
       m_ScoreDisplay.setNumber(m_ScoreController.GetCurrentScore());
       m_CurrentRoundDisplay.setNumber(m_Level);
       m_BestRoundsDisplay.setNumber(m_BestRounds);
       m_ModeStartedAt = millis();
       m_mode = Modes::LEVELLING_UP;
    }
  } //end PLAYING mode
 
 
 /*
   * COUNTDOWN MODE
   */
  if((m_mode == Modes::COUNTDOWN))
  { 
    if(!m_countDownStarted)
    {
      m_countDownStartedAt = t;
      m_countDownStarted = true;
    }
    if (m_countDownStarted)
    {       
        if (t - m_countDownStartedAt > 3000)
        {
          m_mode = Modes::PLAYING;
          m_countDownStarted = false;
          m_CountDownRemaining = m_CountDownDuration;
        }
        else if (t - m_countDownStartedAt > 2000)
        {
          m_CountDownRemaining = 0;
        }
        else if (t - m_countDownStartedAt > 1000)
        {
          m_CountDownRemaining = 1;
        }
        else if (t - m_countDownStartedAt > 0)
        {
          m_CountDownRemaining = 2;
        }
    }
  } //end COUNTDOWN mode

 /*
   * GAME_OVER MODE
   */
  if((m_mode == Modes::GAME_OVER))
  { 
    //do some cool animation thing, celebration
      m_ScoreDisplay.setNumber(m_ScoreController.GetCurrentScore());
      m_CurrentRoundDisplay.setNumber(m_Level);
      m_BestRoundsDisplay.setNumber(m_BestRounds);
      
    if(m_NewBestRounds)
    {
      //if they set a new 'best rounds', let them know.

      m_NewBestRounds = false;
    }
  }

} //end update()
