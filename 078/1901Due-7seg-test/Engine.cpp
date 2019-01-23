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
 }

void Engine::runEngine()
{

  while(true)
    {
      m_Input(); 
      m_Update();
      m_Render(); 
    }
}

void Engine::m_Input()
{
}

void Engine::m_Update()
{
  static unsigned long timer = millis();
  static int Seconds = 0;
  
  if (millis() >= timer) 
  {
    Seconds++; // 1000 milliSeconds is equal to 1 Second
    timer += 1000; 
    if (Seconds == 10) 
    { // Reset to 0 after counting for 1000 seconds.
      Seconds=0;
    }
    m_ScoreDisplay.setNumber(Seconds, 0);
    m_CurrentRoundDisplay.setNumber(Seconds);
    m_BestRoundsDisplay.setNumber(Seconds);
  }  
}

void Engine::m_Render()
{
  m_ScoreDisplay.refreshDisplay();
  m_CurrentRoundDisplay.refreshDisplay();
  m_BestRoundsDisplay.refreshDisplay();
}
