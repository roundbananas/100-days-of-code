//
//  Input.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//
//The game has 5 buttons. In playing mode they are used to fire each of the five canons. In Levelling_Up mode they are used to make power-up selections. In Game_Over and Idle mode, pressing any button will start a new game.
//There are two ways to get input. Events seem to be most appropriate.
//Events notify you when something happens ("this button was pressed", "the mouse has moved") - syntax "(event.type == sf::Event::KeyPressed)". (https://www.sfml-dev.org/tutorials/2.5/window-events.php) At this stage I think tracking button presses as Events will be enough for this game.
//The other type of input I could grab (using SFML) is real-time input (ie is a key CURRENTLY being pressed) - syntax "sf::Keyboard::isKeyPressed(sf::Keyboard::Left)". (https://www.sfml-dev.org/tutorials/2.5/window-inputs.php) This might be useful if I want the player to be able to hold down a button for rapid fire.

#include "Engine.h"
#include "GameMode.h"
#include "BattleGround.h"
#include "CanonProjectile.h"
#include <iostream>

void Engine::m_Input(double t)
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
            //IDLE: "Press any button to start", GAME_OVER: "Press any button to play again"
            if((mode == GameMode::IDLE || mode == GameMode::GAME_OVER) && ((event.key.code == Keyboard::Num1) || (event.key.code == Keyboard::Num2) || (event.key.code == Keyboard::Num3) || (event.key.code == Keyboard::Num4)|| (event.key.code == Keyboard::Num5) || (event.key.code == Keyboard::Return)))
            {
                /******
                 Initialise NEW game (ie at Level 0).
                 *******/
                
                loadLevel();
                mode = GameMode::PLAYING;
            }
            
            //Handle input while playing
            if(mode == GameMode::PLAYING)
            {
                if (event.key.code == Keyboard::Num1)
                {
                    if(((t - player[0].getLastFired()) > 1/player[0].getFireRate()) && player[0].getCharged())
                    {
                        //set canon to fired and not charged
                        player[0].fireCanon(t);
                        
                        //spawn projectile for the appropriate canon position and target
                        canon0Projectiles[m_currentProjectileCanon0].shoot(0, m_canonArrayDigital, m_ProjectileTargetArray);
                        m_currentProjectileCanon0++;
                        
                        if (m_currentProjectileCanon0 > m_projectileArraySize)
                        {
                            m_currentProjectileCanon0 = 0;
                        }
                    }
                }
                if (event.key.code == Keyboard::Num2)
                {
                    if(((t - player[1].getLastFired()) > 1/player[1].getFireRate()) && player[1].getCharged())
                    {
                        player[1].fireCanon(t);
                        canon1Projectiles[m_currentProjectileCanon1].shoot(1, m_canonArrayDigital, m_ProjectileTargetArray);
                        m_currentProjectileCanon1++;
                        if (m_currentProjectileCanon1 > m_projectileArraySize)
                        {
                            m_currentProjectileCanon1 = 0;
                        }
                    }
                }
                if (event.key.code == Keyboard::Num3)
                {
                    if(((t - player[2].getLastFired()) > 1/player[2].getFireRate()) && player[2].getCharged())
                    {
                        player[2].fireCanon(t);
                        canon2Projectiles[m_currentProjectileCanon2].shoot(2, m_canonArrayDigital, m_ProjectileTargetArray);
                        m_currentProjectileCanon2++;
                        if (m_currentProjectileCanon2 > m_projectileArraySize)
                        {
                            m_currentProjectileCanon2 = 0;
                        }
                    }
                }
                if (event.key.code == Keyboard::Num4)
                {
                    if(((t - player[3].getLastFired()) > 1/player[3].getFireRate()) && player[3].getCharged())
                    {
                        player[3].fireCanon(t);
                        canon3Projectiles[m_currentProjectileCanon3].shoot(3, m_canonArrayDigital, m_ProjectileTargetArray);
                        m_currentProjectileCanon3++;
                        if (m_currentProjectileCanon3 > m_projectileArraySize)
                        {
                            m_currentProjectileCanon3 = 0;
                        }
                    }
                }
                if (event.key.code == Keyboard::Num5)
                {
                    if(((t - player[4].getLastFired()) > 1/player[4].getFireRate()) && player[4].getCharged())
                    {
                        player[4].fireCanon(t);
                        canon4Projectiles[m_currentProjectileCanon4].shoot(4, m_canonArrayDigital, m_ProjectileTargetArray);
                        m_currentProjectileCanon4++;
                        if (m_currentProjectileCanon4 > m_projectileArraySize)
                        {
                            m_currentProjectileCanon4 = 0;
                        }
                    }
                }
            }//END handle input while playing
                        
            //handle levelling up choice, and starting next level
            if (mode == GameMode::LEVELLING_UP)
            {
                if (event.key.code == Keyboard::Num1)
                {
                    //grant powerup type 1
                    mode = GameMode::PLAYING;
                }
                else if (event.key.code == Keyboard::Num2)
                {
                    //grant powerup type 2
                    mode = GameMode::PLAYING;
                }
                else if (event.key.code == Keyboard::Num3)
                {
                    //grant powerup type 3
                    mode = GameMode::PLAYING;
                }
                else if (event.key.code == Keyboard::Num4)
                {
                    //grant powerup type 4
                    mode = GameMode::PLAYING;
                }
                else if (event.key.code == Keyboard::Num5)
                {
                    //grant powerup type 5
                    mode = GameMode::PLAYING;
                }
                //if we were levelling up and we switched to playing mode, launch a new level
                if(mode == GameMode::PLAYING)
                {
                    //initialise next level
                    /***TO DO LATER: increase number, speed, types of enemies****/
                    
                    loadLevel();
                }
            }//END handle levelling up
        }//END event polling for a key press
    } //END all event polling
    
    
    
    
    //maybe include inpiut for managing rapid fire here later
}
