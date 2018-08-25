//
//  Engine.cpp
//  TWL
//
//  Created by Carl Turner on 24/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "ResourcePath.hpp"
#include "Engine.h"

//CONSTRUCTOR
Engine::Engine()
{
    //get screen resolution and create an SFML window and view
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    
    m_Window.create(VideoMode(resolution.x, resolution.y), "Thomas was late", Style::Resize);
    
    //initialise full screen view
    m_MainView.setSize(resolution);
    m_HudView.reset(FloatRect(0,0,resolution.x, resolution.y));
    
    //Initialise split-screen views
    //works using ratio where 1 is the entire screen width or height
    //FloatRect(x-start, y-start, x-end, y-end)
    m_LeftView.setViewport(
                           FloatRect(0.001f, 0.001f, 0.499f,0.998f));
    m_RightView.setViewport(
                           FloatRect(0.501f, 0.001f, 0.998f,0.998f));
    m_BGLeftView.setViewport(
                           FloatRect(0.001f, 0.001f, 0.499f,0.998f));
    m_BGRightView.setViewport(
                           FloatRect(0.501f, 0.001f, 0.998f,0.998f));

    m_BackgroundTexture = TextureHolder::GetTexture(resourcePath() + "background.png");
    
    //associate sprite with the texture
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
}

// GAME LOOP
void Engine::run()
{
    //timing
    Clock clock;
    
    while(m_Window.isOpen())
    {
        //cloct.restart() puts the time counter back to zero. It also returns the time elapsed since the clock was started.
        Time dt = clock.restart();
        //update total game time
        m_GameTimeTotal += dt;
        //make a decimal fraction from dt
        float dtAsSeconds = dt.asSeconds(); //this is the fraction of a second that elapsed during the previous frame
        
        //Call each part of the game loop in turn
        //we call private functions declared in Engine.h
        //these private functions are defined in their own cpp files
        input();
        update(dtAsSeconds);
        draw();
    }
}
