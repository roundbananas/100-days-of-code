//
//  CreatePlayer.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "Canon.h"
#include "BattleGround.h"

Canon* createPlayer(int numCanons, bool *canonArray)
{
    Canon* player = new Canon[numCanons];
    
    for (int j=0; j <sizeof(canonArray); j++)
    {
        if (canonArray[j])
        {
            for (int i = 0; i< numCanons; i++)
            {
                //calculate position
                int canonPosition = i;
                //calculate type
                int canonType = 0;  //eventually we may want to save canon types players have upgraded to, between levels.
                
                player[i].spawn(canonPosition, canonType, i);
            }
        }
    }
    
    
    return player;
}
