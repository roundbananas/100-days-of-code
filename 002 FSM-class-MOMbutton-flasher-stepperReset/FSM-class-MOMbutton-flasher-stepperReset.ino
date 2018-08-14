/*State machine:
 * 1. Wait for input from MOM button
 * 2. When button is pressed, change to RUNNING state, and flash leds and turn stepper
 * 3. wait 1 second 
 * 4. reset the stepper position and turn leds off, revert to IDLE state
 * 5. go back to start
 */

#include "FSMbutton.h"
#include "Flasher.h"
#include <FastLED.h>
#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Stepper.h"
 
/*------------------CONSTANTS---------*/
int duration = 1000; //this is the time we'll stay in Running state before reverting to Idle state.
int stepsPerRev = 200; //adjust for the stepper you're using

/*------------------VARIABLES---------*/
int buttonOn; //1 = no, 0 = yes
long stepCounter; //for stepper
int stepperState; //0 = idle, 1 = running, 2 = returning home
long stepsFromHome;
long _stepsFromHome;
/*------------------OBJECTS---------*/
//class is called MomButton and it takes variable (int buttonPin)
MomButton button1(A5);

// Flasher(int number, int colH, int colS, int colV, long on, long off)
// number = position of led on the strip (first one is 0)
// colH / colS / colV refer to HSV colour values
// on = duration the led is on in milliseconds
// off = duration the led is off in milliseconds
struct CRGB leds[NUM_LEDS]; //number of leds in the strip
Flasher led1(0, 255, 150, 150, 250, 100);
Flasher led2(1, 0, 100, 100, 100, 400);
Flasher led3(2, 200, 5, 100, 200, 1000);

//StepperMotor(steps per rev, pin1RedBrown, pin2BlueOrange, pin3GreenRed, pin4BlackYellow)
Stepper stepper1(stepsPerRev, 9, 10, 11, 12);

/*------------------FUNCTIONS---------*/

long calcsteps(long _stepCounter, int stepsPerRev)
{
  //function to calculate steps required to reset stepper to home position
    // calculate steps to home position, based on stepsperrev
        int multiplier;
        for (int x = 0; x < 100; x++)
        {
          long a = (stepCounter - x*stepsPerRev);
          long b = (stepCounter - (x+1)*stepsPerRev);
          if(a <= 0)
            {
              multiplier = x-1;
              break;
            }
          if((a > 0) & (b < 0))
            {
              multiplier = x;
              break;
            }
          if((a > 0) & (b > 0)) 
          {
            //loop again to try next value of x  
          }
        }      
        return stepsFromHome = stepCounter - stepsPerRev*multiplier;
   //     Serial.print("stepCounter = ");
   //     Serial.print(stepCounter);
}

/*------------------STATE TRANSITIONS---------*/
States state; //holds the current state

//If we're in Idle state, the program will call the Idle function to work out what to do next:
States Idle(States current_state, unsigned long current_time, int button_state)
{
  //use switch structure to create options for what to do, based on the buttonState
  switch(button_state)
  {
    case 0: //button has been pushed
    return (States) {current_time, &Running}; //transitions to Running state, and sets started_at to the current time

    case 1: //no button push
    return (States) {current_state.started_at, &Idle}; //stays in Idle state, and doesn't change start_at time.
  }
}

States Running(States current_state, unsigned long current_time, int button_state)
{
   switch(button_state)
   {
    case 0: //button pushed
    /* we only come here if we're in the running state 
     * AND we've reached the specified 'duration' 
     * AND the button has been pushed already (maybe someone held it down or pressed it while the Running state came to an end)
     */
     return (States){current_time, &Running}; //transition back to Running state. ie start Running state again.

     case 1: //button not pushed
     return (States){current_time, &Idle}; //transition to Idle state, and set the time we did that to the current time
   }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Begin Setup");

  //setup leds on the DATA_PIN and CLOCK_PIN, and the number of leds in the strand NUM_LEDS
  //if we want a second strand we could define a second set of pins and quantity of led, 
  //eg DATA_PIN2, CLOCK_PIN2, NUM_LEDS2  
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);

  //Setup the timer
  cli();            // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B
  OCR1A = 60000;  //60000 equates to an interrupt every 0.004 seconds (with no prescalar). This translates to ~80rpm
  TCCR1B |= (1 << WGM12); //CTC mode
  sei();          // enable global interrupts:

  stepCounter = 0; //0 is home position for the stepper
  stepperState = 0; //idle

  //start in idle state
  state.started_at = millis();
  state.stateFunction = &Idle;
  
  Serial.println("Ending Setup");
}

