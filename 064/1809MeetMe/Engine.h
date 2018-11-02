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
#include "SevSeg.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>

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
    
    int m_RestartButtonPin = 2;
    int m_p1StartButtonPin = 2;
    int m_p2StartButtonPin = 2;
    int m_p3StartButtonPin = 2;
    int m_firstPotPin = 0; //NOTE: this refers to Analogue pin. We MUST use analogueRead() to tell arduino to read the Analogue pins. If we use digitalRead() we must include prefix 'A', as in A0 pin.
    int m_firstButtonPin = 3; //we'll use digital pins and digitalRead() for these.
    

    //setup LEDs for players/bullets
    float m_stripLengthArray[m_NumPlayers] = {90.0f, 90.0f, 90.0f}; //float because bullet position is calculated as float 
    int m_stripDataPinArray[m_NumPlayers] = {6, 8, 10};
    int m_stripClockPinArray[m_NumPlayers] = {7, 9, 11};

    Adafruit_DotStar m_PlayerLEDS1 = Adafruit_DotStar(m_stripLengthArray[0], m_stripDataPinArray[0], m_stripClockPinArray[0], DOTSTAR_BGR);
    Adafruit_DotStar m_PlayerLEDS2 = Adafruit_DotStar(m_stripLengthArray[1], m_stripDataPinArray[1], m_stripClockPinArray[1], DOTSTAR_BGR);
    Adafruit_DotStar m_PlayerLEDS3 = Adafruit_DotStar(m_stripLengthArray[2], m_stripDataPinArray[2], m_stripClockPinArray[2], DOTSTAR_BGR);

    Adafruit_DotStar m_PlayerLEDS[m_NumPlayers] = {m_PlayerLEDS1, m_PlayerLEDS2, m_PlayerLEDS3};


    //Common variables for all 7segment displays
    const static int m_NumDisplays = 3;
    bool m_ResistorsOnSegments = false; // 'false' means resistors are on digit pins
    byte m_HardwareConfig = COMMON_CATHODE; // See README.md for options
    bool m_UpdateWithDelays = false; // Default. Recommended
    bool m_LeadingZeros = false; // Use 'true' if you'd like to keep the leading zeros

    //Setup one 4-digit 7segment display for score display
    SevSeg m_ScoreDisplay;
    byte m_Score_NumDigits = 4;
    byte m_Score_DigitPins[4] = {28, 29, 30, 31};
    byte m_Score_7SegPins[8] = {32, 33, 34, 35, 36, 37, 38, 39};
    
     
    //Setup two 2-digit 7segment displays for the current and best #rounds display
    SevSeg m_CurrentRoundDisplay;
    byte m_CurrentRound_NumDigits = 2;
    byte m_CurrentRound_DigitPins[2] = {40, 41};
    byte m_CurrentRound_7SegPins[8] = {42, 43, 44, 45, 46, 47, 48, 49};
   
    SevSeg m_BestRoundsDisplay;
    byte m_BestRounds_NumDigits = 2;
    byte m_BestRounds_DigitPins[2] = {50, 51};
    byte m_BestRounds_7SegPins[8] = {52, 53, 22, 23, 24, 25, 26, 27};

    
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
    
    int m_Level;
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
    void StartNewGame();
    void loadLevel();


    int getExplodeStrip(int j);
    
  //  void addScore(int playerB, int playerA, float value);
   // int getScore(int player);
};
#endif
