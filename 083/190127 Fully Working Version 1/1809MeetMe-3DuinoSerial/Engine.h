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
#include "ScoreController.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>
#include "FlasherStandAlone.h"

class Engine
{
  private:
  //these flags are used to prevent the program running code that doesn't need to be run every single loop.
  //This lets us minimise the loop duration and therefore effectively increase the refresh rate of the render(), including 7 segment displays, which need to refresh at ~10ms period to not flicker 
  bool m_IdleFlag = false;
  bool m_CountdownFlag = false;
  bool m_PlayingFlag = false;
  bool m_LevelUpFlag = false;
  bool m_GameOverFlag = false;
  
    //declare pointers to game object types
    Player* m_Players = nullptr;
    ButtonMom* m_Buttons = nullptr;
    ButtonMom* m_BoostButtons = nullptr;
    SlidePot* m_SlidePots = nullptr;
    Bullet* m_Bullets = nullptr;
    Explosion* m_Explosions = nullptr;

    ScoreController m_ScoreController;
  
    ButtonMom p1StartButton;
    ButtonMom p2StartButton;
    ButtonMom p3StartButton;
    ButtonMom m_RestartButton;

    //constants
    const static int m_NumPlayers = 3; //equals number of buttons and pots
    int m_NumBullets = m_NumPlayers; //number of bullets that we imagine might be in flight at any moment
    int m_NumExplosions = m_NumPlayers; //- 1; //equals number of players (or led strips) minus 1, because it takes two bullets (players) to make an explosion
    
    int m_RestartButtonPin = 34;
    int m_p1StartButtonPin = 34;
    int m_p2StartButtonPin = 34;
    int m_p3StartButtonPin = 34;
    int m_firstPotPin = 0; //NOTE: this refers to Analogue pin. We MUST use analogueRead() to tell arduino to read the Analogue pins. If we use digitalRead() we must include prefix 'A', as in A0 pin.
    int m_firstButtonPin = 28;
    int m_FirstBoostPin = 22;

    //Button LEDs
    //FlasherStandAlone(int pinNumber, long onDuration)
    FlasherStandAlone m_NewGameButtonLED;
    int m_NewGameButtonLedPin = 35;
    long m_NewGameButtonLedOnDuration = 800;

    FlasherStandAlone m_Player1ButtonLED;
    FlasherStandAlone m_Player2ButtonLED;
    FlasherStandAlone m_Player3ButtonLED;
    FlasherStandAlone m_PlayerButtonLeds[3] = {m_Player1ButtonLED, m_Player2ButtonLED, m_Player3ButtonLED}; //used to easily control all ButtonLEDs at once
    int m_PlayerButtonLedPins[3] = {31, 32, 33};
    long m_PlayerButtonLedOnDurations[3] = {500,500,500};

    FlasherStandAlone m_Player1BoostLED;
    FlasherStandAlone m_Player2BoostLED;
    FlasherStandAlone m_Player3BoostLED;
    FlasherStandAlone m_PlayerBoostLeds[3] ={m_Player1BoostLED, m_Player2BoostLED, m_Player3BoostLED};
    int m_PlayerBoostLedPins[3] = {25,26, 27};
    long m_PlayerBoostLedOnDurations[3] = {50,50,50}; //make these flash faster for an exciting effect! haha
    
    //setup LEDs for players/bullets
    float m_stripLengthArray[m_NumPlayers] = {130.0f, 130.0f, 130.0f}; //float because bullet position is calculated as float 
    int m_stripDataPinArray[m_NumPlayers] = {49, 51, 53};
    int m_stripClockPinArray[m_NumPlayers] = {43, 45, 47};

    Adafruit_DotStar m_PlayerLEDS1 = Adafruit_DotStar(m_stripLengthArray[0], m_stripDataPinArray[0], m_stripClockPinArray[0], DOTSTAR_BGR);
    Adafruit_DotStar m_PlayerLEDS2 = Adafruit_DotStar(m_stripLengthArray[1], m_stripDataPinArray[1], m_stripClockPinArray[1], DOTSTAR_BGR);
    Adafruit_DotStar m_PlayerLEDS3 = Adafruit_DotStar(m_stripLengthArray[2], m_stripDataPinArray[2], m_stripClockPinArray[2], DOTSTAR_BGR);

    Adafruit_DotStar m_PlayerLEDS[m_NumPlayers] = {m_PlayerLEDS1, m_PlayerLEDS2, m_PlayerLEDS3};

    //Game variables
    int m_NumPlayersReady = 0;
    int m_LoadedBullet;
    int m_CurrentExplosion;
    unsigned long m_LastExplosionStartedAt = 0;

    //3 seconds countdown. But +1 added to shift the countdown pixels up one pixel along the strip, 
    //because the first pixel is actually hidden in the physical structure.
    //so we'll also stop the countdown once it gets to 1, not 0.
    int m_CountDownDuration = 4; 
    int m_CountDownRemaining;
 
    Modes m_mode;
    unsigned long m_ModeStartedAt;
    unsigned long m_TimeoutLevelUp = 4000;
    
    int m_Level;
    int m_BestRounds = 0; //lowest number of levels players have reached 1000 points in (like a HiScore)
    bool m_NewBestRounds = false;
    unsigned long m_countDownStartedAt = 0;
    bool m_countDownStarted = false;

   // unsigned long m_CurrentTime;

    void m_Input(unsigned long t);
    void m_Update(unsigned long dt, unsigned long t);
    void m_Render(unsigned long t);

  public:
    Engine();
    void runEngine();
    void UpdateStrips(unsigned long currentTime);
    void StartNewGame();
    void loadLevel();


    int getExplodeStrip(int j);
    
  //  void addScore(int playerB, int playerA, float value);
   // int getScore(int player);
};
#endif
