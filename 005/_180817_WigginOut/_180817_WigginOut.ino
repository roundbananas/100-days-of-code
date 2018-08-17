#include "Arduino.h"
#include "momButton.h"
#include "wigginState.h"
#include "flasher.h"
#include "Stepper.h"
#include <avr/io.h> //for timer interrupt
#include <avr/interrupt.h> //for timer interrupt
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

/********GLOBAL VARIABLES**********/
const int button1Pin = A5;
const int stepsPerRev = 200; //adjust for the stepper you're using
const long timeOut = 2000; //this is how long the WigginMode runs for.
volatile int g_stepCounter; //used in timer interrupt to track steps taken. This is used to update the state.step_counter variable.
int g_stepsToHome;
int g_stepperMode;  //0 = off, 1 = fwd, 2 = reverse
bool MP3Flag;

/********INSTANTIATE OBJECTS**********/
State state; //holds the current state  
MomButton button1(button1Pin); //class is called MomButton and it takes variable (int buttonPin)

struct CRGB leds[NUM_LEDS];
Flasher flasher1(0, 200, 100, 100, 250, 150); //Blue
Flasher flasher2(1, 270, 100, 100, 100, 200); //Purple
Flasher flasher3(2, 0, 100, 100, 50, 100); //Red
//Flasher flasher4(3, 58, 100, 100, 50, 100); //Yellow

//StepperMotor(steps per rev, pin1RedBrown, pin2BlueOrange, pin3GreenRed, pin4BlackYellow)
Stepper stepper1(stepsPerRev, 9, 10, 11, 12);

//MP3 Player
SoftwareSerial mySoftwareSerial(5, 6); // MP3 Player RX, TX
DFRobotDFPlayerMini myDFPlayer;

/********MODE BEHAVIOURS**********/
State IdleMode(State current_state, unsigned long current_time, bool button_reading, long time_out){
    Serial.println("IdleMode");

    //Update the state
    State new_state;
    new_state.modeFunction = current_state.modeFunction; 
    new_state.mode_started_at = current_state.mode_started_at;

    if (!button_reading){ //if the button is pushed, transition to wigginMode
        Serial.println("Trans to WigginMode");
        new_state.modeFunction = &WigginMode;
        new_state.mode_started_at = current_time;
        g_stepperMode = 1;
    }
    return new_state;
}

State WigginMode(State current_state, unsigned long current_time, bool button_reading, long time_out){
    Serial.println("WigginMode");

    //Update the state
    State new_state;
    new_state.modeFunction = current_state.modeFunction; 
    new_state.mode_started_at = current_state.mode_started_at;

    if ((current_time - current_state.mode_started_at) >= time_out){ //if we've reached time out, switch to ReturnMode               
        Serial.println("Trans to ReturnMode");
        g_stepperMode = 0; //stop the stepper
        Serial.println(g_stepCounter);
        g_stepsToHome = calcsteps(g_stepCounter, stepsPerRev); //calculate how far the stepper needs to return 
        g_stepCounter = g_stepsToHome;
        new_state.modeFunction = &ReturnMode;
        new_state.mode_started_at = current_time;  
       
    }
    return new_state;
}

State ReturnMode(State current_state, unsigned long current_time, bool button_reading, long time_out){
    Serial.println("ReturnMode");
    
    //Update the state
    State new_state;
    new_state.modeFunction = current_state.modeFunction; 
    new_state.mode_started_at = current_state.mode_started_at;
    g_stepperMode = 2; //start the stepper
    Serial.println(g_stepperMode);
    Serial.println(g_stepCounter);

    if (g_stepCounter <= 0){
        Serial.println("Trans to IdleMode");
        g_stepperMode = 0;
        new_state.modeFunction = &IdleMode; 
        new_state.mode_started_at = current_time; 
    }
    return new_state;
}

/********HELPER FUNCTIONS**********/
void StartTimerInterrupt(){
      Serial.println("Start Timer");
  //Start the timer, so the stepper starts
      TIFR1 |= (1 << OCF1A); //clear any flag (pending interrupt) (datasheet p.185)
      TCNT1 = 0; //zero the counter (datasheet section 20.10, p.157, 20.12.2, p.161 
      TCCR1B = bit (CS10);
}

void ResetTimerInterrupt(){
      Serial.println("Reset Timer");
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B
  TCCR1B |= (1 << WGM12); //CTC mode 
}

