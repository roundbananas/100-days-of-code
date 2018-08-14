/*
 * FSMbutton.h 
 * features:
 *  - data structure for a state machine, and 
 *  - class for creating and reading a MOM button 
 */

#ifndef FSMbutton_h
#define FSMbutton_h

#include "Arduino.h"

/*------------------CLASS FOR BUTTON-----------*/
//this class is for creating a mom button input and reading it using debouncing
class MomButton
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
  MomButton(int buttonPin)
  {
    momButtonPin = buttonPin;

    debounceInterval = 10; //take multiple readings 10 milliseconds apart to confirm the button was pushed
    lastToggleTime = 0;
    lastButtonReading = 1; //initialise as not pressed (if using a pull down resistor, change this to LOW)

  }

  int UpdateButton()
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
           Serial.print("Updating Button state: ");
              Serial.println(buttonReading);
    }
        if(buttonReading != lastButtonReading)
    {
      lastToggleTime = millis();  
                Serial.print("Updating ToggleTime: ");
              Serial.println(lastToggleTime);
    }
   return buttonReading;
  }
};

/*------------------DATA STRUCTURE FOR STATES----*/
/*
 * CURRENT STATE
 * States_struct (alias States) is a 'struct' data type (a collections of variables). 
 * We use this data type to create a variable that stores current state.
 * We declare enough of these collections of variables to cover the static states we have (ie not transition states). 
 * For this program we have two - IDLE or RUNNING - and each one contains:
 * - the name of the state - we give the variable the state's name, ie IDLE or RUNNING
* - the time we entered the current state, ie started_at
* - a function that handles the transitions from this state to the next, ie stateFunction
* 
* TRANSITIONS
* At any time, we need to be able to check what state we are in and if we need to change to another state. 
* The transition required is dependent on the current state (ie what we do next depends on what state we're in),  
* so we use a function, called stateFunction to handle the transition. We need to give stateFunction the relevant info 
* for it to make a decision as to what to do next, and to actually do what needs to be done (either change state or not). 
* 
* In this particular program we want a button push to make the led to turn on then go off after 5 seconds.
* So we need to know the current_time and the time the current state started_at.
* We also need to know what the buttonState is, because that's our trigger to change state.
* So, our stateFunction needs these three variables as inputs.
*/

/* In this case the same set of variables informs all transitions (regardless of what state we're in).  
 *  If we had a scenario where a button push triggered change from State A to B and then a light sensor triggered change from 
 *  State B to A, we could add an extra variable to the stateFunction. In this case we would just ignore the irrelevant variable
 *  when transitioning.
 */
typedef struct States_struct (*StateFn)(struct States_struct current_state, unsigned long current_time, int button_state);

typedef struct States_struct {
  unsigned long started_at; //we'll use this and the current_time variable to work out when to switch the state back to idle
  StateFn stateFunction; //Define a variable called StateFunction, that is of StateFn data type. This function is used to perform transitions between states.
} States;

/*Create two states, named Idle and Running, using the States data type. Note that Idle and Running ARE NOT FUNCTIONS themselves, 
 * but they do contain the function stateFunction. Therefore they must take the variables required by stateFunction.
*/
States Idle(States current_state, unsigned long current_time, int button_state);
States Running(States current_state, unsigned long current_time, int button_state);

#endif
