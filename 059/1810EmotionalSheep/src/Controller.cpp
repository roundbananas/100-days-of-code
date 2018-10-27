#include "Controller.h"

ButtonMom* createButtons(int numButtons, int pins[])
{
    ButtonMom* buttons = new ButtonMom[numButtons];
    
    for (int i = 0; i < numButtons; i++)
    {
        buttons[i].spawn(pins[i]);
    }
    return buttons;
}

