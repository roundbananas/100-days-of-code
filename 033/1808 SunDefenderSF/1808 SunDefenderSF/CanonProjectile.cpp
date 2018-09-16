//
//  CanonProjectile.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 5/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "CanonProjectile.h"
#include <iostream>

//constructor
CanonProjectile::CanonProjectile()
{
    m_ProjectileShape.setSize(sf::Vector2f(5, 10));
    m_ProjectileShape.setFillColor(Color(39, 170, 225)); //a light blue
    m_ProjectileShape.setOutlineThickness(2);
    m_ProjectileShape.setOutlineColor(sf::Color(40, 211, 224)); //a lighter blue
    
    
}

void CanonProjectile::stop()
{
    m_InFlight = false;
}

bool CanonProjectile::isInFlight()
{
    return m_InFlight;
}

bool CanonProjectile::isAtTarget()
{
    if (m_position.y <= m_TargetPosition.y +20)
    {
        return true;
    }
    else
        return false;
}

void CanonProjectile::shoot(int canonNumber, VertexArray& canonVA, VertexArray& projectileTargetsVA)
{
    //set start and target positions by canon number
    switch(canonNumber)
    {
        case 0: //first canon
            m_StartPosition = canonVA[0].position;
            m_TargetPosition = projectileTargetsVA[0].position;
            break;
        case 1:
            m_StartPosition = canonVA[1].position;
            m_TargetPosition = projectileTargetsVA[1].position;
            break;
        case 2:
            m_StartPosition = canonVA[2].position;
            m_TargetPosition = projectileTargetsVA[2].position;
            break;
        case 3:
            m_StartPosition = canonVA[3].position;
            m_TargetPosition = projectileTargetsVA[3].position;
            break;
        case 4:
            m_StartPosition = canonVA[4].position;
            m_TargetPosition = projectileTargetsVA[4].position;
            break;
    }
    
    //keep track of projectile
    m_position.x = m_StartPosition.x + 35; //35 fudge factor
    m_position.y = m_StartPosition.y + 4; //4 to hide them behind the player
    m_InFlight = true;
    
    
        /*
         CALCULATE HOW FAR THE PROJECTILE TRAVELS EACH FRAME,
         the actual direction of travel will be handled in the update function
         */
    
        //calculate gradient of flight path using 'point-slope' form
        //of a linear equation: y - y1 = m(x - x1), where m = gradient.
        //https://en.wikipedia.org/wiki/Linear_equation
    
        float gradient = (m_StartPosition.x - m_TargetPosition.x)/(m_StartPosition.y - m_TargetPosition.y); //Should this be dy/dx? rise over run?
    
        //any gradient less than 0 needs to be converted sign to be positive
        //so that the amount of progression each frame is positive
        //ie the bullet travels forwards
        if (gradient < 0)
        {
            gradient *= -1;
        }
    
        //calculate ratio between x and y
        //bulletSpeed is a fudge factor
        float ratioXY = m_ProjectileSpeed / (1 + gradient);
    
        //set the 'speed' horizontally and vertically
        m_ProjectileTravelDY = ratioXY;            //dx
        m_ProjectileTravelDX = ratioXY * gradient; //dy
    
        //Point bullet in right direction
        if (m_TargetPosition.x < m_StartPosition.x)
        {
            m_ProjectileTravelDX *= -1;
        }
        if (m_TargetPosition.y < m_StartPosition.y)
        {
            m_ProjectileTravelDY *= -1;
        }
    
    //Set base of mountains position on screen in pixels
    //we don't want projectiles to continue past there.
    m_MinY = 600;

    //position the bullet ready to be drawn
    m_ProjectileShape.setPosition(m_position);
}

//tell calling code where projectile is in the world
FloatRect CanonProjectile::getPosition()
{
    return m_ProjectileShape.getGlobalBounds();
}

//return actual shape, for drawing
RectangleShape CanonProjectile::getShape()
{
    return m_ProjectileShape;
}

//update the projectile each frame
void CanonProjectile::update(float dt)
{
    //update bullet position variables
    m_position.x += m_ProjectileTravelDX * dt;
    m_position.y += m_ProjectileTravelDY * dt;
    
    //move the bullet
    m_ProjectileShape.setPosition(m_position);
    
    //has bullet gone out of range?
    if (m_position.y < m_MinY)
    {
        m_InFlight = false;
    //    m_position.x = m_StartPosition.x;
    //    m_position.y = m_StartPosition.y;
    }
}
