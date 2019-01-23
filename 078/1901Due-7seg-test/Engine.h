/*
 *     Engine.h
 *     Created by Carl Turner on 3/1/19.
 *   This test will run three sevSegDisplays, counting on each one.
 */

#ifndef Engine_h
#define Engine_h

#include "SevSeg.h"

class Engine
{
  private:

    //Common variables for all 7segment displays
    const static int m_NumDisplays = 3;
    bool m_ResistorsOnSegments = false; // 'false' means resistors are on digit pins
    bool m_UpdateWithDelays = false; // Default. Recommended
    bool m_LeadingZeros = false; // Use 'true' if you'd like to keep the leading zeros

    //Setup one 4-digit 7segment display for score display
    SevSeg m_ScoreDisplay;
    byte m_Score_NumDigits = 4;
    byte m_Score_HardwareConfig = COMMON_CATHODE; // See README.md for options
    byte m_Score_DigitPins[4] = {3, 4, 5, 6};
    byte m_Score_7SegPins[8] = {7, 8, 9, 10, 11, 12, 13, 14}; //NOTE pin 14 is not connected. We don't need DP.    
     
    //Setup two 2-digit 7segment displays for the current and best #rounds display
    SevSeg m_CurrentRoundDisplay;
    byte m_CurrentRound_NumDigits = 1;
    byte m_CurrentRound_HardwareConfig = COMMON_ANODE;
    byte m_CurrentRound_DigitPins[1] = {15};
    byte m_CurrentRound_7SegPins[8] = {16, 17, 18, 19, 20, 21, 22, 14}; //NOTE pin 14 is not connected. We don't need DP.
   
    SevSeg m_BestRoundsDisplay;
    byte m_BestRounds_NumDigits = 1;
    byte m_BestRounds_HardwareConfig = COMMON_ANODE;
    byte m_BestRounds_DigitPins[1] = {23};
    byte m_BestRounds_7SegPins[8] = {24, 25, 26, 27, 28, 29, 30, 14}; //NOTE pin 14 is not connected. We don't need DP.

    //Main engine functions 
    void m_Input();
    void m_Update();
    void m_Render();

  public:
    Engine();
    void runEngine();
};
#endif
