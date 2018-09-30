//
//  Player.h
//
//  Created by Carl Turner on 18/9/18.
//
#ifndef Player_h
#define Player_h

#include "Arduino.h"

class Player
{
  private:
    int m_Colour[3];  
    bool m_IsReady; //when all players are ready the game will begin
    bool m_HasFired;
    bool m_IsExploding;
    int m_CurrentBulletIndex;
    
  public:
    //constructor specific to Player
    Player();
    void spawn(int* colour);

    bool isReady();
    void setReady(bool value);

    int* getColour();
    
    bool getHasFired();
    void setHasFired();
    bool isExploding();
    void setIsExploding();
    
    void setBulletIndex(int index);
    int getBulletIndex();

};
#endif
