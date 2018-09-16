//
//  SoundManager.cpp
//  1808 SunDefenderSF
//
//  Created by Carl Turner on 16/9/18.
//  Copyright © 2018 Carl Turner. All rights reserved.
//

#include "SoundManager.h"
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"

using namespace sf;

SoundManager::SoundManager()
{
    //load sounds into buffers
    m_CanonFireBuffer.loadFromFile(resourcePath() + "raZap03.wav");
    m_CanonNotChargedBuffer.loadFromFile(resourcePath() + "raCrash.wav");
    
    m_EnemyMoveBuffer.loadFromFile(resourcePath() + "raDrop.wav");
    m_EnemyLaserBuffer.loadFromFile(resourcePath() + "raAccelerationLowAmped.wav");
    m_EnemyExplosionBuffer.loadFromFile(resourcePath() + "raHit02.wav");
    
    m_SunPartialDeathBuffer.loadFromFile(resourcePath() + "raBoom04.wav");
    m_SunTotalDeathBuffer.loadFromFile(resourcePath() + "raExplosion03.wav");
    
    m_PowerUpBuffer.loadFromFile(resourcePath() + "raConfirm01.wav");
    
    m_BGPlayMusicBuffer.loadFromFile(resourcePath() + "strange1_loop.wav");
    m_BGMenuMusicBuffer.loadFromFile(resourcePath() + "RaGameplayLoop.wav");
    
    //associate sounds with buffers
    m_CanonFireSound.setBuffer(m_CanonFireBuffer);
    m_CanonNotChargedSound.setBuffer(m_CanonNotChargedBuffer);
    
    m_EnemyMoveSound.setBuffer(m_EnemyMoveBuffer);
    m_EnemyLaserSound.setBuffer(m_EnemyLaserBuffer);
    m_EnemyExplosionSound.setBuffer(m_EnemyExplosionBuffer);
    
    m_SunPartialDeathSound.setBuffer(m_SunPartialDeathBuffer);
    m_SunTotalDeathSound.setBuffer(m_SunTotalDeathBuffer);
    
    m_PowerUpSound.setBuffer(m_PowerUpBuffer);
    m_BGPlayMusic.setBuffer(m_BGPlayMusicBuffer);
    m_BGMenuMusic.setBuffer(m_BGMenuMusicBuffer);
    
    //loop BG music when it's played, as well as laser
    m_EnemyLaserSound.setLoop(true);
    m_BGPlayMusic.setLoop(true);
    m_BGMenuMusic.setLoop(true);
    
    m_CanonNotChargedSound.setVolume(40.0);
    
    m_EnemyLaserSound.setVolume(25.0);
    m_EnemyMoveSound.setVolume(50.0);
    
    m_BGPlayMusic.setVolume(25.0);
    m_BGMenuMusic.setVolume(20.0);
}

void SoundManager::playFire()
{
    m_CanonFireSound.play();
}
void SoundManager::playNotCharged()
{
    m_CanonNotChargedSound.play();
}
void SoundManager::playEnemyMove()
{
    m_EnemyMoveSound.play();
}
void SoundManager::playEnemyLaser()
{
    m_EnemyLaserSound.play();
}
void SoundManager::stopEnemyLaser()
{
    m_EnemyLaserSound.stop();
}

void SoundManager::playEnemyExplosion()
{
    m_EnemyExplosionSound.play();
}
void SoundManager::playSunPartialDeath()
{
    m_SunPartialDeathSound.play();
}
void SoundManager::playSunTotalDeath()
{
    m_SunTotalDeathSound.play();
}
void SoundManager::playPowerUp()
{
    m_PowerUpSound.play();
}
void SoundManager::playBGPlayingMusic()
{
    m_BGPlayMusic.play();
}
void SoundManager::stopBGPlayingMusic()
{
    m_BGPlayMusic.stop();
}
void SoundManager::playBGMenuMusic()
{
    m_BGMenuMusic.play();
}
void SoundManager::stopBGMenuMusic()
{
    m_BGMenuMusic.stop();
}
