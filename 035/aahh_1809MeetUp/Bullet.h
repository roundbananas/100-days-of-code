//
//  Bullet.h
//
//  Created by Carl Turner on 17/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#ifndef Bullet_h
#define Bullet_h

#include "Arduino.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>  

class Bullet
{
  private:
    //for use by constructor
    int m_NumPixels;
    int m_DataPin;
    int m_ClockPin;

    Adafruit_DotStar m_ledStrip;
  
    //index of first 'on' and 'off' pixels
    int m_Head;
    int m_Tail;

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
    void spawn(int pixels, int dataPin, int clockPin, int head, int tail, int colour[]);
    void updateBullet(unsigned long dt);
    int getHead();
    int getTail();
};

#endif
