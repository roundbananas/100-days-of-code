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
#include "Engine.h"
#include <cstdlib>
#include <ctime>

//with this function we create both the platoon and the mountain range.
//can do this because we're passing the m_mtnArrayDigital by reference, so the actual variable will be updated.
Enemy* createPlatoon(int level, int numEnemies, int numMountains, VertexArray& mountainsVA, int lifeLostPerHit)
{
    /*******
    CREATE MOUNTAIN RANGE
    *******/
    //What type of primitive are we using?
    mountainsVA.setPrimitiveType(Points);
    const int VERTS_IN_POINT = 2;
    
    //Set size of vertex array
    mountainsVA.resize(numMountains * VERTS_IN_POINT);
    
    //initialise vertex array. Doing this manually because in physical game the mountains are fixed
    float posTweakX = 0;
    float posTweakY = 0;
    mountainsVA[0].position = Vector2f(45+posTweakX, 400+posTweakY);
    mountainsVA[1].position = Vector2f(125+posTweakX, 300+posTweakY);
    mountainsVA[2].position = Vector2f(190+posTweakX, 400+posTweakY);
    mountainsVA[3].position = Vector2f(275+posTweakX, 350+posTweakY);
    mountainsVA[4].position = Vector2f(355+posTweakX, 400+posTweakY);
    mountainsVA[5].position = Vector2f(460+posTweakX, 275+posTweakY);
    mountainsVA[6].position = Vector2f(530+posTweakX, 350+posTweakY);
    mountainsVA[7].position = Vector2f(610+posTweakX, 300+posTweakY);
    mountainsVA[8].position = Vector2f(700+posTweakX, 400+posTweakY);
    mountainsVA[9].position = Vector2f(745+posTweakX, 325+posTweakY);
    mountainsVA[10].position = Vector2f(855+posTweakX, 275+posTweakY);
    mountainsVA[11].position = Vector2f(900+posTweakX, 325+posTweakY);
    mountainsVA[12].position = Vector2f(960+posTweakX, 350+posTweakY);
    
    /*******
     CREATE ENEMIES ON THE MOUNTAIN RANGE
     *******/
    Enemy* enemies = new Enemy[numEnemies];
    
    for (int i = 0; i < numEnemies; i++)
    {
    /* Initially I attempted to spawn enemies only on either side of the range. But this meant many of them overlapped and weren't actually visible, despite setting different movement speeds. So I'll try spawning them at any place on the mountain).
     */
        //Where on the should the enemy spawn
        srand((int)time(0) * i);
              int peak = (rand() % numMountains ); //generate random number between 0 and 12, assuming numMountains = 13.
            Vector2f vPos;
        
        for (int k = 0; k < numMountains; k++)
        {
            if (peak == k)
            {
                vPos.x = mountainsVA[peak].position.x;
                vPos.y = mountainsVA[peak].position.y;
            }
        }
        
        //Normal, Strong or Super type of enemy
        int enemyType;
        if(level < 3) //spawn only normal enemies for first 2 levels
        {
            enemyType = 0;
        }
        else if (level < 5) //spawn either normal or strong enemies in levels 3 and 4
        {
            enemyType = (rand() % 2 );
        }
        else //from level 5 spawn normal, strong and super types of enemies
        {
            enemyType = (rand() % 3 );
        }
        int damagePerHit = lifeLostPerHit;
        std::cout << "\nDamage per hit: " << damagePerHit;

        //spawn enemy into the array
       // enemies[i].spawnP(position, enemyType, i);   //generate random number between 0 and 2
        enemies[i].spawnD(vPos, enemyType, i, damagePerHit); //for digital version
    }
    return enemies;
}


