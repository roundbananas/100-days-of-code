/*
 * FlasherStandAlone.h
 * 
 * Created by Carl Turner on 8/11/18.
 * 
 * A single coloured LED that flashes. Not intended for use with RGB LEDs or LED strips
 */

#ifndef FlasherStandAlone_h
#define FlasherStandAlone_h

#include "Arduino.h"

class FlasherStandAlone
{
  private:
  int m_pin;
  long m_OnDuration;  //how long do we want it to flash on for?
  long m_OffDuration; // how long between flashes?

  int m_LedMode; //holds current mode of LED (0 = ConstantOff, 1 = ConstantOn, 3 = Flashing). This could be an enum perhaps.
  bool m_LedState; //holds current state of LED when flashing (0 = off, 1 = on)
  unsigned long m_PreviousMillis; //

  public:
  FlasherStandAlone(); //this function will setup the pinMode(pinNumber, OUTPUT); and initial m_LedMode
  void Spawn(int pinNumber, long onDuration);

  int GetMode();
  void SetMode(int mode);
  
  void TurnOff();
  void TurnOn();
  void FlashLed(); //this will flash the led 
  //void FlashLed(long onDuration, long offDuration); //if we want to have more control at some point
  
};
#endif
 
