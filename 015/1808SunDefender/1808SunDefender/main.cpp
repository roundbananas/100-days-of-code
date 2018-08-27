//
//  main.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//


#include <iostream>
#include <ctime>
#include "BattleGround.h"
#include "Timer.h"

int main() {
    Timer t; //in seconds
    //Engine.cpp
    Enemy* enemies = nullptr; //pointer to a class
    delete[] enemies;         //delete any existing instance
    int numEnemies = 2;
    int numMountains = 25;
    enemies = createPlatoon(numEnemies, numMountains);
    
    while (true)
    {
        double current_time = t.elapsed();
     
       // std::cout << "\nTime: " << current_time;
        for(int i = 0; i < numEnemies; i++)
        //    if (enemies[i].isAlive())
           {
                enemies[i].update(current_time, numMountains);
           }
        for(int i = 0; i < numEnemies; i++)
        {
            std::cout << "\nPosition: " << enemies[i].getPosition();
            std::cout << "\nType: " << enemies[i].getType();
            std::cout << " \n";
        }
    }
    return 0;
}
