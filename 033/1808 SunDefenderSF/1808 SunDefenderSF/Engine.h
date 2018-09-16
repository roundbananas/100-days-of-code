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
#include "CanonProjectile.h"
#include "MtnProjectiles.h"
#include "Hud.h"
#include "SoundManager.h"

using namespace sf;

class Engine
{
private:
    /*******
     Declare objects for graphics and display
     ********/
    TextureHolder th;
    
    //Hud object
    Hud m_Hud;
    int m_FramesSinceLastHUDUpdate = 0;
    int m_TargetFramesPerHUDUpdate = 500;
    
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
    
    //sound manager
    SoundManager m_SM;
    
    /*******
     Declare game objects
     ********/
    Enemy* enemies = nullptr; //pointer to a class
    Canon* player = nullptr;
    MtnProjectiles* mtnProjectiles = nullptr;
    EnemyLaser* enemyLasers = nullptr;
    SunSegment sun;
    
    //Constants
    int m_NumMountains = 13;
    int m_NumEnemyLasers = 5;
    int m_numCanons = 5;
    int m_NumSunSegments = 6;
    
    //these values change with level
    int m_NumEnemies;
    int m_FireRate;
    double m_RechargeTime;
    int m_LifeLostPerHit;

    //keep track of how many enemies remain at all times.
    int m_NumEnemiesAlive;
    
    VertexArray m_mtnArrayDigital; //holds mountain peak positions
    VertexArray m_EnemyLaserArrayDigital; //holds enemy lasers sprite positions.
    VertexArray m_canonArrayDigital;        //holds button sprite positions.
    VertexArray m_mtnProjectilePosArray; //holds mtnProjectile sprite positions
    VertexArray m_ProjectileTargetArray; // used to set targets for projectiles, and as reference for triggering mtnProjectiles to be drawn

        //Should the following go in Engine::loadLevel()?
        int static const m_projectileArraySize = 100; //how many projectiles, maximum, do we imagine we'll want inflight simultaneously?
        CanonProjectile canon0Projectiles[m_projectileArraySize]; //50 projectiles inflight per canon at any one time should be more than enough
        CanonProjectile canon1Projectiles[m_projectileArraySize];
        CanonProjectile canon2Projectiles[m_projectileArraySize];
        CanonProjectile canon3Projectiles[m_projectileArraySize];
        CanonProjectile canon4Projectiles[m_projectileArraySize];
    
        int m_currentProjectileCanon0 = 0;    //increment this each time we shoot, so the shot projectile is not respawned before it does its thing.
        int m_currentProjectileCanon1 = 0;
        int m_currentProjectileCanon2 = 0;
        int m_currentProjectileCanon3 = 0;
        int m_currentProjectileCanon4 = 0;

    
    GameMode mode = GameMode::IDLE;
    int m_score = 0;
    int m_level = 0;
    
    double m_CurrentTime;
    
    //input() handles overall game state. Character controls are handled in character classes.
    void m_Input(double currentTime);
    void m_Update(double currentTime, double lastTime);
    void m_Render();
    
public:
    Engine();
    void run();
    void loadLevel();
};

#endif /* Engine_h */
