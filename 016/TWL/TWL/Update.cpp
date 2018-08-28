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
    if (m_NewLevelRequired)
    {
        //These spawns will be moved to a new LoadLevel function eventually
        m_Thomas.spawn(Vector2f(0, 0), GRAVITY);
        m_Bob.spawn(Vector2f(100, 0), GRAVITY);
        
        //make sure spawn is only called once
        m_TimeRemaining = 10; //in seconds
        m_NewLevelRequired = false;
    }
    
    if (m_Playing)
    {
        //Update Thomas and bob
        m_Thomas.update(dtAsSeconds);
        m_Bob.update(dtAsSeconds);
        
        //Count down the time the player has left
        m_TimeRemaining -= dtAsSeconds;
        
        //Have tHomas and Bob run out of time?
        if (m_TimeRemaining <= 0)
        {
            m_NewLevelRequired = true;
        }
    } //End if playing
    
    //Set appropriate view around character
    if (m_SplitScreen)
    {
        m_LeftView.setCenter(m_Thomas.getCenter());
        m_RightView.setCenter(m_Bob.getCenter());
    }
    else
    {
        //center full screen around appropriate character
        if (m_Character1)
        {
            m_MainView.setCenter(m_Thomas.getCenter());
        }
        else
        {
            m_MainView.setCenter(m_Bob.getCenter());
        }
    }// End setting view
}
