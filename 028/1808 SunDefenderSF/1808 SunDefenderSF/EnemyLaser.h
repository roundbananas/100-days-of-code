//
//  EnemyLaser.h
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 30/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef EnemyLaser_h
#define EnemyLaser_h

#include <SFML/Graphics.hpp>

using namespace sf;

class EnemyLaser
{
private:
    Sprite m_LaserSprite;
    Texture m_LaserTexture;
    Vector2f m_LaserSpritePosition;   //position of the sprite
    Vector2f m_LaserPeakPosition;   //which peak is the laser associated with?
    
    bool m_LaserOn;
    double m_timeLaserHasBeenOn;
    
public:
    bool getOn();
    void turnOff();
    
    Sprite getSprite();
    Vector2f getSpritePosition();
    Vector2f getPeakPosition();
    
    void spawn(Vector2f spritePosition, Vector2f peakPosition, int i);
    void update(double dt, int shootDuration); //updates ONE laser
};


#endif /* EnemyLaser_h */
