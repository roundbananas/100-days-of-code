//
//  Engine.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>

#include "Engine.h"
#include "Timer.h"
#include "BattleGround.h"


//Constructor
Engine::Engine()
{
    //initialise stuff like score in here?
}

void Engine::run()
{
    Timer t; //in seconds
    
    delete[] enemies;         //delete any existing instance
    delete[] player;
    enemies = createPlatoon(m_NumEnemies, m_NumMountains);
    player = createPlayer(m_numCanons, m_mtnArray);
    
    while (true)
    {
        double currentTime = t.elapsed();
        
        m_Input();
        m_Update(currentTime);
        m_Render();
    }
}

