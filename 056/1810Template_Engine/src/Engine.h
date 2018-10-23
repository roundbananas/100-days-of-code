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


class Engine
{
  private:
  	// Define variables and constants
    Mode m_Mode;
    
    // Prototypes
    void m_Input(unsigned long t);
    void m_Update(unsigned long t);
    void m_Render();

  public:
    Engine();
    void runEngine();
};
#endif