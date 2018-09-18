//
//  PlayableCharacter.h
//
//  Created by Carl Turner on 18/9/18.
//

#ifndef PlayableCharacter_h
#define PlayableCharacter_h

#include "Arduino.h"
#include "Bullet.h"

class PlayableCharacter
{
  protected: //can be used as if they're public by a sub-class (inheritance)
    Bullet m_Bullet(30, 5, 6);

    int m_Score;

  public:
    PlayableCharacter();

    int getScore();
    void addScore();
};

#endif
