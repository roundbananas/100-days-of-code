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
    
    bool m_LaserOn;
    Vector2f m_LaserPosition;
    
public:
    EnemyLaser();
    bool getOn();
    Vector2f getPosition();
    void update(Enemy* enemies[]); //needs to update on enemies[i].m_Shooting
}


#endif /* EnemyLaser_h */
