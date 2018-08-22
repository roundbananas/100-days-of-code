//
//  Player.h
//  Zombies
//
//  Created by Carl Turner on 18/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//
#ifndef Player_h
#define Player_h

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

using namespace sf;

class Player
{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    
    //where is the player?
    Vector2f m_Position;
    
    Sprite m_Sprite;
    Texture m_Texture;
    
    //What's the screen resolution?
    Vector2f m_Resolution;
    
    //What's size of current arena?
    IntRect m_Arena;
    
    //How big is each tile of the arena?
    int m_TileSize;
    
    //Which dirns is player currently moving in?
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;
    
    //How much health has player got?
    int m_Health;
    int m_MaxHealth;
    
    //When was player last hit?
    Time m_LastHit;
    
    //Speed in pixels per second
    float m_Speed;
    
public:
    
    Player();
    
    void spawn(IntRect arena, Vector2f resolution, int tileSize);
    
    //Call this at the end of every game
    void resetPlayerStats();
    
    //Handle the player getting hit by a zombie
    bool hit(Time timeHit);
    
    //How long ago was the player last hit?
    Time getLastHitTime(); //use this for detecting collisions
    
    //Where is the player
    FloatRect getPosition(); //gets rectangle which contains the player graphic. Also useful for collision detection
    
    //Where is the centre of the player
    Vector2f getCenter();
    
    //Which angle is player facing?
    float getRotation(); //3-o-clock is 0degrees and increases clockwise.
    
    //Send copy of sprite to main
    Sprite getSprite();
    
    //Move the player
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    //Stop the player moving in a specific direction
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    
    //Call this function once per frame
    void update(float elapsedTme, Vector2i mousePosition);
    
    //give player a speed boost
    void updgradeSpeed();
    
    //Give player some health
    void upgradeHealth();
    
    //increase max amount of health a player can have
    void increaseHealthLevel(int amount);
    
    //How much health has player currently got?
    int getHealth();
};

#endif /* Player_h */
