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
    int m_HeadAPos;     //position of head on player's own led strip
    int m_HeadBPos;     //position of head on other player's led strips
    int m_TrailLength;

    bool m_AIsInFlight;
    bool m_BIsInFlight;

    //how fast does the bullet travel?
    //this is the millisecond interval the bullet stays in one spot while moving
    //in practice it's the time between calling the  updateBullet() function 
    unsigned long m_Speed;

    //create arrays to hold RGB values for each pixel between head and tail
    // for sending to  Adafruit_DotStar::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
    int m_ColourR[];
    int m_ColourG[];
    int m_ColourB[];

  public:
    Bullet();
    void spawn();
    void shoot(int bulletSpeed, int* colourArray);
    void updateBullet(int num_Pixels);  //updates both A and B bullets
   
    int getBulletSpeed(); 
    
    int getHeadAPos();
    int getHeadBPos();
    int getTailAPos();
    int getTailBPos();
    int getTrailLength();
    
    bool AIsInFlight();
    bool BIsInFlight();

    int getColourR(int index); //returns colour of one piece of the bullet (ie one pixel)
    int getColourG(int index);
    int getColourB(int index);
};

#endif
