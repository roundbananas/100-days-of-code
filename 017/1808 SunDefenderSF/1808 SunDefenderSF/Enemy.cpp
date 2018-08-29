//
//  Enemy.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
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

int Enemy::getPosition(){
    return m_Position;
}

/*
void setPosition(Vector2f pos)
{
    m_VPosition.x = pos.x;
    m_VPosition.y = pos.y;
}
*/

int* Enemy::getColour(){
    return m_Colour;
}

int Enemy::getLinger(){
    return m_LingerTime;
}

int Enemy::getType(){
    return m_type;
}

//Maniuplation functions
void Enemy::spawnP(int position, int enemyType, int seed){
    switch(enemyType){
        case 0: // normal
            m_Health = NORMAL_HEALTH;
            m_LingerTime = NORMAL_LINGER;
            m_Colour[0] = NORMAL_COLOURR;
            m_Colour[1] = NORMAL_COLOURG;
            m_Colour[2] = NORMAL_COLOURB;
            m_type = 1;
            break;
        case 1:
            m_Health = STRONG_HEALTH;
            m_LingerTime = STRONG_LINGER;
            m_Colour[0] = STRONG_COLOURR;
            m_Colour[1] = STRONG_COLOURG;
            m_Colour[2] = STRONG_COLOURB;
            m_type = 2;
            break;
        case 2:
            m_Health = SUPER_HEALTH;
            m_LingerTime = SUPER_LINGER;
            m_Colour[0] = SUPER_COLOURR;
            m_Colour[1] = SUPER_COLOURG;
            m_Colour[2] = SUPER_COLOURB;
            m_type = 3;
            break;
    }
    
    m_Position = position;
    
    m_lastUpdate = 0;
    
    m_Alive = true;
    m_Shooting = false;

}

void Enemy::spawnD(Vector2f vPosition, int enemyType, int seed)
{
    switch(enemyType){
        case 0: // normal
            m_Health = NORMAL_HEALTH;
            m_LingerTime = NORMAL_LINGER;
            m_Colour[0] = NORMAL_COLOURR;
            m_Colour[1] = NORMAL_COLOURG;
            m_Colour[2] = NORMAL_COLOURB;
            m_type = 1;
            break;
        case 1:
            m_Health = STRONG_HEALTH;
            m_LingerTime = STRONG_LINGER;
            m_Colour[0] = STRONG_COLOURR;
            m_Colour[1] = STRONG_COLOURG;
            m_Colour[2] = STRONG_COLOURB;
            m_type = 2;
            break;
        case 2:
            m_Health = SUPER_HEALTH;
            m_LingerTime = SUPER_LINGER;
            m_Colour[0] = SUPER_COLOURR;
            m_Colour[1] = SUPER_COLOURG;
            m_Colour[2] = SUPER_COLOURB;
            m_type = 3;
            break;
    }
    
    m_lastUpdate = 0;
    m_Alive = true;
    m_Shooting = false;
    
    m_EnemySprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Enemy.png"));
    
    m_VPosition.x = vPosition.x;
    m_VPosition.y = vPosition.y;
    m_EnemySprite.setPosition(m_VPosition);
}

bool Enemy::hit(){
    m_Health--;
    
    if(m_Health < 0){
        //dead
        m_Alive = false;
        //how to handle explosion/death?
    }
    return false;
}

//update function also needs to know how many peaks
//enemy can go between, so if they get to one side, they come back. Assuming they move only to an adjacent peak.
//Does update also need to know which peaks are currently occupied?
void Enemy::updateP(double t, int numMountains){
    
    m_Position = m_Position + 0;
    
    if (t - m_lastUpdate > m_LingerTime)
    {
        if (m_Position == 0)
        m_Position += 1;    //for now let's just move the enemy across the screen
        else if (m_Position == numMountains)
            m_Position -= 1;
        else        //random left or right
        {
            srand((int)time(0) * t);   //seed random number generator with current position
            int direction = (rand() % 2 ); //generate random number between 0 and 1
            switch (direction)
            {
                case 0:
                    m_Position += 1;
                    break;
                case 1:
                    m_Position -= 1;
                    break;

            }
        }
    }
    
    m_lastUpdate = t;
}

void Enemy::updateD(double t, sf::Vertex *m_mtnArrayDigital)
{
    //if we're due to move, work out where to move
    if (t - m_lastUpdate > m_LingerTime)
    {
        //if we're on left-most mtn, move right
        if (m_VPosition == m_mtnArrayDigital[0].position)
        {
            m_VPosition = m_mtnArrayDigital[1].position;
        }
        //if we're on right-most mtn, move left
        else if (m_VPosition == m_mtnArrayDigital[12].position)
        {
            m_VPosition = m_mtnArrayDigital[11].position;
        }
        else
        {
            //if we're somewhere in middle of mtn range,
            //first work out where we are by identifying the mtn's
            //index in the mtn array.
            int index;
            for (int i = 0; i < sizeof(m_mtnArrayDigital); i++)
            {
                if (m_mtnArrayDigital[i].position == m_VPosition)
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
            m_VPosition = m_mtnArrayDigital[index].position;
        }//end else
    }//end if we're due to move
}
