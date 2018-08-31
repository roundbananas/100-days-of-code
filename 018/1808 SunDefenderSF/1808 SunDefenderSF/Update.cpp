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
        }
        for(int i = 0; i < m_NumEnemies; i++)
        {
            std::cout << "\nEnemyPosition: " << enemies[i].getPositionX();
            std::cout << " - " <<
            enemies[i].getPositionY();
            std::cout << "\nType: " << enemies[i].getType();
            std::cout << " \n";
        }
        
        
        
        /****
         UPDATE THE CANONS
         ****/
        
        for(int i = 0; i < m_numCanons; i++)
        {
            player[i].update(currentTime);
        }
    /*    for(int i = 0; i < m_numCanons; i++)
        {
            std::cout << "\nPlayerPosition: " << player[i].getPosition();
            std::cout << "\nType: " << player[i].getType();
            std::cout << "\nisCharged?: " << player[i].getCharged();
            std::cout << " \n";
        }
      */
    } //End if Playing
}
