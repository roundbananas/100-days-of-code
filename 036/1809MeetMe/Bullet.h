//
//  Bullet.h
//
//  Created by Carl Turner on 17/9/18.
//
//Bullet class manages movement and intensity of LEDs. Player holds the colour.

#ifndef Bullet_h
#define Bullet_h

#include "Arduino.h"  

class Bullet
{
  private:
  
    //index of first 'on' and 'off' pixels
    int m_Head;
    int m_Tail;

    bool m_IsInFlight;

    int &head = m_Head;
    int &tail = m_Tail;

    //how fast does the bullet travel?
    //this is the millisecond interval the bullet stays in one spot while moving 
    unsigned long m_Speed;

    //create arrays to hold RGB values for each pixel between head and tail
    int m_RedValues[];
    int m_GreenValues[];
    int m_BlueValues[];

  public:
    Bullet();
    void setBulletSpeed(int bulletSpeed);  
    void spawn(int head, int tail);
    void updateBullet(unsigned long dt);
    int getHead();
    int getTail();
    bool isInFlight();
    void shoot(int bulletSpeed, int* colourArray);
    void setColour(int r, int g, int b);
};

#endif
