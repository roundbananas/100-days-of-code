//
//  CanonProjectile.h
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 5/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef CanonProjectile_h
#define CanonProjectile_h

#include <SFML/Graphics.hpp>

using namespace sf;

class CanonProjectile
{
private:
    //where is the projectile?
    Vector2f m_position;
    
    //Start and target positions?
    Vector2f m_StartPosition;
    Vector2f m_TargetPosition;
    
    //what does bullet look like?
    RectangleShape m_ProjectileShape;
    
    float m_TrailLength = 200; //create a trail effect
    
    //is this projectile currently in flight?
    bool m_InFlight = false;
    
    //how fast does it travel?
    float m_ProjectileSpeed = 1000;
    
    //What fraction of 1 pixel does the projectile travel each frame?
    float m_ProjectileTravelDX;
    float m_ProjectileTravelDY;
    
    //boundary so projectile stops at base of mountains
    float m_MinY; //Y is measured from top of screen, down to bottom.
    
public:
    //constructor
    CanonProjectile();
    
    //stop the projectile
    void stop();
    
    bool isInFlight();
    
    bool isAtTarget();
    
    //spawn a new projectile
    void shoot(int canonNumber, VertexArray& canonVA, VertexArray& projectileTargetsVA);
    
    //tell calling code where projectile is in the world
    FloatRect getPosition();
    
    //return actual shape, for drawing
    RectangleShape getShape();
    
    //update the projectile each frame
    void update(float currentTime);
    
};

#endif /* CanonProjectile_h */
