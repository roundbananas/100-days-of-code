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

int Canon::getPosition()
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

void Canon::spawn(int position, int canonType, int seed)
{
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Canon.png"));
    
    m_Position = position;
    
    //set position of button on screen for digital version. They don't move.
    switch(m_Position)
    {
        case 0:
            m_VPosition.x = 90; //these numbers taken from my illustrator graphic file coords.
            m_VPosition.y = 1055;
            break;
        case 1:
            m_VPosition.x = 290; //these numbers taken from my illustrator graphic file coords.
            m_VPosition.y = 1055;
            break;
        case 2:
            m_VPosition.x = 465; //these numbers taken from my illustrator graphic file coords.
            m_VPosition.y = 1055;
            break;
        case 3:
            m_VPosition.x = 640; //these numbers taken from my illustrator graphic file coords.
            m_VPosition.y = 1055;
            break;
        case 4:
            m_VPosition.x = 830; //these numbers taken from my illustrator graphic file coords.
            m_VPosition.y = 1055;
            break;
    }
    
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
    
    m_Sprite.setPosition(m_VPosition.x, m_VPosition.y);
}
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
