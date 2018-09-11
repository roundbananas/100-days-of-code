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
#include "MtnProjectiles.h"

//These are forward declarations
Enemy* createPlatoon(int numEnemies, int numMountains, VertexArray& mountainsVA);

Canon* createPlayer(int numCanons, int NumMountains, VertexArray& canonVA);

MtnProjectiles* createMtnProjectiles(int numCanons, VertexArray& mountainsVA, VertexArray& projectileTargetsVA, VertexArray& mtnProjectilePosVA);

EnemyLaser* createEnemyLasers(VertexArray& laserVA, VertexArray& mountainsVA);

#endif /* BattleGround_h */
