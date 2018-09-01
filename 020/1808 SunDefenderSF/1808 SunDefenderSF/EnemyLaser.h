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
#include "Enemy.h"

using namespace sf;

class EnemyLaser
{
private:
    Sprite m_LaserSprite;
    Texture m_LaserTexture;
    bool m_LaserOn;
    Vector2f m_LaserPosition;
    
public:
    bool getOn();
    Vector2f getPosition();
    Sprite getSprite();
    void spawn(Vector2f position, int i);
    void update(Enemy* enemies, int numEnemies, VertexArray& mountainsVA, int index); //updates ONE laser, based on enemies[i].m_Shooting and correlating laser number to mountain position
};


#endif /* EnemyLaser_h */
