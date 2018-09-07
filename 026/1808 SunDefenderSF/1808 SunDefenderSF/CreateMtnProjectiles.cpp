//
//  CreateMtnProjectiles.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 8/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "BattleGround.h"
#include "MtnProjectiles.h"

//create an array of projectiles and initialise their start and target positions
//1. Engine.h - declare a vertexarray: VertexArray m_ProjectileTargetArray; and a pointer CanonProjectile* projectiles = nullptr;
//2. engine.cpp - pass m_ProjectileTargetArray and m_canonArrayDigital (which is the start positions for the projectiles) to CreateProjectiles.cpp, by reference
//3. CreateProjectiles.cpp
//- create vertex array for targets
//- declare projectile array using new keyword
//- position and spawn each projectile by passing a intermediary position variable to the spawn function
//4. when we need to see the projectile, we'll draw it in render() and update it in update()

CanonMtnProjectiles* createMtnProjectiles(VertexArray& mtnProjectileVA, Canon* player)
{
    /*******
     CREATE POSITIONS
     We could just shoot straight at the enemy positions. but in the physical game we won't be able to do that, and I think shooting along the ground will help reinforce/be consistent with the synthwave grid / aesthetic.
     *******/
    //What type of primitive are we using?
    projectileTargetVA.setPrimitiveType(Points);
    const int VERTS_IN_POINT = 2;
    
    //Set size of vertex array
    mtnProjectileVA.resize(5 * VERTS_IN_POINT); //5 = number of canons/projectiles
    
    //initialise vertex array. Doing this manually because in physical game the mountains are fixed
    //vector coords taken from Adobe illustrator
    mtnProjectileVA[0].position = Vector2f(236, 700);
    mtnProjectileVA[1].position = Vector2f(362, 700);
    mtnProjectileVA[2].position = Vector2f(490, 700);
    mtnProjectileVA[3].position = Vector2f(615, 700);
    mtnProjectileVA[4].position = Vector2f(742, 700);
    
    /*******
     GET CANON TARGET POSITIONS (we created these in CanonProjectile.cpp shoot() function)
     these positions will be used to trigger each mtnProjectile on/off
     *******/
    
    MtnProjectiles* mtnProjectiles = new MtnProjectile[5]; //5 = number of projectiles
    
    for(int i = 0; i < 5; i++)
    {
        Vector2f triggerPosition;
        triggerPosition.x = player[i].m_TargetPosition.x;
        triggerPosition.y = player[i].m_TargetPosition.y;
        
        mtnProjectiles[i]spawn(Vector2f spritePosition, int i, Vector2f triggerPosition)
    }
    return mtnProjectiles;
}
