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
        
        //Draw Thomas
        m_Window.draw(m_Thomas.getSprite());
        m_Window.draw(m_Bob.getSprite());
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
        
        //Draw characters. Note order - Thomas is drawn on top cos it's his side of screen.
        m_Window.draw(m_Bob.getSprite());
        m_Window.draw(m_Thomas.getSprite());
        
        
        //Now draw Bob's side of the screen
        
        //switch to background view
        m_Window.setView(m_BGRightView);
        //draw background
        m_Window.draw(m_BackgroundSprite);
        //Switch to m_MainView
        m_Window.setView(m_RightView);
        
        //Draw characters. Note order - Bob is drawn on top cos it's his side of screen.
        m_Window.draw(m_Thomas.getSprite());
        m_Window.draw(m_Bob.getSprite());
    }
    
    //Draw the HUD
    //Switch to m_HudView
    m_Window.setView(m_HudView);
    
    //Show everything we've just drawn
    m_Window.display();
}
