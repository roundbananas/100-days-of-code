//
//  SevenSegDisplay.h
//
//  Created by Carl Turner on 13/10/18.
//

#ifndef SevenSegDisplay_h
#define SevenSegDisplay_h

#include "SevSeg.h"

class SevenSegDisplay
{
  private:
  //the following variables are dependent on number of digits in the display
  byte m_numDigits; //sets the number of digits on your display
  byte m_digitPins[] = {}; //Creates an array that defines the ground pins when using a 4 digit or multi-digit display. Leave it empty if you have a single digit display.

  byte m_segmentPins[8]; //defines which Arduino pins are connected to each segment of the display. The order is alphabetical (A, B, C, D, E, F, G, DP where DP is the decimal point). 
  
  bool m_resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte m_hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool m_updateWithDelays = false; // Default. Recommended
  bool m_leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  
  SevSeg m_SevSegDisplay;
  
  public:
  SevenSegDisplay();
  void Spawn(byte numDigits, byte digitPins[], byte segmentPins[]);  
  void SetNumber(int number);
  void RefreshDisplay(); 
};

#endif
