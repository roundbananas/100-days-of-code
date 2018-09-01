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
         UPDATE THE SUN (COLLISION DETECTION WITH ENEMY LASERS)
         ****/
        //loop through each laser for each sun segment
        for(int i = 0; i < m_NumEnemyLasers; i++)
        {
            //to be continued
            break;
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
