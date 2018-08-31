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

void Engine::m_Update(double currentTime)
{
    if (m_Playing)
    {
        /****
         UPDATE THE ENEMIES
         ****/
    
        // std::cout << "\nTime: " << current_time;
        for(int i = 0; i < m_NumEnemies; i++)
        //    if (enemies[i].isAlive())
        {
           // enemies[i].updateP(currentTime, m_NumMountains);
            enemies[i].updateD(currentTime, m_mtnArrayDigital);
          
            /****
             UPDATE THE LASERS
             ****/
            for(int i = 0; i < m_NumEnemyLasers; i++)
            {
                enemyLasers[i].update(enemies, m_NumEnemies, m_mtnArrayDigital, i);
            }
        }

        /****
         UPDATE THE CANONS
         ****/
        
        for(int i = 0; i < m_numCanons; i++)
        {
            player[i].update(currentTime);
        }

    } //End if Playing
}
