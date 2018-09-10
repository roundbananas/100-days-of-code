//
//  Enemy.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include <iostream>
#include "Enemy.h"
#include <cstdlib>
#include <ctime>

#include "ResourcePath.hpp"
#include "TextureHolder.h"

Sprite Enemy::getSprite()
{
    return m_EnemySprite;
}


bool Enemy::isAlive(){
    return m_Alive;
}

 bool Enemy::isShooting()
{
    return m_Shooting;
}

double Enemy::getShootDuration()
{
    return m_ShootDuration;
}

bool Enemy::getJustStoppedShooting()
{
    return m_JustStoppedShooting;
}

float Enemy::getPositionX(){
    return m_VPosition.x;
}

float Enemy::getPositionY(){
    return m_VPosition.y;
}

Vector2f Enemy::getPosition()
{
    return m_VPosition;
}

double Enemy::getLinger(){
    return m_LingerTime;
}

int Enemy::getType(){
    return m_type;
}

//Maniuplation functions


void Enemy::spawnD(Vector2f pos, int enemyType, int seed)
{
    switch(enemyType){
        case 0: // normal
            m_Health = NORMAL_HEALTH;
            m_LingerTime = NORMAL_LINGER;
            m_type = 1;
            m_EnemySprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Enemy1.png"));
            break;
        case 1:
            m_Health = STRONG_HEALTH;
            m_LingerTime = STRONG_LINGER;
            m_type = 2;
            m_EnemySprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Enemy2.png"));
            break;
        case 2:
            m_Health = SUPER_HEALTH;
            m_LingerTime = SUPER_LINGER;
            m_type = 3;
            m_EnemySprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Enemy3.png"));
            break;
    }
    std::cout << "\nEnemy Health Spawned: " << m_Health;

    m_lastMoveUpdate = 0;
    m_lastShootUpdate = 0;
    m_lastAliveUpate = 0;
    
    m_LifeLostPerHit = 5;
    
    m_Alive = true;
    m_Shooting = false;
    m_JustStoppedShooting = false;
    
    m_VPosition.x = pos.x;
    m_VPosition.y = pos.y;
    m_EnemySprite.setOrigin(8, 52); //set origin to bottom and middle of sprite.
    m_EnemySprite.setPosition(m_VPosition.x, m_VPosition.y);
}

bool Enemy::hit(){
    std::cout << "\nEnemy Health before: " << m_Health;
    m_Health = m_Health - m_LifeLostPerHit;
    std::cout << "\nEnemy Health after: " << m_Health;

    if(m_Health <= 0){
        //dead
        m_Alive = false;
        switch (m_type)
        {
            case 1: //normal enemy
                m_EnemySprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Enemy1Explode.png"));
                break;
            case 2:
                m_EnemySprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Enemy2Explode.png"));
                break;
            case 3:
                m_EnemySprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Enemy3Explode.png"));
                break;
        }
        
        m_EnemySprite.setOrigin(32, 64); //set origin to bottom and middle of sprite.
        return true; //returns true if enemy is dead
    }
    return false; //returns false if enemy is still alive
}

//update function also needs to know how many peaks
//enemy can go between, so if they get to one side, they come back. Assuming they move only to an adjacent peak.
//Does update also need to know which peaks are currently occupied?


void Enemy::updateD(double t, VertexArray& mountainsVA)
{
    if(m_Alive)
    {
        //if we're due to move, work out where to move
        if (!m_Shooting && ((t - m_lastMoveUpdate) >= m_LingerTime))
        {
            //if we're on left-most mtn, move right
            if (m_VPosition == mountainsVA[0].position)
            {
                m_VPosition = mountainsVA[1].position;
                m_EnemySprite.setPosition(m_VPosition.x, m_VPosition.y);
            }
            //if we're on right-most mtn, move left
            else if (m_VPosition == mountainsVA[12].position)
            {
                m_VPosition = mountainsVA[11].position;
                m_EnemySprite.setPosition(m_VPosition.x, m_VPosition.y);
            }
            else
            {
                //if we're somewhere in middle of mtn range,
                //first work out where we are by identifying the mtn's
                //index in the mtn array.
                int index;
                for (int i = 0; i < sizeof(mountainsVA); i++)
                {
                    if (mountainsVA[i].position == m_VPosition)
                    {
                        index = i;
                        break;
                    }
                }
                //move left or right, randomly
                srand((int)time(0) * t);   //seed random number generator with current position
                int direction = (rand() % 2 ); //generate random number between 0 and 1
                switch (direction)
                {
                    case 0:
                        index += 1;
                        break;
                    case 1:
                        index -= 1;
                        break;
                }
                m_VPosition = mountainsVA[index].position;
                m_EnemySprite.setPosition(m_VPosition.x, m_VPosition.y);
            }//end else
            m_lastMoveUpdate = t;
        }//end if we're due to move
        
        //randomly toggle this enemy to shooting mode. ONLY if they're at one of the peaks that aligns with a canon.
        else if (!m_Shooting && (m_VPosition == mountainsVA[3].position || m_VPosition == mountainsVA[5].position || m_VPosition == mountainsVA[7].position || m_VPosition == mountainsVA[9].position || m_VPosition == mountainsVA[10].position))
        {
            srand((int)time(0) * t);   //seed random number generator with current position
            int random = (rand() % 2 ); //generate random number between 0 and 1
            switch (random)
            {
                case 0:
                    m_Shooting = true;
                    m_lastShootUpdate = t;
                    break;
                case 1:
                    m_Shooting = false;
                    break;
            }
        } //end toggling to shooting
        
        //if we've been shooting for 2 seconds, then stop shooting
        //update the laser to have just turned off (so we can update the sun)
        if(m_Shooting && ((t - m_lastShootUpdate) >= 2))
        {
            m_Shooting = false;
            m_JustStoppedShooting = true;
            m_lastShootUpdate = t;

        }// end if shooting
        m_lastAliveUpate = t;
    }//end ifAlive()
    else //not alive
    {
        //if time since death is less than 0.5 second
        //set position of sprite to last position
        if((t - m_lastAliveUpate) > 0.5)
        {
            m_EnemySprite.setPosition(3000, 3000);
        }
        //
        else
        {
            m_EnemySprite.setPosition(m_VPosition.x, m_VPosition.y);
        }
    }
}
