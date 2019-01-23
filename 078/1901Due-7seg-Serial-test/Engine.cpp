/*
 *     Engine.cpp
 *     Created by Carl Turner on 3/1/19.
 */

#include "Engine.h"

 Engine::Engine()
 {
     m_ScoreDisplay.begin(m_Score_HardwareConfig, m_Score_NumDigits, m_Score_DigitPins, m_Score_7SegPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_ScoreDisplay.setBrightness(100);
     
     m_CurrentRoundDisplay.begin(m_CurrentRound_HardwareConfig, m_CurrentRound_NumDigits, m_CurrentRound_DigitPins, m_CurrentRound_7SegPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_CurrentRoundDisplay.setBrightness(100);
     
     m_BestRoundsDisplay.begin(m_BestRounds_HardwareConfig, m_BestRounds_NumDigits, m_BestRounds_DigitPins, m_BestRounds_7SegPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_BestRoundsDisplay.setBrightness(100);

      //initialise display pins
    for (int i = 3; i < 31; i++)
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
  if (Serial1.available ()>0)
  {
      Serial.println(Serial1.read ());
      processIncomingByte (Serial1.read ());
  }
}

void Engine::m_Update()
{
  static unsigned long timer = millis();
  static int Seconds = 0;
  
  if (millis() >= timer) 
  {
  }  

//Update displays with values received over serial
    m_ScoreDisplay.setNumber(m_DataReceived[0], 0);
    m_CurrentRoundDisplay.setNumber(m_DataReceived[1]);
    m_BestRoundsDisplay.setNumber(m_DataReceived[2]);
}

void Engine::m_Render()
{
 // for (int i=0; i < 3; i++) Serial.println(m_DataReceived[i]);
 // Serial.println("");
  
  m_ScoreDisplay.refreshDisplay();
  m_CurrentRoundDisplay.refreshDisplay();
  m_BestRoundsDisplay.refreshDisplay();
}

/*
 * HELPER FUNCTIONS
 */

 void Engine::processIncomingByte(const byte c)
{ //Serial.print("c = ");  Serial.println(c);
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
   //       Serial.println("New State is Score");

        m_DisplayRef = DisplayRefs::GOT_SCORE;
        break;
      case 'B':
    //      Serial.println("New State is CurrentRound");

        m_DisplayRef = DisplayRefs::GOT_CURRENT_ROUND;
        break;
      case 'C':
    //      Serial.println("New State is Best Round");

        m_DisplayRef = DisplayRefs::GOT_BEST_ROUND;
        break;      
      default:
          Serial.println("New State is None");

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
   // Serial.print("Assigning Score = "); 
      processDisplay (0, m_currentValue);
      break;
    case DisplayRefs::GOT_CURRENT_ROUND:
    //    Serial.println("Assigning Current Round = ");
      processDisplay (1, m_currentValue); 
      break;
    case DisplayRefs::GOT_BEST_ROUND:
    //    Serial.println("Assigning Best Round = ");
      processDisplay (2, m_currentValue);
      break;
    }  // end of switch  
 //   Serial.println(m_currentValue);
    m_currentValue = 0; 
}  // end of assignCurrentValueToArray()

void Engine::processDisplay (int _display, const unsigned int value)
{
  // Assign data to array elements for relevant display 
 // Serial.print("Processing Display "); Serial.print(_display); Serial.print(" / "); Serial.println(value);
  m_DataReceived[_display] = value; 
} // end of processDisplay
