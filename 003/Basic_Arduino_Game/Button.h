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

  //these will be used for debouncing input readings
  unsigned long debounceInterval; //interval between input pin measurements
  unsigned long lastToggleTime;
  int lastButtonReading;
  int buttonReading;

  //Constructor - creates a button and initialises member variables and button state
  public:
    Button(int buttonPin);

    int UpdateButton();
};

#endif
