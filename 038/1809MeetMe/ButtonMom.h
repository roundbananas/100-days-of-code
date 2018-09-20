//
//  ButtonMom.h
//
//  Created by Carl Turner on 18/9/18.
//
#ifndef ButtonMom_h
#define ButtonMom_h

#include "Arduino.h"

class ButtonMom
{
  private:
    int m_Pin; //button pin

    bool m_CurrentReading; //this will hold either 1 (not pressed) or 0 (pressed)

    //these will be used for debouncing input readings
    unsigned long m_DebounceInterval; //interval between input pin measurements
    unsigned long m_LastToggleTime;
    bool m_LastButtonReading;

  public:
    ButtonMom();
    void spawn(int pin);
    
    bool updateButton(); //returns m_CurrentReading 
};    

#endif
