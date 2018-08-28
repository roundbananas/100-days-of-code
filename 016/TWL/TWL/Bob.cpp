//
//  Bob.cpp
//  TWL
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Bob.h"
#include "TextureHolder.h"
#include "ResourcePath.hpp"

//Constructor
Bob::Bob()
{
    //associate a texture with sprite
    m_Sprite = Sprite(TextureHolder::GetTexture(resourcePath() + "bob.png"));
    
    m_JumpDuration = 0.25;
}

//Define virtual function
bool Bob::handleInput()
{
    m_JustJumped = false;
    
    if (Keyboard::isKeyPressed(Keyboard::Up))
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
    
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        m_LeftPressed = true;
    }
    else
    {
        m_LeftPressed = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
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
