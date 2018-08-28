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

bool Enemy::isAlive(){
    return m_Alive;
}

int Enemy::getPosition(){
    return m_Position;
}

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
void Enemy::spawn(int position, int enemyType, int seed){
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
void Enemy::update(double t, int numMountains){
    
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
