//
//  Engine.cpp
//
//  Created by Carl Turner on 22/10/18.
//

#include "Engine.h"

Engine::Engine()
{
    m_Mode.control = RC_MODE;
    m_Mode.mood = IDLE;
    m_Mode.startedAt = millis();
    
    //setup radio
    m_pRadio = new RF24(m_CEpin, m_CSpin);
    if (m_Transmitter)
    {
      m_pRadio->begin();
      m_pRadio->openWritingPipe(radioConfig.GetPipe());

      // m_Buttons = createButtons(m_NumButtons, m_ButtonPins);
      m_joystick.Spawn(m_XPin, m_YPin);
    }
    else
    {
      m_pRadio->begin();
      m_pRadio->openReadingPipe(1,radioConfig.GetPipe());
      m_pRadio->startListening(); 

      m_Motor.Spawn(m_MotorSpeedPin, m_MotorDirnPin);
      m_Servo.Spawn(m_ServoPin);
    }
}

void Engine::runEngine()
{
  //  unsigned long lastTime = 0; //used to calculate dt if we need it
  
    while (true)
    {
        unsigned long t = millis();
      //  unsigned long dt = t - lastTime;

        m_Input(t);
        m_Update(t);
        m_Render();
        
      //  lastTime = t;
    }
}