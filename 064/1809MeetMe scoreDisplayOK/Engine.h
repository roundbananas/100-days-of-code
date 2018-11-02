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
#include "SevSeg.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>

class Engine
{
  private:
  SevSeg m_SevSeg;
  byte numDigits = 4;
  byte digitPins[4] = {28, 29, 30, 31};
  byte segmentPins[8] = {32, 33, 34, 35, 36, 37, 38, 39};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros

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
    
    int m_RestartButtonPin = 22;
    int m_p1StartButtonPin = 2;
    int m_p2StartButtonPin = 2;
    int m_p3StartButtonPin = 2;
    int m_firstPotPin = 0; //NOTE: this refers to Analogue pin. We MUST use analogueRead() to tell arduino to read the Analogue pins. If we use digitalRead() we must include prefix 'A', as in A0 pin.
    int m_firstButtonPin = 3; //we'll use digital pins and digitalRead() for these.
    float m_BulletSpeedFactor = 0.01f; //fudge factor to allow enough sensivity on pot interface, while making the bullet fly at a reasonable speed.

    //setup LEDs for players/bullets
    float m_stripLengthArray[m_NumPlayers] = {90.0f, 90.0f, 90.0f}; //float because bullet position is calculated as float 
    int m_stripDataPinArray[m_NumPlayers] = {6, 8, 10};
    int m_stripClockPinArray[m_NumPlayers] = {7, 9, 11};

    Adafruit_DotStar m_PlayerLEDS1 = Adafruit_DotStar(m_stripLengthArray[0], m_stripDataPinArray[0], m_stripClockPinArray[0], DOTSTAR_BGR);
    Adafruit_DotStar m_PlayerLEDS2 = Adafruit_DotStar(m_stripLengthArray[1], m_stripDataPinArray[1], m_stripClockPinArray[1], DOTSTAR_BGR);
    Adafruit_DotStar m_PlayerLEDS3 = Adafruit_DotStar(m_stripLengthArray[2], m_stripDataPinArray[2], m_stripClockPinArray[2], DOTSTAR_BGR);

    Adafruit_DotStar m_PlayerLEDS[m_NumPlayers] = {m_PlayerLEDS1, m_PlayerLEDS2, m_PlayerLEDS3};

    //Setup one 4-digit 7segment display for score display
    byte m_Points_NumDigits = 4;
    byte m_Points_DigitPins[4] = {28, 29, 30, 31};
    byte m_Points_7SegPins[8] = {32, 33, 34, 35, 36, 37, 38, 39};
   // SevenSegDisplay m_PointsDisplay;
     
    //Setup two 2-digit 7segment displays for the current and best #rounds display
    byte m_CurrentRound_NumDigits = 2;
    byte m_CurrentRound_DigitPins[2] = {40, 41};
    byte m_CurrentRound_7SegPins[8] = {42, 43, 44, 45, 46, 47, 48, 49};
 //   SevenSegDisplay m_CurrentRoundDisplay;
    
    byte m_BestRounds_NumDigits = 2;
    byte m_BestRounds_DigitPins[2] = {50, 51};
    byte m_BestRounds_7SegPins[8] = {52, 53, 54, 55, 56, 57, 58, 59};
 //   SevenSegDisplay m_BestRoundsDisplay;

    byte m_7SegDigits[3] = {m_Points_NumDigits, m_CurrentRound_NumDigits, m_BestRounds_NumDigits};
    byte m_7SegDigitPins[3] = {m_Points_DigitPins, m_CurrentRound_DigitPins, m_BestRounds_DigitPins};
    byte m_7SegPins[3] = {m_Points_7SegPins, m_CurrentRound_7SegPins, m_BestRounds_7SegPins};
 //   SevenSegDisplay m_7SegDisplays[3] = {m_PointsDisplay, m_CurrentRoundDisplay, m_BestRoundsDisplay};

    // variables to manage hud
    int m_FramesSinceLastHUDUpdate = 0;
    int m_TargetFramesPerHUDUpdate = 10;
    
    //Game variables
    int m_NumPlayersReady = 0;
    int m_LoadedBullet;
    int m_CurrentExplosion;
    unsigned long m_LastExplosionStartedAt = 0;

    int m_CountDownDuration = 3; //3 seconds
    int m_CountDownRemaining;
 
    Modes m_mode;
    unsigned long m_ModeStartedAt;
    unsigned long m_TimeoutLevelUp = 4000;
    
    int m_Level = 0;
    int m_BestRounds = 0; //lowest number of levels players have reached 1000 points in (like a HiScore)
    bool m_NewBestRounds = false;
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

    void refreshSevSeg();
    
  //  void addScore(int playerB, int playerA, float value);
   // int getScore(int player);
};
#endif
