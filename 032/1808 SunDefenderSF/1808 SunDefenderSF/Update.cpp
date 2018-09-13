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
        for(int i = 0; i < m_NumEnemies; i++)
        {
            /****
             UPDATE THE ENEMY LASERS FOR ENEMIES THAT ARE ALIVE
             ****/
            if (enemies[i].isAlive() && !enemies[i].isShooting())
            {
                for(int j = 0; j < m_NumEnemyLasers; j++)
                {
                     Vector2f enemyPos = enemies[i].getPosition();
                    Vector2f laserPos = enemyLasers[j].getPeakPosition();
                    if(laserPos == enemyPos)
                    {
                        enemyLasers[j].turnOff();
                    }
                }
            }
            if (enemies[i].isAlive() && enemies[i].isShooting())
            {
                //which peak are they shooting from?
                Vector2f enemyPos = enemies[i].getPosition();
                
                //so, which laser do we want to update?
                for(int j = 0; j < m_NumEnemyLasers; j++)
                {
                    Vector2f laserPos = enemyLasers[j].getPeakPosition();
                    if(laserPos == enemyPos)
                    {
                        int shootDuration = enemies[i].getShootDuration();
                        enemyLasers[j].update(dt, shootDuration);
                    }
                }
            }
            enemies[i].updateD(currentTime, m_mtnArrayDigital);
        }
        
        
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
                if (enemies[j].getJustStoppedShooting() && sun.isAlive())
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
         UPDATE CANON PROJECTILES THAT ARE IN FLIGHT
         Toggle MtnProjectiles if appropriate. The mountain projectile is turned on when the canon's projectile reaches the base of the mountain.
         ****/
        for(int j = 0; j < m_projectileArraySize; j++)
        {
            if(canon0Projectiles[j].isInFlight())
            {
                if (canon0Projectiles[j].isAtTarget())
                {
                    canon0Projectiles[j].stop();
                    mtnProjectiles[0].turnOn();
                }
                else
                {
                    canon0Projectiles[j].update(dt);
                }
            }
            
            if(canon1Projectiles[j].isInFlight())
            {
                if (canon1Projectiles[j].isAtTarget())
                {
                    canon1Projectiles[j].stop();
                    mtnProjectiles[1].turnOn();
                }
                else
                {
                    canon1Projectiles[j].update(dt);
                }
            }
            
            if(canon2Projectiles[j].isInFlight())
            {
                if (canon2Projectiles[j].isAtTarget())
                {
                    canon2Projectiles[j].stop();
                    mtnProjectiles[2].turnOn();
                }
                else
                {
                    canon2Projectiles[j].update(dt);
                }
            }
            
            if(canon3Projectiles[j].isInFlight())
            {
                if (canon3Projectiles[j].isAtTarget())
                {
                    canon3Projectiles[j].stop();
                    mtnProjectiles[3].turnOn();
                }
                else
                {
                    canon3Projectiles[j].update(dt);
                }
            }
            
            if(canon4Projectiles[j].isInFlight())
            {
                if (canon4Projectiles[j].isAtTarget())
                {
                    canon4Projectiles[j].stop();
                    mtnProjectiles[4].turnOn();
                }
                else
                {
                    canon4Projectiles[j].update(dt);
                }
            }
        }
        
        //update mtn projectiles
        for(int i = 0; i < m_numCanons; i++)
        {
            mtnProjectiles[i].update(dt);
        }
        
        /****
         COLLISION DETECTION
         - Have any enemies been shot?
         -- cycle through each enemy for each mtn projectile
         -- if enemy is at the mtn projectile's peak AND mtn projectile is on, toggle enemy !alive and change its sprite to the explode sprite
         // I NEED TO UPDATE ENEMY CLASS TO HANDLE THE EXPLODING
         - Update score and #enemies alive
         - If all enemies dead, change game mode to levellingup
         ****/
         
        for(int i = 0; i < m_numCanons; i++)
        {
            for (int j = 0; j < m_NumEnemies; j++)
            {
                if (mtnProjectiles[i].getOn() && mtnProjectiles[i].isDamaging() && enemies[j].isAlive())
                {
                    if(enemies[j].getPosition() == mtnProjectiles[i].getPeakPosition())
                       {
                           mtnProjectiles[i].stopDamaging(); //if you don't stop it, it keeps hitting enemy
                           
                            if(enemies[j].hit()) //returns true ONLY if enemy is dead
                            {
                                //turn off the enemy's laser
                                Vector2f enemyPos = enemies[j].getPosition();
                                
                                //so, which laser do we want to turn off?
                                for(int k = 0; k < m_NumEnemyLasers; k++)
                                {
                                    Vector2f laserPos = enemyLasers[k].getPeakPosition();
                                    if(laserPos == enemyPos)
                                    {
                                        enemyLasers[k].turnOff();
                                    }
                                }
                                
                                //add score for killing an enemy
                                m_score += 10;
                                m_Hud.setScore(m_score);
                                //decrease m_NumEnemiesAlive
                                m_NumEnemiesAlive--;
                                
                                if(m_NumEnemiesAlive == 0)
                                {
                                    //turn everything off
                                    for (int i = 0; i < m_NumMountains; i++)
                                    {
                                        canon0Projectiles[i].stop();
                                        canon1Projectiles[i].stop();
                                        canon2Projectiles[i].stop();
                                        canon3Projectiles[i].stop();
                                        canon4Projectiles[i].stop();
                                        mtnProjectiles[i].stop();
                                        enemyLasers[i].turnOff();
                                    }
                                    
                                    mode = GameMode::LEVELLING_UP;
                                    
                                }
                                
                            }
                       }
                }
                
            }
        }
        
        /****
         UPDATE UI elements
         ****/
        
        
        /****
         UPDATE THE HUD if it's time
         ****/
        
        
    } //End if Playing
}
