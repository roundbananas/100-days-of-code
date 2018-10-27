/*
 * 
 * Carl Turner 27 October 2018
 * roundbananas.com
 * 
 */
#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include "Arduino.h"
#include "Servo.h"

class ServoMotor
{
private:
    //Calibrate - set the sweep angle of your servo here:
    int m_AngleMin = 0;
    int m_AngleMax = 179;

    Servo m_Servo;

public:
    ServoMotor(); 
    void Spawn(int pin); //include attach()
    void Update(int position);
};
#endif
