/*
 * Carl Turner 2018
 * roundbanans.com
 * 
 * Class declaration for a momentary button, including debouncing it on button read.
 */
 
#ifndef BUTTON_H
#define BUTTON_H

class Button
{
  //Class member variables
  int momButtonPin; //button pin

  //the following are used for debouncing input readings
  unsigned long debounceInterval; //interval between input pin measurements
  unsigned long lastToggleTime;
  int lastButtonReading;
  int buttonReading;

  public:
    //Constructor - creates a button
    Button(int buttonPin);

    //methods
    int UpdateButton();
};

#endif
