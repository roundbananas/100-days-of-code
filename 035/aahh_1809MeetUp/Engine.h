//
//  Engine.h
//
//  Created by Carl Turner on 18/9/18.
//
#ifndef Engine_h
#define Engine_h

#include "Arduino.h"
#include "Modes.h"
#include "Player1.h"

class Engine
{
  private:
    //declare players
    Player1 m_Player1;
    Bullet m_Bullet1;
    ButtonMom m_Button1;
    SlidePot m_Pot1;
    
    Player1 m_Player2;
    Bullet m_Bullet2;
    ButtonMom m_Button2;
    SlidePot m_Pot2;
    
    Modes mode = Modes::IDLE_MODE;
    int m_Level = 0;

    unsigned long m_CurrentTime;

    void m_Input(unsigned long currentTime);
    void m_Update(unsigned long currentTime);
    void m_Render();

  public:
    Engine();
    void runEngine();
    void loadLevel();
};

#endif
