//
//  CreateProjectiles.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 6/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "BattleGround.h"
#include "CanonProjectile.h"

//create an array of projectiles and initialise their start and target positions
//1. Engine.h - declare a vertexarray: VertexArray m_ProjectileTargetArray; and a pointer CanonProjectile* projectiles = nullptr;
//2. engine.cpp - pass m_ProjectileTargetArray and m_canonArrayDigital (which is the start positions for the projectiles) to CreateProjectiles.cpp, by reference
//3. CreateProjectiles.cpp
//- create vertex array for targets
//- declare projectile array using new keyword
//- position and spawn each projectile by passing a intermediary position variable to the spawn function
//4. when we need to see the projectile, we'll draw it in render() and update it in update()

CanonProjectile* createProjectiles(VertexArray& projectileTargetVA, VertexArray& canonVA)
{
    /*******
     CREATE TARGET POSITIONS (at the base of the mountains)
     We could just shoot straight at the enemy positions. but in the physical game we won't be able to do that, and I think shooting along the ground will help reinforce/be consistent with the synthwave grid / aesthetic.
     *******/
    //What type of primitive are we using?
    projectileTargetVA.setPrimitiveType(Points);
    const int VERTS_IN_POINT = 2;
    
    //Set size of vertex array
    projectileTargetVA.resize(5 * VERTS_IN_POINT); //5 = number of canons/projectiles
    
    //initialise vertex array. Doing this manually because in physical game the mountains are fixed
    //vector coords taken from Adobe illustrator
    projectileTargetVA[0].position = Vector2f(236, 700);
    projectileTargetVA[1].position = Vector2f(362, 700);
    projectileTargetVA[2].position = Vector2f(490, 700);
    projectileTargetVA[3].position = Vector2f(615, 700);
    projectileTargetVA[4].position = Vector2f(742, 700);
    
    /*******
     GET EXISTING CANON POSITIONS (we created these in createPlayer())
     these are the start positions for the projectiles
     *******/
    
    CanonProjectile* projectiles = new CanonProjectile[5]; //5 = number of projectiles
    
    for(int i = 0; i < 5; i++)
    {
        Vector2f startPos;
        startPos.x = canonVA[i].position.x + 37; //37 fudge factor
        startPos.y = canonVA[i].position.y + 4; //4 to hide them behind the player
        
        Vector2f targetPos;
        targetPos.x = projectileTargetVA[i].position.x;
        targetPos.y = projectileTargetVA[i].position.y;
        
        projectiles[i].spawn(startPos.x, startPos.y, targetPos.x, targetPos.y);
    }
    return projectiles;
}
