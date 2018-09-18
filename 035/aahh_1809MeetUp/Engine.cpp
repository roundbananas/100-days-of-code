//
//  Engine.cpp
//
//  Created by Carl Turner on 18/9/18.
//

#include "Engine.h"

Engine::Engine()
{
   

  
}
void Engine::runEngine()
{
  //unsigned long lastTime = 0; //used to calculate dt if we need it
  
  while(true)
  {
    unsigned long t = millis();
    
    m_Input(t);
    m_Update(t);
    m_Render();
    
    //lastTime = t;
  }
  
}
void Engine::loadLevel()
{
  m_Level++;
  
}

void Engine::m_Input(unsigned long currentTime)
{
  
}
void Engine::m_Update(unsigned long currentTime)
{
  
}
void Engine::m_Render()
{
  
}
