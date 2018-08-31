//
//  EnemyLaser.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 30/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "EnemyLaser.h"
#include "ResourcePath.hpp"
#include "TextureHolder.h"
#include <iostream>

bool EnemyLaser::getOn()
{
    return m_LaserOn;
}
Vector2f EnemyLaser::getPosition()
{
    return m_LaserPosition;
}

Sprite EnemyLaser::getSprite()
{
    return m_LaserSprite;
}

void EnemyLaser::spawn(Vector2f position, int i)
{
    switch(i){
        case 0: // laser 1
            m_LaserSprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Laser1Asset 14.png"));
            break;
        case 1:
            m_LaserSprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Laser2Asset 13.png"));
            break;
        case 2:
            m_LaserSprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Laser3Asset 12.png"));
            break;
        case 3:
            m_LaserSprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Laser4Asset 11.png"));
            break;
        case 4:
            m_LaserSprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Laser5Asset 10.png"));
            break;
    }
    
    m_LaserOn = false;
    m_LaserPosition.x = position.x;
    m_LaserPosition.y = position.y;
    m_LaserSprite.setPosition(m_LaserPosition.x, m_LaserPosition.y);    
}

//Update lasers:
//check to see if each enemy is shooting
//if an enemy is shooting, toggle the laserOn to true.
//Note: in the enemy class we take care of restricting enemies to shoot from only the mountains that align with the canons and laser sprites. So, no need to check the enemy position.
void EnemyLaser::update(Enemy* enemies, int numEnemies, VertexArray& mountainsVA, int index)
{
    //this update function updates ONE laser - the laser at 'index' in the laserarray.
    
    //turn the laser off
    m_LaserOn = false;
    
    //check if there's a shooting enemy at the same peak as this laser
    //if so, turn laser on.
    
    //1. get the position of the peak associated with this laser
    //2. check if any enemy is currently at this peak.
    //3. if so, check if that enemy is shooting
    //4. if so, turn laser on.
    Vector2f mountainPos;
    switch (index)
    {
        case 0: //laser 1
            mountainPos = mountainsVA[3].position; //corresponding peak position
            break;
        case 1: //laser 2
            mountainPos = mountainsVA[5].position;
            break;
        case 2: //laser 3
            mountainPos = mountainsVA[7].position;
            break;
        case 3: //laser 4
            mountainPos = mountainsVA[9].position;
            break;
        case 4: //laser 5
            mountainPos = mountainsVA[10].position;
            break;
    }
    
    for (int i = 0; i < numEnemies; i++)
    {
        if((enemies[i].getPosition() == mountainPos) && (enemies[i].isShooting() == true))
        {
            m_LaserOn = true;
        }
    }
}
