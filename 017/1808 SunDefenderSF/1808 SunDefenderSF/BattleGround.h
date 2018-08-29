//
//  BattleGround.h
//  1808SunDefender
//
//  Created by Carl Turner on 27/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef BattleGround_h
#define BattleGround_h
#include "Enemy.h"
#include "Canon.h"

Enemy* createPlatoon(int numEnemies, int numMountains);

Canon* createPlayer(int numCanons, bool mtnArray[]);

#endif /* BattleGround_h */
