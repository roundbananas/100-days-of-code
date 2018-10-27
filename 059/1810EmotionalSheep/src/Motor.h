/*
 * 
 * Carl Turner 27 October 2018
 * roundbananas.com
 * 
 */
#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor
{
private:
	//pins
	int m_SpeedPin;
	int m_DirnPin;

public:
	Motor();
    void Spawn(int speedPin, int dirnPin);
    void Update(int speed);
};
#endif