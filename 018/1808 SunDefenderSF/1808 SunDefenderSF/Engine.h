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
     Instantiate game objects
     ********/
    Enemy* enemies = nullptr; //pointer to a class
    Canon* player = nullptr;
    Enemy* enemiesDigital = nullptr;
    SunSegment sun;
    
    int m_NumEnemies = 4;
    int m_NumMountains = 13;
    int m_NumEnemiesAlive;
    
    int m_numCanons = 5;
    bool m_canonArray[13] = {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0}; //which mountains are the canons aligned with
    VertexArray m_mtnArrayDigital;

    /*   Vertex m_mtnArrayDigital[13] =
    {
        m_mtnArrayDigital[0].position = Vector2f(45, 400),
        m_mtnArrayDigital[1].position = Vector2f(125, 300),
        m_mtnArrayDigital[2].position = Vector2f(190, 400),
        m_mtnArrayDigital[3].position = Vector2f(275, 350),
        m_mtnArrayDigital[4].position = Vector2f(355, 400),
        m_mtnArrayDigital[5].position = Vector2f(460, 275),
        m_mtnArrayDigital[6].position = Vector2f(530, 350),
        m_mtnArrayDigital[7].position = Vector2f(610, 300),
        m_mtnArrayDigital[8].position = Vector2f(700, 400),
        m_mtnArrayDigital[9].position = Vector2f(745, 325),
        m_mtnArrayDigital[10].position = Vector2f(855, 275),
        m_mtnArrayDigital[11].position = Vector2f(900, 325),
        m_mtnArrayDigital[12].position = Vector2f(960, 350),
    };//Digital version. Mountain peaks/valleys
*/
    bool m_Playing = true;  //CHANGE THIS TO FALSE WHEN I'VE CODED INPUT

    double m_CurrentTime;
    
    //input() handles overall game state. Character controls are handled in character classes.
    void m_Input();
    void m_Update(double currentTime);
    void m_Render();
    
public:
    Engine();
    void run();
    
};

#endif /* Engine_h */
