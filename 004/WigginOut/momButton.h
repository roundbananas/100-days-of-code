#ifndef mombutton_h
#define mombutton_h

#include "Arduino.h"

class MomButton
{
    int momButtonPin; //button pin

    bool buttonReading; //this will hold either 1 (not pressed) or 0 (pressed)

    //these will be used for debouncing input readings
    unsigned long debounceInterval; //interval between input pin measurements
    unsigned long lastToggleTime;
    bool lastButtonReading;

    //Constructor - creates a button and initialises member variables and button state
    public:
    MomButton(int buttonPin)
    {
        momButtonPin = buttonPin;

        debounceInterval = 10; //take multiple readings 10 milliseconds apart to confirm the button was pushed
        lastToggleTime = 0;
        lastButtonReading = 1; //initialise as not pressed (using a pull down resistor)
    }

    bool UpdateButton()
    {
        buttonReading = digitalRead(momButtonPin); //read the input pin
 
        if(((millis() - lastToggleTime) > debounceInterval) && (buttonReading != lastButtonReading))
            lastButtonReading = buttonReading; //if we got a legit reading, update the variable
        
        if(((millis() - lastToggleTime) < debounceInterval) && (buttonReading != lastButtonReading))
            {
                lastToggleTime = millis();  //if we want to question the reading, ignore the reading by setting it to the last valid reading 
                buttonReading = lastButtonReading; 
            }
        else {
                buttonReading = buttonReading;
          }
            
        return buttonReading;
    }
};    

#endif
