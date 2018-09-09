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
#include <iostream>

SunSegment::SunSegment()
{
    m_SunSprite = Sprite(TextureHolder::GetTexture(resourcePath() + "Sun-full.png"));
}

void SunSegment::spawn(Vector2f position)
{
    //initialise /reset all values
    //eventually create 6 different sun sprites, put them in an array. Then reinitialise the m_currentSunSprite = m_SunSprites[0]; here
    m_SunLifeRemaining = m_SunLife;
    m_TotalTimeSunHasBeenLasered = 0.0;
    m_SegmentAlive = true;
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

bool SunSegment::isAlive()
{
    return m_SegmentAlive;
}

void SunSegment::update(int timeToAdd)
{
    m_SegmentAlive = true;
    m_TotalTimeSunHasBeenLasered += timeToAdd;
    m_SunLifeRemaining = m_SunLife - (m_TotalTimeSunHasBeenLasered * m_EnemyLaserEffect);

    std::cout << "\nSun life remaining: " << m_SunLifeRemaining;
    
    if (m_SunLifeRemaining < 0)
    {
        m_SegmentAlive = false;
    }
}