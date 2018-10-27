/*
 * 
 * Carl Turner 27 October 2018
 * roundbananas.com
 * 
 */
#include "ServoMotor.h"

ServoMotor::ServoMotor()
{
    //nothing
}

void ServoMotor::Spawn(int pin)
{
    m_Servo.attach(pin);
}
void ServoMotor::Update(int position)
{
    int angle = map(position, 0, 1023, m_AngleMin, m_AngleMax);
   // Serial.println(position);
   // Serial.println(angle);
    Serial.println(" ");
    m_Servo.write(angle);
}