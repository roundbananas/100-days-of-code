//
//  Enemy.h
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h

class Enemy
{
private:
    
    //How long does each enemy type stay in one spot, before moving?
    const double NORMAL_LINGER = 1.0;  //seconds
    const double STRONG_LINGER = 2.0;
    const double SUPER_LINGER = 0.5;
    
    //Use colours to differentiate enemy types
  //  const int NORMAL_COLOUR[3] = {255, 255, 0};   //yellow
    const int NORMAL_COLOURR = 255; //yellow
    const int NORMAL_COLOURG = 255;
    const int NORMAL_COLOURB = 0;
    
    const int STRONG_COLOURR = 255;   //red
    const int STRONG_COLOURG = 0;
    const int STRONG_COLOURB = 0;
    
    const int SUPER_COLOURR = 255;    //purple
    const int SUPER_COLOURG = 0;
    const int SUPER_COLOURB = 255;
    
    //How much health does each enemy type start with?
    const int NORMAL_HEALTH = 10;
    const int STRONG_HEALTH = 20;
    const int SUPER_HEALTH = 30;
    
    //Variables to describe an enemy's fixed characteristics
    int m_LingerTime;   //how long they stay in one spot
    int m_ColourR = 0;     //colour
    int m_ColourG = 0;
    int m_ColourB = 0;
    int m_Colour[3] = {m_ColourR, m_ColourG, m_ColourB};
    
    //Variables to describe an enemy's dynamic characteristics
    int m_Health;       //current health
    int m_Position;     //current position
    bool m_Alive;       //currently alive?
    bool m_Shooting;    //currently shooting?
    
    int m_type;         //for debugging
    
    unsigned long m_lastUpdate;
    
public:
    //Getter functions
    bool isAlive();
    int getPosition();
    int* getColour();    //returns an array
    int getLinger();
    
    int getType();      //for debugging
    
    //Maniuplation functions
    void spawn(int position, int enemyType, int seed);
    bool hit();         //handle enemy getting hit by projectile
    void update(double t, int numMountains);
};

#endif /* Enemy_h */
