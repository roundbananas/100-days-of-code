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

MtnProjectiles* createMtnProjectiles(int numCanons, VertexArray& projectileTargetsVA, VertexArray& mtnProjectilePosVA)
{
    /*******
     CREATE SPRITE POSITIONS
     We could just shoot straight at the enemy positions. but in the physical game we won't be able to do that, and I think shooting along the ground will help reinforce/be consistent with the synthwave grid / aesthetic.
     *******/
    //What type of primitive are we using?
    mtnProjectilePosVA.setPrimitiveType(Points);
    const int VERTS_IN_POINT = 2;
    
    //Set size of vertex array
    mtnProjectilePosVA.resize(numCanons * VERTS_IN_POINT);
    
    //initialise vertex array. Doing this manually because in physical game the mountains are fixed
    //vector coords taken from Adobe illustrator
    mtnProjectilePosVA[0].position = Vector2f(255, 330);
    mtnProjectilePosVA[1].position = Vector2f(367, 257);
    mtnProjectilePosVA[2].position = Vector2f(479, 280);
    mtnProjectilePosVA[3].position = Vector2f(590, 304);
    mtnProjectilePosVA[4].position = Vector2f(701, 255);
    
    /*******
     CREATE CANON TARGET POSITIONS (we create these here by reference, so CanonProjectile::shoot() function can use them too)
     these positions will be used to trigger each mtnProjectile on/off
     *******/
    projectileTargetsVA.setPrimitiveType(Points);
    projectileTargetsVA.resize(numCanons * VERTS_IN_POINT);
    projectileTargetsVA[0].position = Vector2f(233, 602);
    projectileTargetsVA[1].position = Vector2f(345, 602);
    projectileTargetsVA[2].position = Vector2f(460, 602);
    projectileTargetsVA[3].position = Vector2f(575, 602);
    projectileTargetsVA[4].position = Vector2f(690, 602);
    
    //create an array of mtnProjectile objects
    MtnProjectiles* mtnProjectiles = new MtnProjectiles[numCanons];
    
    //spawn mtnProjectiles
    for(int i = 0; i < 5; i++)
    {
        Vector2f spritePosition;
        spritePosition.x = mtnProjectilePosVA[i].position.x;
        spritePosition.y = mtnProjectilePosVA[i].position.y;

        Vector2f triggerPosition;
        triggerPosition.x = projectileTargetsVA[i].position.x;
        triggerPosition.y = projectileTargetsVA[i].position.y;
        
        mtnProjectiles[i].spawn(spritePosition, i, triggerPosition);
    }
    return mtnProjectiles;
}
