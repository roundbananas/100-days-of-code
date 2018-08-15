/*
 * Carl Turner 2018
 * roundbanans.com
 * 
 * Class implementation for a momentary button, including debouncing it on button read.
 */
 
 #include "Button.h"
#include "Arduino.h"

Button::Button(int buttonPin)
  {
    momButtonPin = buttonPin;

    debounceInterval = 300; //take multiple readings 10 milliseconds apart to confirm the button was pushed
    lastToggleTime = 0;
    lastButtonReading = 1; //initialise as not pressed (if using a pull down resistor, change this to LOW)

  }

Button::UpdateButton()
  {
    //read the input pin. If it's different from last time, update the time the button was toggled
    buttonReading = digitalRead(momButtonPin);
// Serial.print("Reading: ");
 // Serial.println(buttonReading);
    // if we've exceeded our debounce interval AND the latest reading is different to the last, 
    // we assume it's a legitimate reading. Update the reading variable.
    if(((millis() - lastToggleTime) > debounceInterval) & (buttonReading != lastButtonReading))
    {
         lastButtonReading = buttonReading;
    //       Serial.print("Updating Button state: ");
    //          Serial.println(buttonReading);
    }
        if(buttonReading != lastButtonReading)
    {
      lastToggleTime = millis();  
    //            Serial.print("Updating ToggleTime: ");
    //          Serial.println(lastToggleTime);
    }
   return buttonReading;
  }
