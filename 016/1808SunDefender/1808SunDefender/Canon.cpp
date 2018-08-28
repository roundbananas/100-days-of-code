//
//  Canon.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Canon.h"

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
    m_Position = position;
    
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
