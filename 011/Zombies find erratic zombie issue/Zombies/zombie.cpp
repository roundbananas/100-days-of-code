//
//  zombie.cpp
//  Zombies
//
//  Created by Carl Turner on 21/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>
#include "ResourcePath.hpp"
#include <cmath>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed)
{
    //we use static TextureHolder GetTexture() function to assign the texture. This means there'll be a maximum of 3 textures loaded into the GPU, regardless of how many zombies there are.
    switch(type)
    {
        case 0: //Bloater
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath()+ "bloater.png"));
            m_Speed = 40;
            m_Health = 5;
            break;
        
        case 1: //chaser
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath()+ "chaser.png"));
            m_Speed = 80;
            m_Health = 1;
            break;
            
        case 2: //crawler
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath()+ "crawler.png"));
            m_Speed = 20;
            m_Health = 3;
            break;
    }
 
    //Modify the speed to make zombie unique
    
    //Create a speed modifier
    srand((int)time(0) * seed);
    //somewhere between 80 and 100
    float modifier = (rand()%MAX_VARIANCE) + OFFSET; //the result is a value between 0 and 1
    
    //express as a fraction of 1
    modifier /= 100; //now equals between .7 and 1
    m_Speed *= modifier;
  
    //initialise its location
    m_Position.x = startX;
    m_Position.y = startY;
    
    
    
    
    
    
    
    
    
    
    m_Alive = true; //this line was missing
    
    
    
    
    
    
    
    
    
    
    
    
    //set its origin to it's center
    m_Sprite.setOrigin(25, 25);
    
    //set its position
    m_Sprite.setPosition(m_Position);
}
    
bool Zombie::hit()
{
    m_Health--;
    
    if(m_Health < 0)
    {
        //dead
        m_Alive = false;
        m_Sprite.setTexture(TextureHolder::GetTexture(resourcePath() + "blood.png"));
        
        return true;
    }
    //injured but not dead yet
    return false;
}

bool Zombie::isAlive()
{
    return m_Alive;
}

FloatRect Zombie::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Sprite Zombie::getSprite()
{
    return m_Sprite;
}

//FOR MY DEBUGGING
int Zombie::getSpeed()
{
    return m_Speed;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;
    
    //update zombie position
    if (playerX > m_Position.x)
    {
        m_Position.x = m_Position.x + m_Speed * elapsedTime;
    }
    if (playerY > m_Position.y)
    {
        m_Position.y = m_Position.y + m_Speed * elapsedTime;
    }
    if (playerX < m_Position.x)
    {
        m_Position.x = m_Position.x - m_Speed * elapsedTime;
    }
    if (playerY < m_Position.y)
    {
        m_Position.y = m_Position.y - m_Speed * elapsedTime;
    }
    
    //move the sprite
    m_Sprite.setPosition(m_Position);
    
    //face the sprite in correct direction
    float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180)/3.141;
    
    m_Sprite.setRotation(angle);
}

