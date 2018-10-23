//
//  Engine.cpp
//
//  Created by Carl Turner on 22/10/18.
//

#include "Engine.h"

Engine::Engine()
{ 	
	m_Mode.control = RC_MODE;
    m_Mode.mood = IDLE;
    m_Mode.startedAt = millis();
}

void Engine::runEngine()
{
	//  unsigned long lastTime = 0; //used to calculate dt if we need it
  
    while (true)
    {
        unsigned long t = millis();
      //  unsigned long dt = t - lastTime;

        m_Input(t);
        m_Update(t);
        m_Render();

      //  lastTime = t;
    }
}