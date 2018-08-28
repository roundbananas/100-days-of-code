//
//  Thomas.h
//  TWL
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef Thomas_h
#define Thomas_h

#include "PlayableCharacter.h"

class Thomas : public PlayableCharacter
{
public:
    //constructor specific to thomas
    Thomas();
    
    //overriden input handler for Thomas
    bool virtual handleInput();
};

#endif /* Thomas_h */
