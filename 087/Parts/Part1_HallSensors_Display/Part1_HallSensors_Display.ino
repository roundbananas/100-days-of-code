/*
 * Part1_HallSensors_Display
 * By Carl Turner 5 March 2019
 * roundbananas.com
 * 
 * 3 hall sensors
 * display
 * mode changes
 * state
 * 
 * MODE: Setup
 * The program randomly assigns one of three locations as having the 'jewels'.
 * When setup is complete, trigger JewelsHidden mode.
 * 
 * MODE: JewelsHidden
 * There are three hall sensors, one for each of location.
 * When a hall sensor corresponding to false jewel location is triggered, let player know.
 * 
 * When the hall sensor corresponding the jewel location is triggered, the jewels have been 'found':
 * - go to Jewels_Found mode
 * 
 * MODE: JewelsFound 
 * - 
 * 
 * Use pinchange interrupts to read hall sensors, without delaying the rest of the program.
 * Using pinchange library by NicoHood.
 */
#include <Arduino.h>
#include "PinChangeInterrupt.h"

#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "Modes.h"        //mode functions and state struct

/*
 * PINS
 */
byte sensorPins[3] = {A0, A1, A2};

byte OLED_clk = 13;   //to D0/SCK/SCL on display
byte OLED_data = 11;  //to D1/MOSI/SDA on display
byte OLED_cs = 10;    //to CS on display
byte OLED_dc = 9;     //to DC on display
byte OLED_reset = 8;  //to RES on display

 /*
 * VARIABLES
 */
State_Struct state; //holds current state

volatile bool sensor1State = LOW;
volatile bool sensor2State = LOW;
volatile bool sensor3State = LOW;
volatile bool sensorStates[3] = {sensor1State, sensor2State, sensor3State};

char *clueOptions[3] = {"NOT volcano", "NOT Mine", "NOT Swamp"};

/*
 * INPUTS
 */

/*
 * OUTPUTS
 */
//OLED
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ OLED_clk, /* data=*/ OLED_data, /* cs=*/ OLED_cs, /* dc=*/ OLED_dc, /* reset=*/ OLED_reset);

/*
 * HELPER FUNCTIONS
 */
  //updateSensor functions are called when a 'CHANGE' is registered by the sensor
 void updateSensor1() 
    { sensor1State = !sensor1State; //toggle state
      sensorStates[0] = sensor1State;} 

 void updateSensor2() 
    { sensor2State = !sensor2State; 
      sensorStates[1] = sensor2State;} 

 void updateSensor3() 
    { sensor3State = !sensor3State; 
      sensorStates[2] = sensor3State;} 

int HideTheJewels(int randomReading)
{
  randomSeed(randomReading);
  int location = random(0,3);   //returns a random number either 0, 1 or 2 (not inclusive of max bound).
      Serial.println(location);

  //assign possible clues to state 
  switch (location)
  {
    case 0: //volcano has jewels
      state.clues.clue1 = clueOptions[1];
      state.clues.clue1 = clueOptions[2];
      Serial.println("Volcano");
      break;
    case 1: //mine has jewels
      state.clues.clue1 = clueOptions[0];
      state.clues.clue2 = clueOptions[2];
      Serial.println("Mine");
      break;
    case 2: //swamp has jewels
      state.clues.clue1 = clueOptions[0];
      state.clues.clue2 = clueOptions[1];
      Serial.println("Swamp");
      break;  
  }  
  return location;
}

void setup() {
  Serial.begin(115200);

  //Set initial state
  state.startedAt = millis();
  state.jewelLocation = HideTheJewels(analogRead(A5));
  state.displayingClue = false;
  state.updateMode = &Setup;
  
  //setup to the interrupt to toggle Hall_State
  Serial.println("Setting up interrupts");
  for (int i = 0; i < 3; i++)
  {
      pinMode(sensorPins[i], INPUT_PULLUP);
  }
  attachPCINT(digitalPinToPCINT(sensorPins[0]), updateSensor1, CHANGE);
  attachPCINT(digitalPinToPCINT(sensorPins[1]), updateSensor2, CHANGE);
  attachPCINT(digitalPinToPCINT(sensorPins[2]), updateSensor3, CHANGE);

  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_t0_16_mr); // choose a suitable font
  u8g2.drawStr(0,10,"Hello");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay (1000);
}

void loop() {
  //updateMode(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState);
  state = state.updateMode(state, millis(), sensorStates, 0);
  Serial.println("");
  delay (1000);

}
