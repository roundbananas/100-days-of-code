//
//  CreatePlayer.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Canon.h"
#include "BattleGround.h"

Canon* createPlayer(int numCanons, int m_NumMountains, VertexArray& canonVA)
{
    /*******
     CREATE CANON POSITIONS
     *******/
    //What type of primitive are we using?
    canonVA.setPrimitiveType(Points);
    const int VERTS_IN_POINT = 2;
    
    //Set size of vertex array
    canonVA.resize(numCanons * VERTS_IN_POINT); //
    
    //initialise vertex array. Doing this manually because in physical game the mountains are fixed
    //vector coords taken from Adobe illustrator
    
    canonVA[0].position = Vector2f(90, 1055);
    canonVA[1].position = Vector2f(290, 1055);
    canonVA[2].position = Vector2f(465, 1055);
    canonVA[3].position = Vector2f(640, 1055);
    canonVA[4].position = Vector2f(830, 1055);
    
    /*******
     CREATE CANONS
     *******/
    Canon* player = new Canon[numCanons];
    
    for (int i = 0; i < numCanons; i++)
    {
        Vector2f pos;
        pos.x = canonVA[i].position.x;
        pos.y = canonVA[i].position.y;
        
        //calculate type.Eventually we may want to save canon types players have upgraded to, between levels.
        int canonType = (rand() % 2 ); //number between 0 and 1
        
        //spawn canon into the player array
        player[i].spawn(pos, canonType, i);
    }
    return player;
}
