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
#include "Timer.h"

using namespace sf;

void Engine::m_Update()
{
    if(mode == GameMode::PLAYING)
    {
        //declare a clock
        Timer t; //in seconds
        //update the time: t.elapsed() returns time the program has been running in seconds
        m_PlayingTimeElapsed = t.elapsed();
        
        /****
         UPDATE THE ENEMIES
         ****/
        for(int i = 0; i < m_NumEnemies; i++)
        {
            if (enemies[i].isAlive())
            {
                enemies[i].updateD(m_PlayingTimeElapsed, m_mtnArrayDigital);
            }
        }//END updating Enemies
       
        /****
         UPDATE THE ENEMY LASERS
         ****/
        for(int i = 0; i < m_NumEnemyLasers; i++)
        {
            enemyLasers[i].update(enemies, m_NumEnemies, m_mtnArrayDigital, i);
        }

        /****
         UPDATE THE SUN - COLLISION DETECTION BTWN SUN and ENEMY LASERS)
         ****/
        //Normally we might loop through each laser for each sun segment, to check if there's any collision. BUT, in this game the way the sun is affected by lasers differs.
        //The sun has a total life: double m_SunLife. //in 'units' (use double because the Timer object uses a double.
        //Enemy lasers have an effect of draining sunlife at a rate: double m_EnemyLaserEffect; //in 'units per second'
        //So, if enemie lasers have shot the sun for a total of: m_SunLife/m_EnemyLaserEffect seconds, the sun will be completely drained.
        //So we need to create a variable to hold how many seconds the sun has been shot so far: double m_TotalTimeSunHasBeenLasered
        
        //cycle through each laser and if it's just been turned off, add the shootduration time to the total time the sun's been lasered.
        //then, update the sun's remaining life.
        for(int i = 0; i < m_NumEnemyLasers; i++)
        {
            if (enemyLasers[i].justOff() && sun.isAlive())
            {
                int time = enemies[i].getShootDuration();   //NOTE THIS IS CLUMSY AND ERROR PRONE. NEED TO FIX IT. (because I'm grabbing shoot duration from enemies using the same index as the laser, which is incorrect. But currently it doesn't matter since all enemies have the same shoot duration.
                sun.update(time);   //this function toggles m_SunAlive to false when the sun is dead.
            }
        }
        
        
        
        /****
         UPDATE THE CANONS
         ****/
        
        for(int i = 0; i < m_numCanons; i++)
        {
            player[i].update(m_PlayingTimeElapsed);
        }//END updating canons (player)

        /****
         UPDATE THE CANON PROJECTILES
         ****/
        
        
        
    } //End if Playing
    
    if(mode == GameMode::PLAYING)
    {
    }
    
}
