//
//  Input.cpp
//
//  Created by Carl Turner on 20/9/18.
//
#include "Engine.h"

void Engine::m_Input(unsigned long t)
{
  if((m_mode == Modes::IDLE_MODE))
  {
    if(m_NumPlayersReady >= m_NumPlayers)
    {
       //reset all variables
      for (int i=0; i < m_NumPlayers; i++)
      {
         m_Score[i] = 0;
      }   
      m_NumPlayersReady = 0;
      m_LoadedBullet = 0;
      m_Level = 0;

      loadLevel();
      m_mode = Modes::COUNTDOWN;
    }
    else
    {
      for (int i=0; i < m_NumPlayers; i++)
      {
        if (m_Buttons[i].updateButton() && !m_Players[i].isReady())
        {
          m_Players[i].setReady();
          m_NumPlayersReady++;
        }
      }
    }
  }
  
  if((m_mode == Modes::PLAYING))
  {
    for (int i=0; i < m_NumPlayers; i++)
    {
      if (m_Buttons[i].updateButton() && !m_Players[i].getHasFired())
      {
        m_Players[i].setHasFired();
        m_Players[i].setBulletIndex(m_LoadedBullet);
        m_Bullets[m_LoadedBullet].shoot(m_SlidePots[i].getPotValue(),m_Players[i].getColour()); 
        m_LoadedBullet++;
      }
    }
    if(m_RestartButton.updateButton())
    {  
      m_mode = Modes::IDLE_MODE;
    }
  }
}
