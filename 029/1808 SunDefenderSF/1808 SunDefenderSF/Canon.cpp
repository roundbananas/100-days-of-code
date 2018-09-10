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

void Canon::fireCanon(double t)
{
    if(m_isCharged)
    {
    m_LastFiredTime = t;
    m_JustFired = true;
    m_isCharged = false;
    }
}

double Canon::getLastFired()
{
    return m_LastFiredTime;
}

int Canon::getFireRate()
{
    switch (m_CanonType)
    {
        case 0: //normal
            m_FireRate = NORMAL_FIRERATE;
            break;
        case 1:
            m_FireRate = RAPID_FIRERATE;
            break;
    }
    
    return m_FireRate;
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
            m_FireRate = NORMAL_FIRERATE;
            break;
        case 1:  //rapid
            m_RechargeTime = RAPID_RECHARGE;
            m_FireRate = RAPID_FIRERATE;
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
        //check if it's fired
        if(m_JustFired)
        {
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "CanonPushed.png"));
            m_Sprite.setPosition(m_Position.x, m_Position.y);
            
            if((currentTime - m_LastFiredTime) > 0.4) //0.4 second button push
            {
                m_JustFired = false;
                m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "CanonCharging.png"));
                m_Sprite.setPosition(m_Position.x, m_Position.y);
                
            }
        }
        //check if it is now charged
        if((currentTime - m_LastFiredTime) > m_RechargeTime)
        {
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Canon.png"));
            m_Sprite.setPosition(m_Position.x, m_Position.y);
            m_isCharged = true;
        }
        
    
        
    }
}
