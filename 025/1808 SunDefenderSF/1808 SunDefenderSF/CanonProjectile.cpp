//
//  CanonProjectile.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 5/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "CanonProjectile.h"

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

void CanonProjectile::shoot()
{
    m_InFlight = true;
}

void CanonProjectile::spawn(float startX, float startY, float xTarget, float yTarget)
{
    //keep track of projectile
    m_position.x = startX;
    m_position.y = startY;
    
    //store start position for resetting it after it's hit the mountain
    m_StartPosition.x = startX;
    m_StartPosition.y = startY;
    
        /*
         CALCULATE HOW FAR THE PROJECTILE TRAVELS EACH FRAME,
         the actual direction of travel will be handled in the update function
         */
    
        //calculate gradient of flight path using 'point-slope' form
        //of a linear equation: y - y1 = m(x - x1), where m = gradient.
        //https://en.wikipedia.org/wiki/Linear_equation
    
        float gradient = (startX - xTarget)/(startY - yTarget); //Should this be dy/dx? rise over run?
    
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
        if (xTarget < startX)
        {
            m_ProjectileTravelDX *= -1;
        }
        if (yTarget < startY)
        {
            m_ProjectileTravelDY *= -1;
        }
    
    //Set base of mountains position on screen in pixels
    //we don't want projectiles to continue past there.
    m_MinY = 600;
    m_InFlight = true;

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
        m_position.x = m_StartPosition.x;
        m_position.y = m_StartPosition.y;
    }
}
