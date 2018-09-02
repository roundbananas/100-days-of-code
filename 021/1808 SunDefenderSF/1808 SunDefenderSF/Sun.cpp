//
//  Sun.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 29/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "ResourcePath.hpp"
#include "TextureHolder.h"
#include "SunSegment.h"


SunSegment::SunSegment()
{
    m_SunSprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Sun-full.png"));
    m_SegmentAlive = true;
}

void SunSegment::spawn(Vector2f position)
{
    m_Position.x = position.x;
    m_Position.y = position.y;
    m_SunSprite.setPosition(m_Position);
}

Sprite SunSegment::getSprite()
{
    return m_SunSprite;
}

double SunSegment::getTotalLife()
{
    return m_SunLife;
}
double SunSegment::getTimeLasered()
{
    return m_TotalTimeSunHasBeenLasered;
}
double SunSegment::getLaserEffect()
{
    return m_EnemyLaserEffect;
}

double SunSegment::getLifeRemaining()
{
    return m_SunLifeRemaining;
}

void SunSegment::update(int timeToAdd)
{
    m_TotalTimeSunHasBeenLasered += timeToAdd;
    m_SunLifeRemaining = m_TotalTimeSunHasBeenLasered * m_SunLife/m_EnemyLaserEffect;
    
    if (m_SunLifeRemaining < 0)
    {
        m_SegmentAlive = false;
    }
}
