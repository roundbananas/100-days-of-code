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
        
        for(int j = 0; j < m_projectileArraySize; j++)
        {
            if(canon0Projectiles[j].isInFlight())
            {
                m_Window.draw(canon0Projectiles[j].getShape());
            }
            if(canon1Projectiles[j].isInFlight())
            {
                m_Window.draw(canon1Projectiles[j].getShape());
            }
            if(canon2Projectiles[j].isInFlight())
            {
                m_Window.draw(canon2Projectiles[j].getShape());
            }
            if(canon3Projectiles[j].isInFlight())
            {
                m_Window.draw(canon3Projectiles[j].getShape());
            }
            if(canon4Projectiles[j].isInFlight())
            {
                m_Window.draw(canon4Projectiles[j].getShape());
            }
        }
        
        for(int i = 0; i < m_numCanons; i++)
        {
            if(mtnProjectiles[i].getOn())
            {
            m_Window.draw(mtnProjectiles[i].getSprite());
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
        m_Window.setView(m_HudView);
        m_Window.draw(m_Hud.getScore());
        m_Window.draw(m_Hud.getLevel());
    }
    
    if(mode == GameMode::GAME_OVER)
    {
        m_Window.setView(m_HudView);
        m_Window.draw(m_Hud.getScore());
        m_Window.draw(m_Hud.getLevel());
        m_Window.draw(m_Hud.getGameOverText());
    }
    
    if(mode == GameMode::LEVELLING_UP)
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
            m_Window.draw(player[i].getSprite());
        }
        
        m_Window.setView(m_HudView);
        m_Window.draw(m_Hud.getScore());
        m_Window.draw(m_Hud.getLevel());
        m_Window.draw(m_Hud.getLevelUpText());
    }
    
    if (mode == GameMode::IDLE)
    {
        //rub out last frame
        m_Window.clear(Color::White);
        
        //Switch to m_MainView
        m_Window.setView(m_MainView);
        //draw background
        m_Window.draw(m_BackgroundSprite);
        
        m_Window.setView(m_HudView);
        m_Window.draw(m_Hud.getTitle());
      //  m_Window.draw(m_Hud.getSynopsis());
        m_Window.draw(m_Hud.getHowToHeading());
        m_Window.draw(m_Hud.getHowToInstructions());
        m_Window.draw(m_Hud.getAuthorText());
    }
    
    //Show everything we've just drawn
    m_Window.display();
}
