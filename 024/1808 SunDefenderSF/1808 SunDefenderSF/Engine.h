//
//  Engine.h
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

#include "Enemy.h"
#include "Canon.h"
#include "SunSegment.h"
#include "EnemyLaser.h"
#include "GameMode.h"

using namespace sf;

class Engine
{
private:
    /*******
     Declare objects for graphics and display
     ********/
    TextureHolder th;
    
    RenderWindow m_Window; //the application window
    
    //the views ("cameras") (SFML objects)
    View m_MainView;
    View m_HudView;
    
    //A sprite and texture for background
    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;
    
    //Sun will need to be split into separate segments eventually
    Sprite m_SunSprite;
    Texture m_SunTexture;
    Sprite m_CanonSprite;
    Texture m_CanonTexture;
    
    /*******
     Declare game objects
     ********/
    Enemy* enemies = nullptr; //pointer to a class
    Canon* player = nullptr;
    EnemyLaser* enemyLasers = nullptr;
    SunSegment sun;
    
    int m_NumEnemies = 5;
    int m_NumMountains = 13;
    int m_NumEnemiesAlive;
    int m_NumEnemyLasers = 5;
    int m_numCanons = 5;
    int m_NumSunSegments = 6;

    VertexArray m_mtnArrayDigital;
    VertexArray m_EnemyLaserArrayDigital;
    VertexArray m_canonArrayDigital;        //use to hold positions of buttons. Use another bool canonInPlace array to designate if a canon is at that position or not.
 
    
   // bool m_Playing = true;  //CHANGE THIS TO FALSE WHEN I'VE CODED INPUT
    GameMode mode = GameMode::IDLE;

    double m_CurrentTime;
    
    //input() handles overall game state. Character controls are handled in character classes.
    void m_Input();
    void m_Update(double currentTime, double lastTime);
    void m_Render();
    
public:
    Engine();
    void run();
    void loadLevel();
};

#endif /* Engine_h */
