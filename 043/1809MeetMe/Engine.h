//
//  Engine.h
//
//  Created by Carl Turner on 18/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#ifndef Engine_h
#define Engine_h

#include "Player.h"
#include "Bullet.h"
#include "ButtonMom.h"
#include "SlidePot.h"
#include "Modes.h"
#include "Arduino.h"
#include "Explosion.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>

class Engine
{
  private:
    //declare pointers to game object types
    Player* m_Players = nullptr;
    ButtonMom* m_Buttons = nullptr;
    SlidePot* m_SlidePots = nullptr;
    Bullet* m_Bullets = nullptr;
    Explosion* m_Explosions = nullptr;
    
    ButtonMom p1StartButton;
    ButtonMom p2StartButton;
    ButtonMom m_RestartButton;

    //constants
    const static int m_NumPlayers = 2; //equals number of buttons and pots
    int m_NumExplosions = m_NumPlayers - 1; //equals number of players (or led strips) minus 1, because it takes two bullets (players) to make an explosion
    int m_RestartButtonPin = 26;
    int m_p1StartButtonPin = 2;
    int m_p2StartButtonPin = 2;
    int m_firstPotPin = 0; //NOTE: this refers to Analogue pin. We MUST use analogueRead() to tell arduino to read the Analogue pins. If we use digitalRead() we must include prefix 'A', as in A0 pin.
    int m_firstButtonPin = 4; //we'll use digital pins and digitalRead() for these.
    int m_NumBullets = 2; //number of bullets that we imagine might be in flight at any moment
    float m_BulletSpeedFactor = 0.002f; //fudge factor to allow enough sensivity on pot interface, while making the bullet fly at a reasonable speed.

    int m_stripLengthArray[m_NumPlayers] = {25, 25}; 
    int m_stripDataPinArray[m_NumPlayers] = {6, 8};
    int m_stripClockPinArray[m_NumPlayers] = {7, 9};

    int m_FramesSinceLastHUDUpdate = 0;
    int m_TargetFramesPerHUDUpdate = 10;

    Adafruit_DotStar m_PlayerLEDS1 = Adafruit_DotStar(m_stripLengthArray[0], m_stripDataPinArray[0], m_stripClockPinArray[0], DOTSTAR_BRG);
    Adafruit_DotStar m_PlayerLEDS2 = Adafruit_DotStar(m_stripLengthArray[1], m_stripDataPinArray[1], m_stripClockPinArray[1], DOTSTAR_BRG);

    Adafruit_DotStar m_PlayerLEDS[m_NumPlayers] = {m_PlayerLEDS1, m_PlayerLEDS2};

    
    //Game variables
    int m_NumPlayersReady = 0;
    int m_LoadedBullet = 1;
    int m_CurrentExplosion = 0;
    Modes m_mode;
    int m_Level = 0;
    int m_Score[m_NumPlayers];
    unsigned long m_countDownStartedAt = 0;
     bool m_countDownStarted = false;

   // unsigned long m_CurrentTime;

    void m_Input(unsigned long t);
    void m_Update(unsigned long dt, unsigned long t);
    void m_Render();

  public:
    Engine();
    void runEngine();
    void loadLevel();
    
    int getExplodeStrip(int j);
};
#endif
