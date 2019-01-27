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
      if (m_Players[i].getHasFired() && m_BoostButtons[i].updateButton())
      {
        m_Bullets[i].setBoosting(t);
      }
                 
      if (m_Buttons[i].updateButton() && !m_Players[i].getHasFired())
      {
          m_Players[i].setHasFired();
          m_Bullets[i].shoot(m_SlidePots[i].updateSlidePot(),m_Players[i].getColour()); 
      }
    }
  }
  
  if((m_mode == Modes::IDLE_MODE))
  {

    if(m_RestartButton.updateButton())
    {  
      StartNewGame();
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
      
      StartNewGame();
    }
  }
}
