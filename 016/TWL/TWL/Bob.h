//
//  Bob.h
//  TWL
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef Bob_h
#define Bob_h

#include "PlayableCharacter.h"

class Bob : public PlayableCharacter
{
public:
    //constructor specific to Bob
    Bob();
    
    //overriden input handler for Bob
    //handleInput returns m_JustJumped, used to trigger jumping sound effect
    bool virtual handleInput();
};

#endif /* Bob_h */
