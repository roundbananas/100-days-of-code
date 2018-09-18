//
//  PlayerCharacter.h
//
//  Created by Carl Turner on 18/9/18.
//
/*
 * How PlayableCharacter class works:
 * - I want multiple players in the game. 
 * - Each player has same basic behaviour and characteristics (bullets, input controls, score)
 * - BUT, I want to manage their individual values separately (bullet colour, input pins for button/pot, and their score.)
 * - So: 
 *   - PlayableCharacter class declares common characteristics and behaviour.
 *   - create separate sub-classes (Player1 and Player2), that inherit from PlayableCharacter, to initialise and manage values specific to each player.
 *   - PlayableCharacter contains the update function, since both players have the same behaviour.
 * - THEN:
 *   - Engine.h declares individual player objects
 *   - Each player's update and input functions are called from Input.cpp, Update.cpp and Render.cpp (part of Engine.cpp)
 */

#ifndef PlayerCharacter_h
#define PlayerCharacter_h

#include "Arduino.h"

class PlayerCharacter
{
  protected: //can be used as if they're public by a sub-class (inheritance)
    
    bool m_HasFired = false;
    int m_Score;
    int m_Colour[3];

  public:
    PlayerCharacter();
    bool getHasFired();
    int getScore();
    void setScore(int score);
    int* getColour();
    
   // bool virtual handleInput() = 0; //returns value of m_HasFired, which will be used to let calling code know if it needs to play a sound effect
    void addScore();
    void updatePlayer(unsigned long currentTime);
};

#endif
