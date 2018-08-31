//
//  Render.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Engine.h"

void Engine::m_Render()
{
    //rub out last frame
    m_Window.clear(Color::White);
    
        //Switch to m_MainView
        m_Window.setView(m_MainView);
        //draw background
        m_Window.draw(m_BackgroundSprite);
    
       // if (m_Playing)
       // {
        m_Window.draw(sun.getSprite());
    
    
    
    for(int i = 0; i < m_numCanons; i++)
    {
        m_Window.draw(player[i].getSprite());
    }
    
    for(int i = 0; i < m_NumEnemies; i++)
    {
        m_Window.draw(enemies[i].getSprite());
    }
    
      //  }
    
    //Draw the HUD
    //Switch to m_HudView
  //  m_Window.setView(m_HudView);
    
    //Show everything we've just drawn
    m_Window.display();
}
