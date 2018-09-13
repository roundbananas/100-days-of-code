//
//  Enemy.h
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h

#include <SFML/Graphics.hpp>
#include "EnemyLaser.h"

using namespace sf;

class Enemy
{
private:
    
    Sprite m_EnemySprite;
    Texture m_EnemyTexture;
    
    //How long does each enemy type stay in one spot, before moving?
    const double NORMAL_LINGER = 1.8;  //seconds
    const double STRONG_LINGER = 1.2;
    const double SUPER_LINGER = 1.0;
    
    //How much health does each enemy type start with?
    const int NORMAL_HEALTH = 10;
    const int STRONG_HEALTH = 20;
    const int SUPER_HEALTH = 30;
    
    int m_DamagePerHit;
    
    //Variables to describe an enemy's fixed characteristics
    double m_LingerTime;   //how long they stay in one spot
    
    //Variables to describe an enemy's dynamic characteristics
    int m_Health;       //current health
    Vector2f m_VPosition; //current position (digital version)

    bool m_Alive;       //currently alive?
    bool m_Shooting;    //currently shooting?
    bool m_JustStoppedShooting; //used to update sun
    double m_ShootDuration;
    double m_lastAliveUpate;

    
    int m_type;         //for debugging
    
    double m_lastMoveUpdate; //in seconds
    double m_lastShootUpdate; //in seconds

    
public:
    //there's no default constructor?
    Sprite getSprite();
    
    //Getter functions
    bool isAlive();
    bool isShooting();
    double getShootDuration();
    bool getJustStoppedShooting();

    float getPositionX();
    float getPositionY();
    Vector2f getPosition();

    int* getColour();    //returns an array
    double getLinger();
        
    int getType();      //for debugging
    
    void spawnD(Vector2f pos, int enemyType, int seed, int lifeLost); //for digital version
    bool hit();         //handle enemy getting hit by projectile
    void updateD(double t, VertexArray& mountainsVA); //for digital version
};

#endif /* Enemy_h */
