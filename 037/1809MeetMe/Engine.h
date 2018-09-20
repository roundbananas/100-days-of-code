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
#include <Adafruit_DotStar.h>
#include <SPI.h>

class Engine
{
  private:
    //declare pointers to game object types
    Player* m_Players = nullptr;
    ButtonMom* m_Buttons = nullptr;
    SlidePot* m_SlidePots = nullptr;
    ButtonMom m_RestartButton;

    Bullet* m_Bullets = nullptr;

    //declare displays
    int m_NumPixels1 = 30;
    int m_DataPin1 = 6;
    int m_ClockPin1 = 7;
    Adafruit_DotStar m_Player1LEDS = Adafruit_DotStar(m_NumPixels1, m_DataPin1, m_ClockPin1, DOTSTAR_BRG);

    int m_NumPixels2 = 30;
    int m_DataPin2 = 8;
    int m_ClockPin2 = 9;
    Adafruit_DotStar m_Player2LEDS = Adafruit_DotStar(m_NumPixels1, m_DataPin1, m_ClockPin1, DOTSTAR_BRG);

    //constants
    const static int m_NumPlayers = 2; //equals number of buttons and pots
    int m_RestartButtonPin = 3;
    int m_firstPotPin = 0; //NOTE: this refers to Analogue pin. We MUST use analogueRead() to tell arduino to read the Analogue pins. If we use digitalRead() we must include prefix 'A', as in A0 pin.
    int m_firstButtonPin = 4; //we'll use digital pins and digitalRead() for these.
    int m_NumBullets = 10; //number of bullets that we imagine might be in flight at any moment

    //Game variables
    int m_NumPlayersReady = 0;
    int m_LoadedBullet = 0;
    Modes m_mode = Modes::IDLE_MODE;
    int m_Level = 0;
    int m_Score[m_NumPlayers];

   // unsigned long m_CurrentTime;

    void m_Input(unsigned long t);
    void m_Update(unsigned long dt, unsigned long t);
    void m_Render();

  public:
    Engine();
    void runEngine();
    void loadLevel();
};
#endif
