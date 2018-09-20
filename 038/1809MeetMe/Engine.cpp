//
//  Engine.cpp
//
//  Created by Carl Turner on 18/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#include "Engine.h"
#include "Arena.h"

Engine::Engine()
{  
    //Initialise displays
  
    for (int i = 0; i < m_NumPlayers; i++)
    {
    m_PlayerLEDS[i].begin(); //initialise pins for output
    m_PlayerLEDS[i].show(); //turn all LEDs off
    }
   
}

void Engine::runEngine()
{
  unsigned long lastTime = 0; //used to calculate dt if we need it

  while(true)
  {
    unsigned long t = millis();
    unsigned long dt = t - lastTime;
    
    m_Input(t);
    m_Update(dt, t);
    m_Render();
    
    lastTime = t;
  }
  
}
void Engine::loadLevel()
{
  m_Level++;

  delete[] m_Players;
  delete[] m_Bullets;
  delete[] m_Buttons;
 // delete[] m_PlayerLEDS;
  delete[] m_SlidePots;

  m_Players = createPlayers(m_NumPlayers);
  m_SlidePots = createPots(m_NumPlayers, m_firstPotPin);
  m_Buttons = createButtons(m_NumPlayers, m_firstButtonPin);
//  m_PlayerLEDS = createLEDS(m_NumPlayers);
  m_RestartButton.spawn(m_RestartButtonPin);

  m_Bullets = createBullets(m_NumBullets);
}
