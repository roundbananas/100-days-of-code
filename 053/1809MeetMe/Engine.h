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
#include "SevenSegDisplay.h"
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

    ScoreController m_ScoreController;
  
    ButtonMom p1StartButton;
    ButtonMom p2StartButton;
    ButtonMom p3StartButton;
    ButtonMom m_RestartButton;

    //constants
    const static int m_NumPlayers = 3; //equals number of buttons and pots
    int m_NumBullets = m_NumPlayers; //number of bullets that we imagine might be in flight at any moment
    int m_NumExplosions = m_NumPlayers - 1; //equals number of players (or led strips) minus 1, because it takes two bullets (players) to make an explosion
    
    int m_RestartButtonPin = 22;
    int m_p1StartButtonPin = 2;
    int m_p2StartButtonPin = 2;
    int m_p3StartButtonPin = 2;
    int m_firstPotPin = 0; //NOTE: this refers to Analogue pin. We MUST use analogueRead() to tell arduino to read the Analogue pins. If we use digitalRead() we must include prefix 'A', as in A0 pin.
    int m_firstButtonPin = 3; //we'll use digital pins and digitalRead() for these.
    float m_BulletSpeedFactor = 0.01f; //fudge factor to allow enough sensivity on pot interface, while making the bullet fly at a reasonable speed.

    //setup LEDs for players/bullets
    float m_stripLengthArray[m_NumPlayers] = {25.0f, 25.0f, 25.0f}; //float because bullet position is calculated as float 
    int m_stripDataPinArray[m_NumPlayers] = {6, 8, 10};
    int m_stripClockPinArray[m_NumPlayers] = {7, 9, 11};

    Adafruit_DotStar m_PlayerLEDS1 = Adafruit_DotStar(m_stripLengthArray[0], m_stripDataPinArray[0], m_stripClockPinArray[0], DOTSTAR_BGR);
    Adafruit_DotStar m_PlayerLEDS2 = Adafruit_DotStar(m_stripLengthArray[1], m_stripDataPinArray[1], m_stripClockPinArray[1], DOTSTAR_BGR);
    Adafruit_DotStar m_PlayerLEDS3 = Adafruit_DotStar(m_stripLengthArray[2], m_stripDataPinArray[2], m_stripClockPinArray[2], DOTSTAR_BGR);

    Adafruit_DotStar m_PlayerLEDS[m_NumPlayers] = {m_PlayerLEDS1, m_PlayerLEDS2, m_PlayerLEDS3};

    //setup LEDs for score display
    int m_ScoreStripLength = 25;  //how many LEDs in the strip that displays score? int type because score is calculated/displayed as int
    int m_ScoreStripDataPin = 24;
    int m_ScoreStripClockPin = 25;
    Adafruit_DotStar m_ScoreLEDS = Adafruit_DotStar(m_ScoreStripLength, m_ScoreStripDataPin, m_ScoreStripClockPin, DOTSTAR_BGR);

    //Setup two 7segment displays for level display, 8 pins each
    byte m_Segment1Pins[8] = {30, 31, 32, 33, 34, 35, 36, 37};
    byte m_Segment2Pins[8] = {40, 41, 42, 43, 44, 45, 46, 47};
    byte m_SegmentPins[2] = {m_Segment1Pins, m_Segment2Pins};
    
    SevenSegDisplay m_LevelDisplay1;
    SevenSegDisplay m_LevelDisplay2;
    SevenSegDisplay m_LevelDisplay[2] = {m_LevelDisplay1, m_LevelDisplay2};

    // variables to manage hud
    int m_FramesSinceLastHUDUpdate = 0;
    int m_TargetFramesPerHUDUpdate = 10;
    
    //Game variables
    int m_NumPlayersReady = 0;
    int m_LoadedBullet;
    int m_CurrentExplosion;
    unsigned long m_LastExplosionStartedAt = 0;

    int m_CountDownRemaining;
 
    Modes m_mode;
    unsigned long m_ModeStartedAt;
    unsigned long m_TimeoutLevelUp = 4000;
    
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

    int firstDigit(int level);
    int secondDigit (int level);
  //  void addScore(int playerB, int playerA, float value);
   // int getScore(int player);
};
#endif