/*
 * Part1_HallSensors 
 * By Carl Turner 5 March 2019
 * roundbananas.com
 * 
 * 3 hall sensors
 * modes
 * state
 * 
 * MODE: SETUP
 * The program randomly assigns one of three locations as having the 'jewels'.
 * When setup is complete, trigger Jewels_Not_Found mode.
 * 
 * MODE: JEWELS_NOT_FOUND
 * There are three hall sensors, one for each of location.
 * When a hall sensor corresponding to false jewel location is triggered:
 * - LED 13 blinks once
 * 
 * When the hall sensor corresponding the jewel location is triggered, the jewels have been 'found':
 * - go to Jewels_Found mode
 * MODE: JEWELS_FOUND 
 * - LED 13 blinks repeatedly
 *
 * STATE VARIABLES ()
 * Variable                 triggers mode change
 * byte jewelLocation       for checking any hall readings
 * bool hallSensor[i]       if i != jewelLocation, triggers fail song. If i = jewelLocation, trigger success song and Jewels_Found mode     
 * bool setupComplete       setup --> Jewels_Not_Found        
 * 
 * Use interrupt to read the hall sensors, 
 * without delaying the rest of the program.
 * using pinchange library.
 */
#include <Arduino.h>
#include "PinChangeInterrupt.h"

#include "Modes.h"        //mode functions and state struct

/*
 * PINS
 */
byte sensorPins[3] = {A0, A1, A2};

 /*
 * VARIABLES
 */
State_Struct state; //holds current state
volatile bool sensor1State = LOW;
volatile bool sensor2State = LOW;
volatile bool sensor3State = LOW;
volatile bool sensorStates[3] = {sensor1State, sensor2State, sensor3State};

/*
 * INPUTS
 */


/*
 * HELPER FUNCTIONS
 */

 void updateSensor1() //Called when a 'CHANGE' is registered by the sensor
    { 
      sensor1State = !sensor1State; //toggle state
      // Switch Led state
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    } 

 void updateSensor2() //Called when a 'CHANGE' is registered by the sensor
{ 
  sensor2State = !sensor2State; //toggle state
  // Switch Led state
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
} 

 void updateSensor3() //Called when a 'CHANGE' is registered by the sensor
    { 
      sensor3State = !sensor3State; //toggle state
      // Switch Led state
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    } 

void setup() {
  Serial.begin(115200);

  Serial.println("Testing LED");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(1000);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  
  //setup to the interrupt to toggle Hall_State
  Serial.println("Setting up interrupts");
  for (int i = 0; i < 3; i++)
  {
      pinMode(sensorPins[i], INPUT_PULLUP);
  }

  attachPCINT(digitalPinToPCINT(sensorPins[0]), updateSensor1, CHANGE);
  attachPCINT(digitalPinToPCINT(sensorPins[1]), updateSensor2, CHANGE);
  attachPCINT(digitalPinToPCINT(sensorPins[2]), updateSensor3, CHANGE);

 

    
}

void loop() {}
