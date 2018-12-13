//
//  Engine.h
//
//  Created by Carl Turner on 18/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!
 /*** CONNECTIONS ****/
 /* Mega pin     Logic Level Shifter    ESP8266 (Wemos mini)
  * TX (1)       HV-TX0       LV-TXI    RX
  * RX (0)       -            -         TX
  */

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
#include "FlasherStandAlone.h"	//for button leds

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

    float m_stripLengthArray[m_NumPlayers] = {90.0f, 90.0f, 90.0f}; //How many pixels in LED Strips? Float type because bullet position is calculated as float 
    
    int m_RestartButtonPin = 9;
    int m_p1StartButtonPin = 9;
    int m_p2StartButtonPin = 9;
    int m_p3StartButtonPin = 9;
    int m_firstPotPin = 0; //NOTE: this refers to Analogue pin. We MUST use analogueRead() to tell arduino to read the Analogue pins. If we use digitalRead() we must include prefix 'A', as in A0 pin.
    int m_firstButtonPin = 13;
    int m_FirstBoostPin = 3;

    //Button LEDs
    //FlasherStandAlone(int pinNumber, long onDuration)
    FlasherStandAlone m_NewGameButtonLED;
    int m_NewGameButtonLedPin = 10;
    long m_NewGameButtonLedOnDuration = 800;

    FlasherStandAlone m_Player1ButtonLED;
    FlasherStandAlone m_Player2ButtonLED;
    FlasherStandAlone m_Player3ButtonLED;
    FlasherStandAlone m_PlayerButtonLeds[3] = {m_Player1ButtonLED, m_Player2ButtonLED, m_Player3ButtonLED}; //used to easily control all ButtonLEDs at once
    int m_PlayerButtonLedPins[3] = {16, 17, 18};
    long m_PlayerButtonLedOnDurations[3] = {500,500,500};

    FlasherStandAlone m_Player1BoostLED;
    FlasherStandAlone m_Player2BoostLED;
    FlasherStandAlone m_Player3BoostLED;
    FlasherStandAlone m_PlayerBoostLeds[3] ={m_Player1BoostLED, m_Player2BoostLED, m_Player3BoostLED};
    int m_PlayerBoostLedPins[3] = {6, 7, 8};
    long m_PlayerBoostLedOnDurations[3] = {50,50,50}; //make these flash faster for an exciting effect! haha
    
    
    //Common variables for all 7segment displays
    const static int m_NumDisplays = 3;
   // byte m_SegPins[8] = {37, 39, 41, 43, 45, 47, 49, 51};     
    bool m_ResistorsOnSegments = false; // 'false' means resistors are on digit pins
    bool m_UpdateWithDelays = false; // Default. Recommended
    bool m_LeadingZeros = false; // Use 'true' if you'd like to keep the leading zeros

    //Setup one 4-digit 7segment display for score display
    SevSeg m_ScoreDisplay;
    byte m_Score_HardwareConfig = COMMON_CATHODE; // See README.md for options
    byte m_Score_NumDigits = 4;
    byte m_Score_DigitPins[4] = {25, 27, 29, 31};
    byte m_Score_SegmentPins[8] = {37, 39, 41, 43, 45, 47, 49, 51}; //NOTE DP pin is not connected. We don't need DP.

     
    //Setup two 1-digit 7segment displays for the current and best #rounds display
    SevSeg m_CurrentRoundDisplay;
    byte m_CurrentRound_Score_HardwareConfig = COMMON_ANODE;    
    byte m_CurrentRound_NumDigits = 1;
    byte m_CurrentRound_DigitPins[1] = {33};
    byte m_CurrentRound_SegmentPins[8] = {26, 28, 30, 32, 34, 36, 38, 40};

   
    SevSeg m_BestRoundsDisplay;
    byte m_BestRounds_Score_HardwareConfig = COMMON_ANODE;
    byte m_BestRounds_NumDigits = 1;
    byte m_BestRounds_DigitPins[1] = {35};
    byte m_BestRounds_SegmentPins[8] = {42, 44, 46, 48, 50, 52, 53};

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

    unsigned long m_LastTime = 0;
  //  unsigned long m_7SegRefreshRate = 50; //ms

    //Array to hold data to send to ESP, which will update and render LED strips.
     /* byte m_DataToSend[m_NumPlayers][10];
      *	[m_NumPlayers] holds strip number - possible value of 0, 1, 2...up to m_NumPlayers-1
	  * [10] holds mode, on/off and position data for BulletA, BulletB and Explosion
	  * Note this means we have 3 array spots for holding game mode, but we only use one. 
	  * It just seems easier this way, rather than creating a whole new type of data and 
	  * managing sending that as well.
	  * 
	  * Array index   Relates to      Possible values
	  * [i][0]		  Game Mode       0, 1, 2, 3, 4 (for IDLE, COUNTDOWN, PLAYING, LEVELLING_UP, GAME_OVER)
	  * [i][1]        BulletA on/off  0, 1
	  * [i][2]        BulletB on/off  0, 1
	  * [i][3]        Expl'n on/off   0, 1
	  * [i][4]        BulletAHead     0 - 90 (ie a location on a strip of, say, length 90)
	  * [i][5]        BulletATail     0 - 90 
	  * [i][6]        BulletBHead     0 - 90 
	  * [i][7]        BulletBTail     0 - 90 
	  * [i][8]        Expl'nHead      0 - 90 
	  * [i][9]        Expl'nTail      0 - 90 
	  * 
	  * See Codes.h for more info on how I'm handling data for serial comms.
	  */
    byte m_DataToSend[m_NumPlayers][10] = {};	//initialise to 0

    void m_Input(unsigned long t);
    void m_Update(unsigned long dt, unsigned long t);
    void m_Render(unsigned long t);
    void m_SendDataToESP();

  public:
    Engine();
    void runEngine();
    void UpdateStrips(unsigned long currentTime);
	void UpdateArray();
    void StartNewGame();
    void loadLevel();


    int getExplodeStrip(int j);

};
#endif
