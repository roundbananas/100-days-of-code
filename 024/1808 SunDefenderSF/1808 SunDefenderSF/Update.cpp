//
//  Update.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Engine.h"

using namespace sf;

void Engine::m_Update(double currentTime, double lastTime)
{
    
    if (mode == GameMode::PLAYING)
    {
        double dt = currentTime - lastTime;
        //1. update the game time
        //2. update position of any player controls (eg mouse pointer)
        //3. update position of player
        //4. check if each enemy is alive, and if so update it, including enemy lasers
        //5. update player projectiles
        //6a. collision detection - have any enemies been shot? loop through each projectile for each enemy to see if there's any intersections
        //6b. update score and #enemies alive
        //6c. if all enemies dead, change game mode
        //7. update the sun, if it's dead change game mode
        //8. update any UI elements
        //9. update the hud, if it's time to do so
        
        
        
        /****
         UPDATE THE PLAYER 'position' and controls
         - In this game this means update canon status
         ****/
        for(int i = 0; i < m_numCanons; i++)
        {
            player[i].update(currentTime);
        }
        
        /****
         UPDATE THE ENEMIES
         ****/
        // std::cout << "\nTime: " << current_time;
        for(int i = 0; i < m_NumEnemies; i++)
        {
            if (enemies[i].isAlive())
            {
                enemies[i].updateD(currentTime, m_mtnArrayDigital);
                /****
                 UPDATE THE LASERS FOR ENEMIES THAT ARE ALIVE
                 ****/
                if(enemies[i].isShooting())
                {
                    //which peak are they shooting from?
                    Vector2f enemyPos = enemies[i].getPosition();
                    //so, which laser do we want to update?
                    
                    for(int j = 0; j < m_NumEnemyLasers; j++)
                    {
                        Vector2f laserPos = enemyLasers[j].getPeakPosition();
                       
                        
                        if(enemyLasers[j].getPeakPosition() == enemyPos)
                        {
                            
                            int shootDuration = enemies[i].getShootDuration();
                            enemyLasers[j].update(dt, shootDuration);
                        }
                    }
                }
            }
        }
        
        /****
         UPDATE CANON PROJECTILES THAT ARE IN FLIGHT
         ****/

        
        /****
         COLLISION DETECTION
         - Have any enemies been shot?
         - Update score and #enemies alive
         - If all enemies dead, change game mode to levellingup
         ****/
        
        
        /****
         COLLISION DETECTION
         - Has the sun been shot?
         - Update sun health
         - if sun is dead change game mode to gameover
         ****/
        //Normally we might loop through each laser for each sun segment, to check if there's any collision. BUT, in this game the way the sun is affected by lasers differs.
        //The sun has a total life: double m_SunLife. //in 'units' (use double because the Timer object uses a double.
        //Enemy lasers have an effect of draining sunlife at a rate: double m_EnemyLaserEffect; //in 'units per second'
        //So, if enemie lasers have shot the sun for a total of: m_SunLife/m_EnemyLaserEffect seconds, the sun will be completely drained.
        //So we need to create a variable to hold how many seconds the sun has been shot so far: double m_TotalTimeSunHasBeenLasered
        
        //cycle through each laser for each enemy, and if laser has just been turned off, add the enemy's shootduration time to the total time the sun's been lasered.
        //then, update the sun's remaining life.
        //if sun is dead change game mode
        for(int i = 0; i < m_NumEnemyLasers; i++)
        {
            for (int j = 0; j< m_NumEnemies; j++)
            {
                if (enemies[i].getJustStoppedShooting() && sun.isAlive())
                {
                    double time = enemies[j].getShootDuration();
                    sun.update(time);   //this function toggles m_SunAlive to false when the sun is dead.
                    if(!sun.isAlive())
                    {
                        mode = GameMode::GAME_OVER;
                    }
                }
            }
        } //End sun being shot

        /****
         UPDATE UI elements
         ****/
        
        
        /****
         UPDATE THE HUD if it's time
         ****/
        
        
    } //End if Playing
}
