//
//  CreateHorde.cpp
//  Zombies
//
//  Created by Carl Turner on 21/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include "ZombieArena.h"
#include "zombie.h"

Zombie* createHorde(int numZombies, IntRect arena) //this line is called a function signature. This function must return TO a pointer to a zombie object. numZombies = number of zombies we require in this horde
{
    Zombie* zombies = new Zombie[numZombies]; //Once we're done creating the horde, we'll return the array. When we return an array, we actually returning the address of the first element of the array (which is the same as a pointer). SO, we can declare a pointer to the array Zombie[numZombies]. new keyword allocates memory on the heap.
    
    const int WALL_THICKNESS = 50;
    
    int maxY = arena.height - WALL_THICKNESS;   //20 is to stop zombies appear on top of walls
    int minY = arena.top + WALL_THICKNESS;
    int maxX = arena.width - WALL_THICKNESS;
    int minX = arena.left + WALL_THICKNESS;
 
    for (int i = 0; i < numZombies; i++) //we create a zombie for each element in the array
    {
        //which side of the outside edge of arena should the zombie spawn
        srand((int)time(0) * i);
        int side = (rand() % 4);
        float x, y;
        
        switch (side)
        {
            case 0:
                //left
                x = minX;
                y = (rand() % maxY) + minY;
                break;
            
            case 1:
                //right
                x = maxX;
                y = (rand() % maxY) + minY;
                break;
                
            case 2:
                //top
                x = (rand() % maxX) + minX;
                y = minY;
                break;
                
            case 3:
                //bottom
                x = (rand() % maxX) + minX;
                y = maxY;
                break;
        }
        
        //bloater, crawler or runner
        srand((int)time(0) * i * 2); //generate random number btwn 0 and 2
        int type = (rand() % 3);
        
        //spawn new zombie into array
        zombies[i].spawn(x, y, type, i); //starting location, type. i = seed for random number
    } //for() loop repeats once for each zombie in the array
    return zombies;
}
