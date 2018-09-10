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

void EnemyLaser::turnOff()
{
    m_LaserOn = false;
}

Vector2f EnemyLaser::getSpritePosition()
{
    return m_LaserSpritePosition;
}

Vector2f EnemyLaser::getPeakPosition()
{
    return m_LaserPeakPosition;
}

Sprite EnemyLaser::getSprite()
{
    return m_LaserSprite;
}

void EnemyLaser::spawn(Vector2f spritePosition, Vector2f peakPosition, int i)
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
    m_timeLaserHasBeenOn = 0;
    m_LaserSpritePosition.x = spritePosition.x;
    m_LaserSpritePosition.y = spritePosition.y;
    m_LaserSprite.setPosition(m_LaserSpritePosition.x, m_LaserSpritePosition.y);
    
    m_LaserPeakPosition.x = peakPosition.x;
    m_LaserPeakPosition.y = peakPosition.y;
}

//Update lasers:
//check to see if each enemy is shooting
//if an enemy is shooting, toggle the laserOn to true.
//Note: in the enemy class we take care of restricting enemies to shoot from only the mountains that align with the canons and laser sprites. So, no need to check the enemy position.
void EnemyLaser::update(double dt, int shootDuration)
{
    //this update function updates ONE laser - the laser at 'index' in the laserarray.
    //This function only gets called if an enemy is on a peak that has a laser
    
    m_LaserOn = true;
 
        //increment time
        m_timeLaserHasBeenOn += dt;

        if(m_timeLaserHasBeenOn > shootDuration)
        {
            m_LaserOn = false;
        }
}
