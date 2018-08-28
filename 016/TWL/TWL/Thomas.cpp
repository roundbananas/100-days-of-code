//
//  Thomas.cpp
//  TWL
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Thomas.h"
#include "TextureHolder.h"
#include "ResourcePath.hpp"

//Constructor
Thomas::Thomas()
{
    //associate a texture with sprite
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "thomas.png"));
    
    m_JumpDuration = 0.45;
}

//Define virtual function
bool Thomas::handleInput()
{
    m_JustJumped = false;
    
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        //Start jump if not already jumping, but only if not falling
        if (!m_IsJumping && !m_IsFalling)
        {
            m_IsJumping = true;
            m_TimeThisJump = 0;
            m_JustJumped = true; //this will let the calling code know if it needs to play a sound effect
        }
        
        // do we need m_JustJumped = false here?
    }
    else
    {
        m_IsJumping = false;
        m_IsFalling = true;
    }
    
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        m_LeftPressed = true;
    }
    else
    {
        m_LeftPressed = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        m_RightPressed = true;
    }
    else
    {
        m_RightPressed = false;
    }
    
    //this will let the calling code know if it needs to play a sound effect
    return m_JustJumped;
}
