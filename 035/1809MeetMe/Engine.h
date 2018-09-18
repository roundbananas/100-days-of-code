//
//  Engine.h
//
//  Created by Carl Turner on 18/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#ifndef Engine_h
#define Engine_h

#include "Player1.h"
#include "Bullet.h"
#include "ButtonMom.h"
#include "SlidePot.h"
#include "Modes.h"
#include "Arduino.h"

class Engine
{
  private:
    //declare pointers to player types.
    Player1* m_Player1 = nullptr;
    Player1* m_Player2 = nullptr;

    //declare pointers to game object types
    Bullet* m_Bullets = nullptr;
    ButtonMom* m_Buttons = nullptr;
    SlidePot* m_SlidePots = nullptr;

    //constants
    int m_NumBullets; //number of bullets that we imagine might be in flight at any moment
    int m_NumPlayers; //equals number of buttons and pots
    
    Modes m_mode = Modes::IDLE_MODE;
    int m_Level = 0;

    unsigned long m_CurrentTime;

    void m_Input(unsigned long dt);
    void m_Update(unsigned long t);
    void m_Render();

  public:
    Engine();
    void runEngine();
    void loadLevel();
};
#endif
