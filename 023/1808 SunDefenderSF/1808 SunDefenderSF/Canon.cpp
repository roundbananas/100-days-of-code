//
//  Canon.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Canon.h"
#include "TextureHolder.h"
#include "ResourcePath.hpp"

Sprite Canon::getSprite()
{
    return m_Sprite;
}

Vector2f Canon::getPosition()
{
    return m_Position;
}

int Canon::getType()
{
    return m_CanonType;
}

bool Canon::getCharged()
{
    return m_isCharged;
}

void Canon::fireCanon()
{
    m_JustFired = true;
    m_isCharged = false;
}

void Canon::spawn(Vector2f position, int canonType, int seed)
{
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Canon.png"));
    
    //What type can it be
    m_CanonType = canonType;
    switch (m_CanonType)
    {
        case 0: //normal
            m_RechargeTime = NORMAL_RECHARGE;
            break;
        case 1:  //rapid
            m_RechargeTime = RAPID_RECHARGE;
            break;
    }
    
    m_LastFiredTime = 0;
    m_JustFired = false;
    m_isCharged = true;
    
    m_Position.x = position.x;
    m_Position.y = position.y;
    m_Sprite.setPosition(m_Position.x, m_Position.y);
}//END SPAWN

void Canon::powerUp(){}         //handle canon getting powerup

void Canon::update(double currentTime)
{
    if(!m_isCharged)
    {
        //check if it is now charged
        if((currentTime - m_LastFiredTime) > m_RechargeTime)
        {
            m_isCharged = true;
        }
    }
    
    if(m_isCharged)
    {
        //check if it's fired
        if(m_JustFired)
        {
            m_LastFiredTime = currentTime;
            m_isCharged = false;
        }
    }
}