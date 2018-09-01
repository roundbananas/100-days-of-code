//
//  SunSegment.h
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

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
    bool m_SegmentAlive;
    
public:
    SunSegment();
    void spawn(Vector2f position);
    Sprite getSprite();
    
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
