//
//  ZombieArena.h
//  Zombies
//
//  Created by Carl Turner on 20/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef ZombieArena_h
#define ZombieArena_h
#include "zombie.h"

using namespace sf;
int createBackground(VertexArray& rVA, IntRect arena);

//declare a pointer of type Zombie
Zombie* createHorde(int numZombies, IntRect arena);


#endif /* ZombieArena_h */
