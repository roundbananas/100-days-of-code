//
//  Header.h
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <SFML/Graphics.hpp>
using namespace sf;

class Canon
{
private:
    //variables for graphics
    Sprite m_Sprite;
    Texture m_Texture;
    Vector2f m_Position;     //where is the canon
    
    //What type can it be
    //What type is it currently, and how long to recharge
    int m_CanonType;
        const int NORMAL_CANON = 0;
        const int RAPID_CANON = 1;
    
    int m_FireRate;
        const int NORMAL_FIRERATE = 4;
        const int RAPID_FIRERATE = 10;
    
    //how long does it take to recharge after firing?
    double m_RechargeTime;
        const double NORMAL_RECHARGE = 0.3; //seconds
        const double RAPID_RECHARGE = 0.1;
    
    //What colour is it?
    //   const int NORMAL_COLOUR
    
 
    
    //When was the last time it fired?
    double m_LastFiredTime;
    
    //is it ready to fire again?
    bool m_isCharged;
    
    //Tell me if it just fired, so we can play a sound
    bool m_JustFired;
    
    
public:
    //Canon();
    //Getter functions?
    
    Sprite getSprite();
    
    Vector2f getPosition();
    int getType();
    bool getCharged();
    
    double getLastFired();
    int getFireRate();
    
    //Manipulator functions
    void fireCanon(double t);
    void spawn(Vector2f position, int canonType, int seed);
    void powerUp();         //handle canon getting powerup
    void update(double elapsedTime);  //all we need to update canon is current time, and what Engine:m_Input() grabs.
};

#endif /* Header_h */
