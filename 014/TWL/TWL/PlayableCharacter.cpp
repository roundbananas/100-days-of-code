//
//  PlayableCharacter.cpp
//  TWL
//
//  Created by Carl Turner on 26/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include "PlayableCharacter.h"

void PlayableCharacter::spawn(sf::Vector2f startPosition, float gravity)
{
    //place player at starting point
    m_Position.x = startPosition.x;
    m_Position.y = startPosition.y;
    
    //initialise gravity
    m_Gravity = gravity;
    
    //move sprite to position
    m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::update(float elapsedTime)
{
    if (m_RightPressed)
    {
        m_Position.x += m_Speed*elapsedTime;
    }
    if (m_LeftPressed)
    {
        m_Position.x -= m_Speed*elapsedTime;
    }
    
    if (m_IsJumping)
    {
        //update how long the jump has been going
        m_TimeThisJump += elapsedTime;
        
        //is jump going up?
        if(m_TimeThisJump < m_Jumpduration)
        {
            //move up at twice gravity
            m_Position.y -= m_Gravity * 2 * elapsedTime;
        }
        else
        {
            m_IsJumping = false;
            m_IsFalling = true;
        }
    }
    
    //Apply gravity
    if (m_IsFalling)
    {
        m_Position.y += m_Gravity * elapsedTime;
    }
    
    //Update rect for all body parts
    FloatRect r = getPosition();
    
    //Character graphic has dimensions:
    //Body: 6px wide x 
    //
    
    //Feet
    m_Feet.left = r.left + 3;
    m_Feet.top = r.top + r.height - 1;
    m_Feet.width = r.width - 6;
    m_Feet.height = 1;
    
    //Head
    m_Head.left = r.left;
    m_Head.top = r.top + (r.height * 0.3); //should this be -, not +?
    m_Head.width = r.width;
    m_Head.height = 1;
    
    //Right
    m_Right.left = r.left + r.width;
    m_Right.top = r.top + (r.height * 0.35); //Inconsistent with m_Left.width
    m_Right.width = 1; //this extends beyond character sprite. Inconsistent with m_Left.width
    m_Right.height = r.height * 0.3;
    
    //Left
    m_Left.left = r.left;
    m_Left.top = r.top + (r.height * 0.5); //Inconsistent with m_Right.width
    m_Left.width = 1; //this is contained within character sprite. Inconsistent with m_Right.width
    m_Left.height = r.height * 0.3;
    
    //Move sprite into position
    m_Sprite.setPosition(m_Position);
}

FloatRect PlayableCharacter::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::getCenter() //this also handles different sizes of the characters, by referring to their sprite dimensions
{
    return Vector2f(
    m_Position.x + m_Sprite.getGlobalBounds().width /2,
    m_Position.y + m_Sprite.getGlobalBounds().height/2);
}

FloatRect PlayableCharacter::getFeet()
{
    return m_Feet;
}

FloatRect PlayableCharacter::getHead()
{
    return m_Head;
}

FloatRect PlayableCharacter::getLeft()
{
    return m_Left;
}

FloatRect PlayableCharacter::getRight()
{
    return m_Right;
}

Sprite PlayableCharacter::getSprite()
{
    return m_Sprite;
}

void PlayableCharacter::stopFalling(float position)
{
    m_Position.y = position - getPosition().height;
    m_Sprite.setPosition(m_Position);
    m_IsFalling = false;
}

void PlayableCharacter::stopRight(float position)
{
    m_Position.x = position - m_Sprite.getGlobalBounds().width;
    m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopLeft(float position)
{
    m_Position.x = position + m_Sprite.getGlobalBounds().width;
    m_Sprite.setPosition(m_Position);
}

