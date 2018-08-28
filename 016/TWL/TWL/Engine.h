//
//  Engine.h
//  TWL
//
//  Created by Carl Turner on 24/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"

using namespace sf;

class Engine
{
private:
    //the texture holder
    TextureHolder th;
    
    //Instantiate Thomas and Bob
    Thomas m_Thomas;
    Bob m_Bob;
    
    const int TILE_SIZE = 50; //pixel size of tiles in sprite sheet
    const int VERTS_IN_QUAD = 4; //number of vertices in a quad. Makes manipulation of vertexArray less error prone
    
    //gravity force pushing characters down
    const int GRAVITY = 300;
    
    //A RenderWindow
    RenderWindow m_Window;
    
    //the main views (SFML objects)
    View m_MainView; //full screen
    View m_LeftView; //for split screen
    View m_RightView; //for split screen
    
    //Three views for background
    View m_BGMainView;
    View m_BGLeftView;
    View m_BGRightView;
    
    View m_HudView;
    
    //Declare a sprite and texture for background
    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;
    
    //is game currently playing?
    bool m_Playing = false;
    
    //Is character 1 or 2 the current focus?
    bool m_Character1 = true; //thomas = true, bob = false
    
    //Start in full screen mode
    bool m_SplitScreen = false;
    
    //how much time is left in current level
    float m_TimeRemaining = 10;
    Time m_GameTimeTotal;
    
    //is it time for a new/first level?
    bool m_NewLevelRequired = true;
    
    //private functions for internal use only
    void input(); //this only handle quiting, split screen switching etc. Character controls are handled in character classes.
    void update(float dtAsSeconds);
    void draw();
    
public:
    //Enginer constructor
    Engine();
    
    //run will call all the private functions
    void run();
    
};

#endif /* Engine_h */
