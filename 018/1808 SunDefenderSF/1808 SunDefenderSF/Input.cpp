//
//  Input.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Engine.h"

void Engine::m_Input()
{
    Event event;
    while(m_Window.pollEvent(event))
    {
        if(event.type == Event::KeyPressed)
        {
            //Handle player quitting
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_Window.close();
            }
            
            //handle player starting the game
            if(Keyboard::isKeyPressed(Keyboard::Return))
            {
                m_Playing = true;
                
            }
        }
    }
}
