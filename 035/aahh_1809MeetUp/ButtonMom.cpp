//
//  ButtonMom.cpp
//
//  Created by Carl Turner on 18/9/18.
//
#include "ButtonMom.h"

ButtonMom::ButtonMom()
{
  
}

void ButtonMom::spawn(int buttonPin)
    {
        m_Pin = buttonPin;

        m_DebounceInterval = 50; //take multiple readings 10 milliseconds apart to confirm the button was pushed
        m_LastToggleTime = 0;
        m_LastButtonReading = 0; //initialise as not pressed (using a pull down resistor)
    }

bool ButtonMom::UpdateButton()
{
    m_CurrentReading = digitalRead(m_Pin); //read the input pin

    if(((millis() - m_LastToggleTime) > m_DebounceInterval) && (m_CurrentReading != m_LastButtonReading))
        m_LastButtonReading = m_CurrentReading; //if we got a legit reading, update the variable
    
    if(((millis() - m_LastToggleTime) < m_DebounceInterval) && (m_CurrentReading != m_LastButtonReading))
        {
            m_LastToggleTime = millis();  //if we want to question the reading, update the 
            m_CurrentReading = m_LastButtonReading; 
        }
    return m_CurrentReading;
}
