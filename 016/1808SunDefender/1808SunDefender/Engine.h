//
//  Engine.h
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

#include "Enemy.h"
#include "Canon.h"

class Engine
{
private:

    Enemy* enemies = nullptr; //pointer to a class
    Canon* player = nullptr;
    
    int m_NumEnemies = 2;
    int m_NumMountains = 10;
    int m_NumEnemiesAlive;
    
    int m_numCanons = 5;
    int m_mtnArray[10] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    
    bool m_Playing = true;  //CHANGE THIS TO FALSE WHEN I'VE CODED INPUT

    double m_CurrentTime;
    
    //input() only handles state machine. Character controls are handled in character classes.
    void m_Input();
    void m_Update(double currentTime);
    void m_Render();
    
public:
    Engine();
    void run();
    
};

#endif /* Engine_h */
