//
//  zombie.h
//  Zombies
//
//  Created by Carl Turner on 21/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef zombie_h
#define zombie_h

//#include <stdio.h>

#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
    //how fast is each zombie type?
    const float BLOATER_SPEED = 40;
    const float CHASER_SPEED = 80;
    const float CRAWLER_SPEED = 20;
    
    //how tough is each zombie type?
    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 3;
    
    //Make each zombie vary its speed slightly
    //stops zombies bunching up together
    const int MAX_VARIANCE = 30;
    const int OFFSET = 101 - MAX_VARIANCE;
    
    //variables for each individual zombie
    Vector2f m_Position;
    Sprite m_Sprite;
    float m_Speed;
    float m_Health;
    bool m_Alive;
    
public: //function prototypes
    //handle when a bullet hits zombie
    bool hit();
    
    //find out if the zombie is alive
    bool isAlive();
    
    //Spawn a new zombie
    void spawn(float startX, float startY, int type, int seed); //type refers to the type of zombie
    
    //Return a rectangle that is the position occupied by the zombie in the world
    FloatRect getPosition();
    
    //get a copy of the sprite to draw
    Sprite getSprite();
    
    //update zombie each frame
    void update(float elapsedTime, Vector2f playerLocation); //use player location to make zombie chase the player
}

#endif /* zombie_hpp */
