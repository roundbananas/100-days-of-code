//
//  Player1.h
//
//  Created by Carl Turner on 18/9/18.
//
#ifndef Player1_h
#define Player1_h

#include "PlayerCharacter.h"

class Player1 : public PlayerCharacter
{
  public:
    //constructor specific to Player1
    Player1();
    void spawn(int r, int g, int b);

    bool virtual handleInput();
};
#endif
