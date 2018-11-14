//
//  Input.cpp
//
//  Created by Carl Turner on 20/9/18.
//
#include "Engine.h"

void Engine::m_Input(unsigned long t)
{
  if(m_mode == Modes::PLAYING)
  {
    for (int i = 0; i < m_NumPlayers; i++)
    {               
      if (m_Buttons[i].updateButton() && !m_Players[i].getHasFired())
      {
          m_Players[i].setHasFired();
          m_Bullets[i].shoot(m_SlidePots[i].updateSlidePot(),m_Players[i].getColour(), m_BulletSpeedFactor); 
      }
    }
  }
  
  if((m_mode == Modes::IDLE_MODE))
  {

    if(m_RestartButton.updateButton())
    {  
       //reset all variables
       m_ScoreController.ResetScore();
      
      m_NumPlayersReady = 0;
      m_LoadedBullet = 0;
      m_CurrentExplosion = 0;
      m_Level = 0;
      m_NewBestRounds = false;

      loadLevel();
      delay(100); //allow for button bounce, otherwise we just come straight back here
      m_mode = Modes::COUNTDOWN;
    }
  }

  if (m_mode == Modes::GAME_OVER || m_mode == Modes::COUNTDOWN || m_mode == Modes::PLAYING || m_mode == Modes::LEVELLING_UP)
  {     
   if(m_RestartButton.updateButton())
    {  
       for (int i = 0; i < m_NumPlayers; i++)
      {
        for (int j=0; j < m_stripLengthArray[i]; j++)
        {
          m_PlayerLEDS[i].setPixelColor(j, 0); 
        }
          m_PlayerLEDS[i].show(); //turn all LEDs off
      }
      //delay(100); //allow for button bounce, otherwise we just come straight back here
      m_mode = Modes::IDLE_MODE;
    }
  }
}