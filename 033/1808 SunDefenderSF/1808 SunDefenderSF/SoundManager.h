//
//  SoundManager.h
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 16/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#ifndef SoundManager_h
#define SoundManager_h

#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
private:
    //buffers
    SoundBuffer m_CanonFireBuffer;
    SoundBuffer m_CanonNotChargedBuffer;
    
    SoundBuffer m_EnemyMoveBuffer;
    SoundBuffer m_EnemyLaserBuffer;
    SoundBuffer m_EnemyExplosionBuffer;
    
    SoundBuffer m_SunPartialDeathBuffer;
    SoundBuffer m_SunTotalDeathBuffer;
    
    SoundBuffer m_PowerUpBuffer;
    
    SoundBuffer m_BGPlayMusicBuffer;
    SoundBuffer m_BGMenuMusicBuffer;
    
    //the sounds
    Sound m_CanonFireSound;
    Sound m_CanonNotChargedSound;
    
    Sound m_EnemyMoveSound;
    Sound m_EnemyLaserSound;
    Sound m_EnemyExplosionSound;
    
    Sound m_SunPartialDeathSound;
    Sound m_SunTotalDeathSound;
    
    Sound m_PowerUpSound;
    
    Sound m_BGPlayMusic;
    Sound m_BGMenuMusic;
    
public:
    SoundManager();
    
    void playFire();
    void playNotCharged();
    
    void playEnemyMove();
    void playEnemyLaser();
    void stopEnemyLaser();
    void playEnemyExplosion();
    
    void playSunPartialDeath();
    void playSunTotalDeath();
    
    void playPowerUp();
    
    void playBGPlayingMusic();
    void stopBGPlayingMusic();
    
    void playBGMenuMusic();
    void stopBGMenuMusic();
    
    
};

#endif /* SoundManager_h */
