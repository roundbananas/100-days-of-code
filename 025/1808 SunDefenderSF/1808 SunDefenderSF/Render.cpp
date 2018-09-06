//
//  Render.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Engine.h"
#include "ResourcePath.hpp"
#include <iostream> //for debugging

void Engine::m_Render()
{
    if (mode == GameMode::PLAYING)
    {
        //rub out last frame
        m_Window.clear(Color::White);
        
        //Switch to m_MainView
        m_Window.setView(m_MainView);
        //draw background
        m_Window.draw(m_BackgroundSprite);
        
        m_Window.draw(sun.getSprite());
        
        for(int i = 0; i < m_numCanons; i++)
        {
            if(projectiles[i].isInFlight())
            {
            m_Window.draw(projectiles[i].getShape());
            }
        }
        
        for(int i = 0; i < m_numCanons; i++)
        {
            m_Window.draw(player[i].getSprite());
        }
        
        for(int i = 0; i < m_NumEnemies; i++)
        {
            m_Window.draw(enemies[i].getSprite());
        }
        
        for(int i = 0; i < m_NumEnemyLasers; i++)
        {
            if(enemyLasers[i].getOn())
            {
            m_Window.draw(enemyLasers[i].getSprite());
            }
        }
        
        //Draw the HUD
        //Switch to m_HudView
        //  m_Window.setView(m_HudView);
    }
    
    if(mode == GameMode::GAME_OVER)
    {
        //load font
        Font font;
        font.loadFromFile(resourcePath() + "zombiecontrol.ttf");
        
        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(40);
        gameOverText.setFillColor(Color::White);
        gameOverText.setPosition(5, 500);
        gameOverText.setString("              Press 1 to restart");
        m_Window.draw(gameOverText);
    }
    
    if (mode == GameMode::IDLE)
    {
        //rub out last frame
        m_Window.clear(Color::White);
        
        //Switch to m_MainView
        m_Window.setView(m_MainView);
        //draw background
        m_Window.draw(m_BackgroundSprite);
    }
    
    //Show everything we've just drawn
    m_Window.display();
}
