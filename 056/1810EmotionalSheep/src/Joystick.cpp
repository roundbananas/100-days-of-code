#include "Joystick.h"

void Joystick::Spawn(int xPin, int yPin)
{
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}

Joystick::Position Joystick::GetPosition(int xPin, int yPin)
{
    int x = analogRead(xPin);
    int y = analogRead(yPin);
    return (Position){x, y};
}