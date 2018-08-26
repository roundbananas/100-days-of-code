//
//  PlayableCharacter.h
//  TWL
//
//  Created by Carl Turner on 26/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef PlayableCharacter_h
#define PlayableCharacter_h

#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected: //these can be used as if they are public, by a sub-class (inheritance)
    Sprite m_Sprite; //character sprite
    
    float m_Jumpduration; //how long does jump last
    
    //are they currently jumping/falling
    bool m_IsJumping;
    bool m_IsFalling;
    
    //which direction they currently moving?
    bool m_LeftPressed;
    bool m_RightPressed;
    
    //how long has this jump lasted for  so far
    //useful to trigger a jump sound effect
    float m_TimeThisJump;
    
    //has player just initialised a jump
    bool m_JustJumped = false;
    
private: //NOT accessible directly
    //What is the gravity
    //holds number of px per second the character will fall
    float m_Gravity;
    
    //how fast is the character
    //hold number of px per second the character moves
    float m_Speed = 400;
    
    //Where is the player
    //world position, not screen position.
    Vector2f m_Position;
    
    //Where are the character's various body parts?
    //we create a composite collision boundary for the character (more accurate than just one big box)
    FloatRect m_Feet;
    FloatRect m_Head;
    FloatRect m_Right;
    FloatRect m_Left;
    
    Texture m_texture;
    
public:
    void spawn(Vector2f startPosition, float gravity);
    
    //Pure virtual function. Having this in the class
    //makes it an Abstract Class and it cannot be
    //instantiated.
    //All sub-classes must provide a definition for this function. So we don't need to define it in PlayableCharacter.cpp
    bool virtual handleInput() = 0;
    
    //Getter function - Where is the player
    FloatRect getPosition();
    
    //Getter functions
    FloatRect getFeet();
    FloatRect getHead();
    FloatRect getRight();
    FloatRect getLeft();
    
    //Getter function. Send a copy of sprite to main
    Sprite getSprite();
    
    //Manipulator functions - Make characters stand firm, not jump through a solid tile
    void stopFalling(float position);
    void stopRight(float position);
    void stopLeft(float position);
    void stopJump(float position);
    
    //Getter functions - where is centre of character
    //this value is held in m_Position
    Vector2f getCenter();
    
    void update(float elapsedTime);
    
}

#endif /* PlayableCharacter_h */
