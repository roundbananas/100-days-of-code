//
//  SevenSegDisplay.cpp
//
//  Created by Carl Turner on 13/10/18.
//
#include "SevenSegDisplay.h"

SevenSegDisplay::SevenSegDisplay()
{
}

void SevenSegDisplay::Spawn(byte segmentPins[])
{
  for (byte i = 0; i < 8; i++)
  {
    m_segmentPins[i] = segmentPins[i];
  }
 
  m_SevSegDisplay.begin(m_hardwareConfig, m_numDigits, m_digitPins, m_segmentPins, m_resistorsOnSegments, m_updateWithDelays, m_leadingZeros);
  m_SevSegDisplay.setBrightness(90);
}

void SevenSegDisplay::SetNumber(int number)
{
  m_SevSegDisplay.setNumber(number);
}

void SevenSegDisplay::RefreshDisplay()
{
  m_SevSegDisplay.refreshDisplay(); 
}


 
