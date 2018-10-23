//
//  Engine.h
//
//  Created by Carl Turner on 22/10/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#ifndef Engine_h
#define Engine_h

// Define structures and classes
#include "Arduino.h"
#include "Modes.h"
#include "ButtonMom.h"
#include "Joystick.h"
#include "Controller.h"

class Engine
{
  private:

    // Define variables and constants
    Mode m_Mode;
    
    static const int m_NumButtons = 3;
    int m_ButtonPins[m_NumButtons] = {3, 4, 5}; //digital pins
    ButtonMom* m_Buttons = nullptr;

    const int m_XPin = A0; //variable for joystick input (left/right)
    const int m_YPin = A1; //variable for joystick input (forward/back)
    Joystick m_joystick;

    // Prototypes
    void m_Input(unsigned long t);
    void m_Update(unsigned long t);
    void m_Render();

  public:
    Engine();
    void runEngine();
};
#endif