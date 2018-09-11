//
//  SunSegment.h
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//
//The sun has a total life: double m_SunLife. //in 'units' (use double because the Timer object uses a double.
//Enemy lasers have an effect of draining sunlife at a rate: double m_EnemyLaserEffect; //in 'units per second'
//So, if enemie lasers have shot the sun for a total of: m_SunLife/m_EnemyLaserEffect seconds, the sun will be completely drained.
//So we need to create a variable to hold how many seconds the sun has been shot so far: double m_TotalTimeSunHasBeenLasered
//We'll give visual feedback about the sun's status using a series of sprites. Each sprite will have varying degrees of sun coloured (alive), from 100% to 0.

#ifndef SunSegment_h
#define SunSegment_h

#include <SFML/Graphics.hpp>

using namespace sf;

class SunSegment
{
private:
    Sprite m_SunSprite;
    Texture m_SunTexture;
    Vector2f m_Position;
    
    double m_SunLife = 50000.0;           //in 'units'
    double m_EnemyLaserEffect = 0.1;  //in 'units per second'
    
    //time dependent variables
    double m_TotalTimeSunHasBeenLasered;    //for how many seconds has the sun has been lasered so far?    
    double m_SunLifeRemaining;
    bool m_SegmentAlive;
    
public:
    SunSegment();
    void spawn(Vector2f position);
    Sprite getSprite();
    
    bool isAlive();
    double getTotalLife();
    double getTimeLasered();
    double getLaserEffect();
    double getLifeRemaining();
    void update(int timeToAdd); //timeToAdd in seconds to total time sun has been lasered
};
#endif /* SunSegment_h */

/*
 //local variables
 int sunArray[] {1, 2, 3, 4, 5};
 int numSegments = sizeof(sunArray);
 
 //SunSegment.h
 class SunSegment
 {
 private:
 
 public:
 void spawn(int position, float size);
 };
 
 //BattleGround.h (to forward declare createSun in Engine.cpp
 SunSegment* createSun(int numSegments, int sunArray);
 
 //CreateSun.cpp
 SunSegment* createSun(int numSegments, int sunArray)
 {
 SunSegment* sun = new SunSegment[numSegments];
 sun[i].spawn (pos, size);
 }
 
 
 }
 */
