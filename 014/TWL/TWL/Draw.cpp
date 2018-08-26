//
//  Draw.cpp
//  TWL
//
//  Created by Carl Turner on 24/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Engine.h"

void Engine::draw()
{
    //rub out last frame
    m_Window.clear(Color::White);
    
    if (!m_SplitScreen)
    {
        //switch to background view
        m_Window.setView(m_BGMainView);
        //draw background
        m_Window.draw(m_BackgroundSprite);
        //Switch to m_MainView
        m_Window.setView(m_MainView);
    }
    else
    {
        //Split screen view is active
      //  m_Window.clear(Color::White);
        //First draw Thomas' side of the screen
        
        //switch to background view
        m_Window.setView(m_BGLeftView);
        //draw background
        m_Window.draw(m_BackgroundSprite);
        //Switch to m_MainView
        m_Window.setView(m_LeftView);
        
        //Now draw Bob's side of the screen
        
        //switch to background view
        m_Window.setView(m_BGRightView);
        //draw background
        m_Window.draw(m_BackgroundSprite);
        //Switch to m_MainView
        m_Window.setView(m_RightView);
    }
    
    //Draw the HUD
    //Switch to m_HudView
    m_Window.setView(m_HudView);
    
    //Show everything we've just drawn
    m_Window.display();
}