int calcsteps(volatile int _stepCounter, int _stepsPerRev) {
        //function to calculate steps required to reset stepper to home position
        int multiplier;
        for (int x = 0; x < 100; x++)
        {
          int a = (_stepCounter - x*_stepsPerRev);
          int b = (_stepCounter - (x+1)*_stepsPerRev);
          if(a <= 0)
            {
              multiplier = x-1;
              break;
            }
          if((a > 0) && (b < 0))
            {
              multiplier = x;
              break;
            }
          if((a > 0) && (b > 0)) 
          {
            //loop again to try next value of x  
          }
        }      
        int _stepsFromHome;
        return _stepsFromHome = _stepCounter - _stepsPerRev*multiplier;
}

void StartUpMP3Player(){
  Serial.println();
      Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
      
      if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while(true){
          delay(0); // Code to compatible with ESP8266 watch dog.
        }
      }
      Serial.println(F("DFPlayer Mini online."));   
     
      myDFPlayer.volume(10);  //Set volume value. From 0 to 30

}

void Render(State current_state){
    Serial.println("Rendering");

    /*Render actions corresponding to the mode:
    Idle Mode: make sure everything is off
    Wiggin Mode: run everything
    Return Mode: make sure everything is off, except the stepper and timer.
    */

   if(state.modeFunction == IdleMode){
       flasher1.GoBlack();
       flasher2.GoBlack();
       flasher3.GoBlack();
     }

   if(state.modeFunction == WigginMode){
       flasher1.UpdateLed();
       flasher2.UpdateLed();
       flasher3.UpdateLed();

        if(!MP3Flag){
           myDFPlayer.next();
           bool MP3Flag = true;
        }
       //if mp3 not playing, start playing it
       
   }

   if(state.modeFunction == ReturnMode){
       
       flasher1.GoBlack();
       flasher2.GoBlack();
       flasher3.GoBlack();
       //the timer takes care of returning the stepper to home position.
       //if mp3player is playing, myDFPLayer.stop();
       if(MP3Flag){
           myDFPlayer.stop();
           bool MP3Flag = false;
        }
   }
}

/********SETUP AND MAIN LOOP**********/
void setup() {
    Serial.begin(9600);
    mySoftwareSerial.begin(9600); 
    Serial.begin(115200);
    Serial.println("Begin Setup");

    //start the software serial to run the mp3 player

    pinMode(button1Pin, INPUT);

    //setup leds on the DATA_PIN and CLOCK_PIN, and the number of leds in the strand NUM_LEDS
    //if we want a second strand we could define a second set of pins and quantity of led, 
    //eg DATA_PIN2, CLOCK_PIN2, NUM_LEDS2  
    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
    
    cli();            // disable global interrupts
    ResetTimerInterrupt(); //Setup the timer. See helper function, above.
    OCR1A = 60000;  //60000 equates to an interrupt every 0.004 seconds (with no prescalar). This translates to ~80rpm
    TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt (Datasheet, p.184):
    sei();          // enable global interrupts:
    StartTimerInterrupt();
    
    state.modeFunction = &IdleMode;
    state.mode_started_at = millis();

    g_stepperMode = 0;
    g_stepCounter = 0; 
    g_stepsToHome = 0;

       flasher1.GoBlack();
       flasher2.GoBlack();
       flasher3.GoBlack();
    
    //start the mp3 player
    StartUpMP3Player();
    bool MP3Flag = false;
}

void loop() {    
    unsigned long t = millis();
    state = state.modeFunction(state, t, button1.UpdateButton(), timeOut); 
    Render (state);
    Serial.println(" ");
}

//Code for interrupt when counter matches compare value. This function will be called every time the timer count reaches OCR1A. 
//NOTE: putting Serial.print commands in the ISR function create a delay that messes up the timer, and messes up your whole program
ISR(TIMER1_COMPA_vect) ///Datasheet Table 16.1, p.82. Note for ATTiny it's "TIM1..."; for ATMega328 it's "TIMER1..." 
{

  switch (g_stepperMode){
 
     case 0: //idle
       //do nothing
       break;
       
    case 1: //running
       stepper1.step(1); // take one step
       g_stepCounter++;     // increment the step counter
       break;
  
    case 2: //return
       if (g_stepCounter > 0)
        {
          stepper1.step(-1); // go back to home position
          g_stepCounter--;
        }
       break;
  }
}
