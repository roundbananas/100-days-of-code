//
//  MtnProjectiles.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 8/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "MtnProjectiles.h"
#include "ResourcePath.hpp"
#include "TextureHolder.h"

bool MtnProjectiles::getOn()
{
    return m_MtnProjectileOn;
}

void MtnProjectiles::stop()
{
    m_MtnProjectileOn = false;
}


bool MtnProjectiles::isDamaging()
{
    return m_IsDamaging;
}
void MtnProjectiles::stopDamaging()
{
    m_IsDamaging = false;
}

Sprite MtnProjectiles::getSprite()
{
    return m_Sprite;
}
Vector2f MtnProjectiles::getSpritePosition()
{
    return m_SpritePosition;
}
Vector2f MtnProjectiles::getTriggerPosition()
{
    return m_TriggerPosition;
}

Vector2f MtnProjectiles::getPeakPosition()
{
    return m_PeakPosition;
}

void MtnProjectiles::turnOn()
{
    m_MtnProjectileOn = true;
}

void MtnProjectiles::spawn(Vector2f spritePosition, int i, Vector2f triggerPosition, Vector2f peakPosition)
{
    //load the image for each mtnProjectile
    switch(i){
        case 0: // laser 1
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "MtnProjectile1.png"));
            break;
        case 1:
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "MtnProjectile2.png"));
            break;
        case 2:
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "MtnProjectile3.png"));
            break;
        case 3:
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "MtnProjectile4.png"));
            break;
        case 4:
            m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "MtnProjectile5.png"));
            break;
    }
    
    m_MtnProjectileOn = false;
    m_TimeMtnProjHasBeenOn = 0;
    m_IsDamaging = true;
    m_SpritePosition.x = spritePosition.x;
    m_SpritePosition.y = spritePosition.y;
    m_Sprite.setPosition(m_SpritePosition.x, m_SpritePosition.y);
    
    //the trigger position is the location where the canon's projectile hit the base of the mountain. This is the same as the target that the player's canon shoots at.
    m_TriggerPosition.x = triggerPosition.x;
    m_TriggerPosition.y = triggerPosition.y;
    
    m_PeakPosition.x = peakPosition.x;
    m_PeakPosition.y = peakPosition.y;
    
}
void MtnProjectiles::update (double dt)
{
    if(m_MtnProjectileOn)
    {
        //increment time
        m_TimeMtnProjHasBeenOn += dt;
    
        if(m_TimeMtnProjHasBeenOn > m_OnDuration)
        {
            m_TimeMtnProjHasBeenOn = 0;
            m_MtnProjectileOn = false;
            m_IsDamaging = true;
        }
    }
}
