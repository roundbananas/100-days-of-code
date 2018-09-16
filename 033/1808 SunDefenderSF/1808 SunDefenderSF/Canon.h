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
    
    //How fast can it fire?
    int m_FireRate;

    //how long does it take to recharge after firing?
    double m_RechargeTime;

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
    bool getCharged();
    
    double getLastFired();
    int getFireRate();
    
    //Manipulator functions
    void fireCanon(double t);
    void spawn(Vector2f position, double rechargeTime, int seed, int fireRate);
  
    void update(double elapsedTime);  //all we need to update canon is current time, and what Engine:m_Input() grabs.
};

#endif /* Header_h */
