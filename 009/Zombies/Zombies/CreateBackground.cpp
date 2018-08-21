//
//  CreateBackground.cpp
//  Zombies
//
//  Created by Carl Turner on 20/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "SFML/Graphics.hpp"
#include "ZombieArena.h"

int createBackground(VertexArray& rVA, IntRect arena)
{
    //Anything we do to rVA we are actually doing
    // to background (in the main function).
    
    //How big is each tile/texture
    const int TILE_SIZE = 50; //refers to number of pixels
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4; // this means there a 4
    
    //size of world in TILES, not pixels
    int worldWidth = arena.width / TILE_SIZE;
    int worldHeight = arena.height / TILE_SIZE;
    
    //What type of primitive are we using?
    rVA.setPrimitiveType(Quads);
    
    //Set size of vertex array
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
    
    //Star at the beginning of the vertex array
    int currentVertex = 0;
    
    //initialise vertex array
    //putting height for() loop inside the w for() loop means it will initialise the array column by column, not in rows.
    for (int w = 0; w < worldWidth; w++)
    {
        for (int h=0; h< worldHeight; h++)
        {
        rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h  * TILE_SIZE);
        rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h  * TILE_SIZE);
        rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h  * TILE_SIZE)+TILE_SIZE);
        rVA[currentVertex + 3].position = Vector2f(w * TILE_SIZE, (h  * TILE_SIZE)+TILE_SIZE);
        
        //Define position in the texture for current quad
        //Either grass, stone, bush or wall
            if (h == 0 || h == worldHeight - 1 || w==0 || w == worldWidth - 1)
            {
                //use wall texture (it's the 4th tile down in the sprite sheet, hence the location of top left corner of it in the sprite sheet = 3*TILE_SIZE = TILE_TYPES*TILE_SIZE = 150
                rVA[currentVertex+0].texCoords = Vector2f(0,0 + TILE_TYPES*TILE_SIZE);
                rVA[currentVertex+1].texCoords = Vector2f(TILE_SIZE,0 + TILE_TYPES*TILE_SIZE);
                rVA[currentVertex+2].texCoords = Vector2f(TILE_SIZE,TILE_SIZE + TILE_TYPES*TILE_SIZE);
                rVA[currentVertex+3].texCoords = Vector2f(0,TILE_SIZE + TILE_TYPES*TILE_SIZE);
            }
            else{
                //use a random floor texture
                srand((int)time(0) + h*w-h);        //seed the random number generator with h*w-h
                int mOrG =(rand() % TILE_TYPES);    //get random number between 0 and value of TILE_TYPES (ie 0 and 3). mOrg = mud or grass (an arbitrary name)
                int verticalOffset = mOrG * TILE_SIZE;  //choose a tile by its vertical position in the sprite sheet, based on the random number. Our sprite sheet is only one tile wide. If we had two columns of tiles in the sprite sheet we'd need to calculate a random horizontal offset too.
                rVA[currentVertex+0].texCoords = Vector2f(0,0 + verticalOffset);
                rVA[currentVertex+1].texCoords = Vector2f(TILE_SIZE,0 + verticalOffset);
                rVA[currentVertex+2].texCoords = Vector2f(TILE_SIZE,TILE_SIZE + verticalOffset);
                rVA[currentVertex+3].texCoords = Vector2f(0,TILE_SIZE + verticalOffset);
                
            }
        
        //position ready for next vertices
            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }
    return TILE_SIZE;
    
}

