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
  
    //index of first 'on' pixel and length of trail
    float m_HeadAPos;     //position of head on player's own led strip
    float m_HeadBPos;     //position of head on other player's led strips
    float m_TrailLength;

    bool m_AIsInFlight;
    bool m_BIsInFlight;

    //how fast does the bullet travel?
    //this is the millisecond interval the bullet stays in one spot while moving
    //in practice it's the time between calling the  updateBullet() function 
    float m_Speed;

    float m_BulletSpeedFactor = 0.04f; //fudge factor to allow enough sensivity on pot interface, while making the bullet fly at a reasonable speed.
  
    //create arrays to hold RGB values for each pixel between head and tail
    // for sending to  Adafruit_DotStar::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
    long m_Colour;

  public:
    Bullet();
    void spawn();
    void shoot(float bulletSpeed, long colour);
    void updateBullet(int num_Pixels, float bulletSpeed, unsigned long dt);  //updates both A and B bullets
   
    float getBulletSpeed(); 
    
    float getHeadAPos();
    float getHeadBPos();
    float getTailAPos();
    float getTailBPos();
    float getTrailLength();
    
    bool AIsInFlight();
    bool BIsInFlight();

    void StopA();
    void StopB();

    long getColour(int index); //returns colour of one piece of the bullet (ie one pixel)

};

#endif
