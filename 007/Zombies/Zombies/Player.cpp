//
//  Player.cpp
//  Zombies
//
//  Created by Carl Turner on 18/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include <cmath>
#include "ResourcePath.hpp"
#include "Player.h"

//constructor
Player::Player()
{
    //initialise constants
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
    
    //associate texture with sprite
    m_Texture.loadFromFile(resourcePath() + "player.png");
    m_Sprite.setTexture(m_Texture);
    
    //Set origin of sprite to the centre for smooth rotn
    m_Sprite.setOrigin(25,25);
}

//Spawn the player into each level
void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
    //Place player in middle of arena
    m_Position.x = arena.width/2;
    m_Position.y = arena.height/2;
    
    //copy details of the arena to player's m_Arena
    m_Arena.left = arena.left;
    m_Arena.width = arena.width;
    m_Arena.top = arena.top;
    m_Arena.height = arena.height;
    
    //Remember how big the tiles are in this arena
    m_TileSize = tileSize;
    
    //Store the resolution for future use
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
    return m_LastHit;
}

bool Player::hit(Time timeHit)
{
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) //health only deducted up to 5 times per second. Makes the game playable.
    {
        m_LastHit = timeHit;
        m_Health -= 10;
        return true;
    }
    else
    {
        return false;
    }
}

//The following get values from Player
FloatRect Player::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
    return m_Position;
}

float Player::getRotation()
{
    return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
    return m_Sprite;
}

int Player::getHealth()
{
    return m_Health;
}

//the following can be called from main() to change data contained in Player object
void Player::moveLeft()
{
    m_LeftPressed = true;
}

void Player::moveRight()
{
    m_RightPressed = true;
}

void Player::moveUp()
{
    m_UpPressed = true;
}

void Player::moveDown()
{
    m_DownPressed = true;
}

void Player::stopLeft()
{
    m_LeftPressed = false;
}

void Player::stopRight()
{
    m_RightPressed = false;
}

void Player::stopUp()
{
    m_UpPressed = false;
}

void Player::stopDown()
{
    m_DownPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
    if (m_UpPressed)
    {
        m_Position.y -= m_Speed * elapsedTime; //minus because screen is measured from top to bottom, so this will move player UP the screen.
    }
    
    if (m_DownPressed)
    {
        m_Position.y += m_Speed * elapsedTime;
    }
    
    if (m_RightPressed)
    {
        m_Position.x += m_Speed * elapsedTime;
    }
    
    if (m_LeftPressed)
    {
        m_Position.x -= m_Speed * elapsedTime;
    }
    
    m_Sprite.setPosition(m_Position);


    //Keep the player in the arena
    //Remember confines of the arena are stored in m_Arena, by the spawn function
    if (m_Position.x > m_Arena.width - m_TileSize)
    {
        m_Position.x = m_Arena.width - m_TileSize;
    }
    
    if (m_Position.x < m_Arena.left + m_TileSize)
    {
        m_Position.x = m_Arena.left + m_TileSize;
    }
    
    if (m_Position.y > m_Arena.height - m_TileSize)
    {
        m_Position.x = m_Arena.height - m_TileSize;
    }
    
    if (m_Position.y < m_Arena.top + m_TileSize)
    {
        m_Position.y = m_Arena.top + m_TileSize;
    }
    
    //Calculate angle player is facing
    //requires cmath.h header
    //Compute arc tangent with two parameters
    //atan(a, b) returns radians. rads*180/pi = degrees.
    //This calculation is relative to centre of the screen, where the player is. Player always stays in centre of screen, while the background moves.
    float angle = (atan2(mousePosition.y - m_Resolution.y/2, mousePosition.x - m_Resolution.x/2) * 180)/3.141;
    
    m_Sprite.setRotation(angle);
}

void Player::updgradeSpeed()
{
    //20% speed upgrade
    m_Speed += (START_SPEED * 0.2);
}

void Player::upgradeHealth()
{
    //20% max health upgrade
    m_MaxHealth += (START_HEALTH * 0.2);
}

void Player::increaseHealthLevel(int amount)
{
    m_Health += amount;
    
    //but not beyond the max
    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }
}

