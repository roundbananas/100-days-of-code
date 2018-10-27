//
//  Joystick.h
//
//  Created by Carl Turner on 22/10/18.
//
 
#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

class Joystick
{
  private:
    /*the joystick range is 0 to 900, with 450 in the middle-ish. Create a window of +/-5 around the
    * middle to allow for the dodgy joystick. Within this window we'll set speed and direction to 0.

    *  NOTE THE RANGE 0-900 IS IF YOU ARE SUPPLYING 5V TO THE JOYSTICK. 
    *  IF YOU SUPPLY 9V IT GOES TO FULL RANGE ie 0-1023.
    */
    const int m_CentreX = 512;    //the joystick I have 'centres' at 512 on X axis
    const int m_CentreY = 508;  //the joystick I have 'centres' at 508 on Y axis   
    const int m_XLimit1 = m_CentreX - 5; 
    const int m_XLimit2 = m_CentreX + 5;
    const int m_YLimit1 = m_CentreY - 5; 
    const int m_YLimit2 = m_CentreY + 5;

    int m_xPin;
    int m_yPin;

    int m_PositionX;
    int m_PositionY;

public:
    Joystick();
    void Spawn(int xPin, int yPin);
    int GetPositionX();
    int GetPositionY();
};

#endif

