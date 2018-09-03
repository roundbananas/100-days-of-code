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
#include "EnemyLaser.h"

//These are forward declarations
Enemy* createPlatoon(int numEnemies, int numMountains, VertexArray& mountainsVA);

Canon* createPlayer(int numCanons, int NumMountains, VertexArray& canonVA);

EnemyLaser* createEnemyLasers(VertexArray& laserVA);

#endif /* BattleGround_h */
