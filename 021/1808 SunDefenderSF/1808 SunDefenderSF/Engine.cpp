//
//  Engine.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include <iostream> //for debugging
#include "Engine.h"
#include "ResourcePath.hpp"

//Constructor
Engine::Engine()
{
    /*******
     Initialise objects for display
     ********/
    //get screen resolution and create an SFML window and view
    Vector2f resolution;
   // resolution.x = VideoMode::getDesktopMode().width;
   // resolution.y = VideoMode::getDesktopMode().height;
    
    resolution.x = 1000;
    resolution.y = 1200;
    
    m_Window.create(VideoMode(resolution.x, resolution.y), "Sun Defender",Style::Resize);
    
    //initialise full screen view
    m_MainView.setSize(resolution);
 //   m_HudView.reset(FloatRect(0,0,resolution.x, resolution.y));
    
    /*******
     Initialise objects for graphics
     ********/
     m_BackgroundTexture = TextureHolder::GetTexture(resourcePath() + "SunDefender_background-01.png");
    //associate sprite with the texture
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
    m_BackgroundSprite.setPosition(0, -100);
}

void Engine::run()
{
    while (m_Window.isOpen())
    {
        m_Input();
        m_Update();
        m_Render();
    }
}