void loop()
{
  //read the button
  buttonOn = button1.UpdateButton();
//  Serial.print("ButtonON: ");
 // Serial.println(buttonOn);
  
  //record the current time
  unsigned long t = millis(); 

//update the state, depending on what the current state is and how long we've been in the current state
// -if it's running and time elapsed is less than our specified limit, keep running
// -if it's running and time elapsed since it started running has reached the limit, transition to IDLE state
// -if idle and button been pushed transition to RUNNING state

  if ((state.stateFunction == Running) & (t - state.started_at < duration)) //ONCE WE ADD MP3, we'll substitute duration variable for a test that checks if MP3 is still playing
  {
    Serial.println("in Running state");
    //No need to transition. Just keep running. (The stepper keeps running because the timer interrupt is still on.) 
      led1.UpdateLed();
      led2.UpdateLed();
      led3.UpdateLed();
  }

  if ((state.stateFunction == Running) & (t - state.started_at >= duration))
  {
    //if the button has been held down as the duration is reached, we want it to run again.
    // So only stop the timer (ie stepper) if the button is not currently being pushed.
    if (buttonOn == 0)
    {
      Serial.println("in Running state, button pushed, so let's go again!");
    }
    else if (buttonOn == 1)
    {
      stepperState = 2; //When the stepperState is 2 the timer will send the stepper home and turn itself off
      
          _stepsFromHome = calcsteps(stepCounter, stepsPerRev);
          stepCounter = _stepsFromHome;
       
      Serial.println("in Running state, transitioning to Idle state");
    }
    //syntax is stateFunction(States current_state, unsigned long current_time, int button_state);
    state = state.stateFunction(state, t, buttonOn); //go to transition (ie update the state) 
  }

  if ((state.stateFunction == Idle) & (buttonOn == 0))
  {
      Serial.println("in Idle state, transitioning to Running state");
    //button has been pushed. Transition to RUNNING state
      //Start the timer, so the stepper starts
      TIFR1 |= (1 << OCF1A); //clear any flag (pending interrupt) (datasheet p.185)
      TCNT1 = 0; //clear the counter (datasheet section 20.10, p.157, 20.12.2, p.161 
      TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt (Datasheet, p.184):
       // Set CS12/11/10 bits for prescaler (Datasheet, p.173)
               TCCR1B |= (1 << CS10); //START TIMER, with no prescaling
          //   TCCR1B |= (1 << CS11); 
           //  TCCR1B |= (1 << CS12); 
      
       stepCounter = 0; //start with zero step count 
       stepperState = 1;  //set stepper state to Running
       
    state = state.stateFunction(state, t, buttonOn);
  }

   if ((state.stateFunction == Idle) & (buttonOn == 1))
  {
  //  Serial.println("in Idle state: turning leds off");
      //Make sure LEDS are OFF. NOTE we can't use FastLed syntax directly here (ie leds[LedX] = CRGB::Black;), it 
      // needs to be put into another function within the Flasher class. Then we update each led in the same way as
      // we turned it on, except we call the new function, GoBlack(), instead of Update().
  
      led1.GoBlack();
      led2.GoBlack();
      led3.GoBlack();
   }  
       if(stepCounter >0)
       Serial.println(stepCounter);

}

//Code for interrupt when counter matches compare value. This function will be called every time the timer count reaches OCR1A. 
//NOTE: putting Serial.print commands in the ISR function create a delay that messes up the timer, and messes up your whole program
ISR(TIMER1_COMPA_vect) ///Datasheet Table 16.1, p.82. Note for ATTiny it's "TIM1..."; for ATMega328 it's "TIMER1..." 
{
/*
 * If running, take another step
 * if going home, go home then turn timer off
 */
  if(stepperState == 1)
  {
     stepper1.step(1); // take one step
     stepCounter++;     // increment the step counter
  }

if(stepperState == 2)
  {
        Serial.println("before while");

     while (stepCounter > 0)
      {
        Serial.println("in while");
        stepper1.step(-1); // go back to home position
        stepCounter--;
      }
     stepperState = 0;   // reset to idle    
  } 
}
