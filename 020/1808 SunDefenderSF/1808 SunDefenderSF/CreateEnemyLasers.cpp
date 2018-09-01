//
//  CreateEnemyLasers.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 30/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "EnemyLaser.h"
#include "BattleGround.h"
#include "Engine.h"

EnemyLaser* createEnemyLasers(VertexArray& laserVA)
{
    /*******
     CREATE LASER POSITIONS
     *******/
    //What type of primitive are we using?
    laserVA.setPrimitiveType(Points);
    const int VERTS_IN_POINT = 2;
    
    //Set size of vertex array
    laserVA.resize(5 * VERTS_IN_POINT); //5 = number of lasers
    
    //initialise vertex array. Doing this manually because in physical game the mountains are fixed
    //vector coords taken from Adobe illustrator
    float posTweakX = -5;
    float posTweakY = -80;
    laserVA[0].position = Vector2f(288+posTweakX, 200+posTweakY);
    laserVA[1].position = Vector2f(473+posTweakX, 235+posTweakY);
    laserVA[2].position = Vector2f(575+posTweakX, 215+posTweakY);
    laserVA[3].position = Vector2f(615+posTweakX, 180+posTweakY);
    laserVA[4].position = Vector2f(625+posTweakX, 140+posTweakY);
    
    /*******
     CREATE LASERS
     *******/
    EnemyLaser* enemyLasers = new EnemyLaser[5]; //5=number of lasers
    
    for (int i = 0; i < 5 ; i++)
    {
        Vector2f vPos;
        vPos.x = laserVA[i].position.x;
        vPos.y = laserVA[i].position.y;
        
        enemyLasers[i].spawn(vPos, i);
    }
    return enemyLasers;
}

/*
 HOW TO:
 engine.h - declare VertexArray m_EnemyLaserArray
Engine.cpp - pass m_EnemyLaserArray to enemyLasers = CreateEnemyLasers.cpp, by reference
 CreateEnemyLasers.cpp
 - create the vertex array for laser positions
 - declare laser array using new keyword
 - position and spawn each laser, by passing a intermediary position variable to the spawn function
 

*/
