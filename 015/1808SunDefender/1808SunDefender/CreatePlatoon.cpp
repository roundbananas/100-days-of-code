//
//  CreateHorde.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include <iostream>
#include "Enemy.h"
#include "BattleGround.h"
#include <cstdlib>
#include <ctime>

Enemy* createPlatoon(int numEnemies, int numMountains){
    Enemy* enemies = new Enemy[numEnemies];
    
    for (int i = 0; i < numEnemies; i++)
    {
        //which side should the enemy spawn
        srand((int)time(0) * i);
              int side = (rand() % 2 ); //generate random number between 0 and 1
              int position = 0;
        switch(side)
        {
            case 0:
                position = 1;
                break;
            case 1:
                position = numMountains;
                break;
        }
    
        //Normal, Strong or Super type of enemy
        int enemyType = (rand() % 3 );
        
        //spawn enemy into the array
        enemies[i].spawn(position, enemyType, i);   //generate random number between 0 and 2

    }
    return enemies;
}
