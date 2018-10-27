/*
 * 
 * Carl Turner 27 October 2018
 * roundbananas.com
 * 
 */
#include "Motor.h"

Motor::Motor(){}

void Motor::Spawn(int speedPin, int dirnPin)
{
	m_SpeedPin = speedPin;
	m_DirnPin = dirnPin;
}

void Motor::Update(int speed)
{
    if(speed >= 0)
    {
        digitalWrite(m_DirnPin, HIGH);  //assuming HIGH corresponds to forwards
        analogWrite(m_SpeedPin, speed);
    }
    else //go backwards
    {
        digitalWrite(m_DirnPin, LOW);
        analogWrite(m_SpeedPin, -speed);
    }  
}