/*
 *     Engine.cpp
 *     Created by Carl Turner on 3/1/19.
 */

#include "Engine.h"

 Engine::Engine()
 {
  Serial.println("Engine Constructor");
     //instantiate displays
     m_ScoreDisplay.begin(m_Score_HardwareConfig, m_Score_NumDigits, m_Score_DigitPins, m_Score_7SegPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_ScoreDisplay.setBrightness(100);
     
     m_CurrentRoundDisplay.begin(m_CurrentRound_HardwareConfig, m_CurrentRound_NumDigits, m_CurrentRound_DigitPins, m_CurrentRound_7SegPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_CurrentRoundDisplay.setBrightness(100);
     
     m_BestRoundsDisplay.begin(m_BestRounds_HardwareConfig, m_BestRounds_NumDigits, m_BestRounds_DigitPins, m_BestRounds_7SegPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_BestRoundsDisplay.setBrightness(100);

    //initialise display pins
    for (int i = 3; i < 32; i++)
    {
      pinMode(i, OUTPUT);
    }

    //initialise scores to 0
     m_ScoreValue = 0;
     m_CurrentRoundValue = 0;
     m_BestRoundsValue = 0;

    //initialise data processing machine
    m_DisplayRef = DisplayRefs::NONE;
    m_currentValue = 0;
  
 
 }

void Engine::runEngine()
{
    Serial.println("Engine Run");

  while(true)
    {
      m_Input(); 
      m_Update();
      m_Render(); 
    }
}

void Engine::m_Input()
{
    Serial.println("Engine Input");

  while (Serial1.available ())
  {
      Serial.println(Serial1.read ());
      processIncomingByte (Serial1.read ());
  }
}


void Engine::m_Update()
{
    Serial.println("Engine Update");

    for (int i = 0; i < m_NumDisplays; i++)
    {
      m_Displays[i].setNumber(m_DataReceived[i], 0);
    } 
}

void Engine::m_Render()
{
    Serial.println("Engine Render");

  for (int i = 0; i < m_NumDisplays; i++)
    {
      m_Displays[i].refreshDisplay();
    } 
}

/*
 * HELPER FUNCTIONS
 */

 void Engine::processIncomingByte(const byte c)
{
if (isdigit (c))
  {
    m_currentValue *= 10;
    m_currentValue += c - '0';
  }  // end of digit
  
  else
  {
    // The end of the number signals a state change
    assignCurrentValueToArray();

    // set the new state, if we recognize it
    switch (c)
    {
      //DisplayRefs
      case 'A':
        m_DisplayRef = DisplayRefs::GOT_SCORE;
        break;
      case 'B':
        m_DisplayRef = DisplayRefs::GOT_CURRENT_ROUND;
        break;
      case 'C':
        m_DisplayRef = DisplayRefs::GOT_BEST_ROUND;
        break;      
      default:
       m_DisplayRef = DisplayRefs::NONE;
        break;
    }  // end of switch on incoming byte
  } // end of not digit   
} // end of processIncomingByte()

void Engine::assignCurrentValueToArray()
{
  switch (m_DisplayRef)
    {
    case DisplayRefs::GOT_SCORE:
      processDisplay (0, m_currentValue);
      break;
    case DisplayRefs::GOT_CURRENT_ROUND:
      processDisplay (1, m_currentValue); 
      break;
    case DisplayRefs::GOT_BEST_ROUND:
      processDisplay (2, m_currentValue);
      break;
    }  // end of switch  

    m_currentValue = 0; 
}  // end of assignCurrentValueToArray()

void Engine::processDisplay (int _display, const unsigned int value)
{
  // Assign data to array elements for relevant display 
  m_DataReceived[_display] = value;  
} // end of processDisplay
