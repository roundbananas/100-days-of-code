#include "Joystick.h"

Joystick::Joystick()
{

}

void Joystick::Spawn(int xPin, int yPin)
{
    m_xPin = xPin;
    m_yPin = yPin;
    pinMode(m_xPin, INPUT);
    pinMode(m_yPin, INPUT);
}

int Joystick::GetPositionX()
{
    //Serial.println(analogRead(m_xPin);); //Calibration: set m_CentreX to whatever this value is
    m_PositionX = analogRead(m_xPin);
    return m_PositionX;
}
int Joystick::GetPositionY()
{
    int val = analogRead(m_yPin);
    //Serial.println(val); //Calibration: set m_CentreY to whatever this value is
    if(val < m_YLimit1)
    {
        m_PositionY = -map(val, m_YLimit1, 0, 0, 255); //I want 0 to be in middle (joystick in neutral position), and fastest reversing to be when joystick is as far as it can be pushed downwards.
    }
    else if (val > m_YLimit2)
    {
        m_PositionY = map(val, m_YLimit2, 1023, 0, 255);
    }
    else
    {
        m_PositionY = 0;
    }
    return m_PositionY;
}