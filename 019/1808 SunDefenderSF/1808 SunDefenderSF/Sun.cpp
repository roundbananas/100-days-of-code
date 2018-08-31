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

