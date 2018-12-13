// dodo 
//  ESP_Render.cpp
//
//  Created by Carl Turner on 11/12/18.
//
//  Update LED pixel colours and refresh the strips

#include "ESP_Engine.h"

void ESP_Engine::m_Render()
{
  for (int i = 0; i < m_NumPlayers; i++)  m_LedStrips[i].show();	
}// End Render()
