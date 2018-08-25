//
//  Input.cpp
//  TWL
//
//  Created by Carl Turner on 24/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Engine.h"

void Engine::input()
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
            
            //Switch between Thomas and Bob characters
            if (Keyboard::isKeyPressed(Keyboard::Q))
            {
                m_Character1 = !m_Character1;
            }
            
            //Switch between full and split screen
            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                m_SplitScreen = !m_SplitScreen;
            }
        }
    }
}
