//
//  Update.cpp
//  TWL
//
//  Created by Carl Turner on 24/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    if (m_Playing)
    {
        //Count down the time the player has left
        m_TimeRemaining -= dtAsSeconds;
        
        //Have tHomas and Bob run out of time?
        if (m_TimeRemaining <= 0)
        {
            m_NewLevelRequired = true;
        }
    } //End if playing
}
