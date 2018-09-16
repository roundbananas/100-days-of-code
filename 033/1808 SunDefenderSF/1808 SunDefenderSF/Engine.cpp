//
//  Engine.cpp
//  1808SunDefender
//
//  Created by Carl Turner on 28/8/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

//#include <stdio.h>
#include <iostream> //for debugging
#include "Engine.h"
#include "Timer.h"
#include "BattleGround.h"
#include "ResourcePath.hpp"

//Constructor
Engine::Engine()
{
    /*******
     Initialise objects for display
     ********/
    //get screen resolution and create an SFML window and view
    Vector2f resolution;
   // resolution.x = VideoMode::getDesktopMode().width;
   // resolution.y = VideoMode::getDesktopMode().height;
    
    resolution.x = 1000;
    resolution.y = 1200;
    
    m_Window.create(VideoMode(resolution.x, resolution.y), "Sun Defender",Style::Resize);
    
    m_Window.setKeyRepeatEnabled(false); //If key repeat is enabled, you will receive repeated KeyPressed events while keeping a key pressed. If it is disabled, you will only get a single event when the key is pressed. I DISABLED this so player has to press button each time they want to shoot. Could enable to allow holding down button for rapid fire.
    
    //initialise full screen view
    m_MainView.setSize(resolution);
 //   m_HudView.reset(FloatRect(0,0,resolution.x, resolution.y));
    
    /*******
     Initialise objects for graphics
     ********/
     m_BackgroundTexture = TextureHolder::GetTexture(resourcePath() + "SunDefender_background-01.png");
    //associate sprite with the texture
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
    m_BackgroundSprite.setPosition(0, -100);
    
    
}

void Engine::run()
{
    Timer t; //in seconds
    double lastTime = 0; //variable to hold the time at end of last frame
    m_SM.playBGMenuMusic();
    
    while (m_Window.isOpen())
    {
        double currentTime = t.elapsed(); //t.elapsed() returns time the program has been running in seconds
        
        m_Input(currentTime);
        m_Update(currentTime, lastTime);
        m_Render();
        
        lastTime = currentTime;
    }
}

void Engine::loadLevel()
{
    //Update conditions for this level
    m_NumEnemies += 1; //add two enemies each level
    m_NumEnemiesAlive = m_NumEnemies;
    m_level++;
    
    //delete any existing instance
    delete[] player;
    delete[] enemies;
    delete[] mtnProjectiles;
    delete[] enemyLasers;
    
   //Spawn objects
    sun.spawn(Vector2f(380, -90)); //moved up 105px from where I thought it would be. ??
 
    //**The following functions must be called in order, because several of them initialise arrays that subsequent functions use**//
    
    player = createPlayer(m_numCanons, m_NumMountains, m_canonArrayDigital, m_FireRate, m_RechargeTime); //initialises m_canonArrayDigital


    enemies = createPlatoon(m_level, m_NumEnemies, m_NumMountains, m_mtnArrayDigital, m_LifeLostPerHit); //this also creates the mountains (initialises m_mtnArrayDigital)
    
    mtnProjectiles = createMtnProjectiles(m_numCanons, m_mtnArrayDigital, m_ProjectileTargetArray, m_mtnProjectilePosArray); //initialises m_ProjectileTargetArray and m_mtnProjectilePosArray.
    
    enemyLasers = createEnemyLasers(m_EnemyLaserArrayDigital, m_mtnArrayDigital); //initialises m_EnemyLaserArrayDigital
    
    m_Hud.setLevel(m_level);
    m_Hud.setScore(m_score);
    
}
