/*
 * There are three identical rocks. One has a magnet underneath (which you can't see from above).
 * The rocks are placed randomly in three designated locations. (two locations have hall sensors)
 * You have to guess which of the rocks has the magnet, without turning the rocks over.
 * 
 * The program deduces the location of the magnet.
 * The program will give you a random clue, as to where the magnet is NOT located, if you choose.
 * 
 * Use interrupt to read the hall sensors, 
 * without delaying the rest of the program.
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * 
 * Note on pinmodes: https://www.arduino.cc/en/Tutorial/DigitalPins
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include "ButtonMom.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//****** HALL SENSORS ******//
byte sensor1_InterruptPin = 2;
byte sensor2_InterruptPin = 3;
volatile bool sensor1_state = LOW;
volatile bool sensor2_state = LOW;

//This function is called when there's a change registered by the hall sensor
void UpdateSensor1State() {
  sensor1_state = !sensor1_state;
}

void UpdateSensor2State() {
  sensor2_state = !sensor2_state;
}

//****** OLED ******//
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);



//****** STATE ******//
byte JewelPosition = 0;
byte ClueOption1 = 0; 
byte ClueOption2 = 0;

char *ClueOptions[] = {"No Jewels!?", "NOT volcano", "NOT Mine", "NOT Swamp"};
char *Clues[2] = {"null", "null"};



//****** Buttons ******//
ButtonMom StartButton;
ButtonMom ClueButton;

byte startButtonPin = 4; 
byte clueButtonPin = 5;

bool haveStarted = false;

void setup() {
  //setup to the interrupt to toggle Hall_State
  //whenever the magnet moves onto or away from the sensor
  pinMode(sensor1_InterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor1_InterruptPin), UpdateSensor1State, CHANGE);
  pinMode(sensor2_InterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor2_InterruptPin), UpdateSensor2State, CHANGE);
  
  u8g2.begin();  
  u8g2.setFont(u8g2_font_t0_16_mr); // choose a suitable font
  
  Serial.begin(9600);
  Serial.println("End Setup");

  StartButton.spawn(startButtonPin);
  ClueButton.spawn(clueButtonPin);
}

void loop() {

  if (!haveStarted)
  {
    if(StartButton.updateButton())
    { 
      //work out where the jewels are 
      if(sensor1_state == LOW) {JewelPosition = 1; Clues[0] = ClueOptions[2]; Clues[1] = ClueOptions[3];}
      else if (sensor2_state == LOW) {JewelPosition = 2; Clues[0] = ClueOptions[1]; Clues[1] = ClueOptions[3];}
      else {JewelPosition = 3; Clues[0] = ClueOptions[1]; Clues[1] = ClueOptions[2];}
      
      u8g2.clearDisplay();   
      haveStarted = true;
    }
    else 
    {
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.drawStr(0,10,"Put Rocks Down");  // write something to the internal memory
    u8g2.drawStr(0,25,"then Press Start");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display
    }
  }
  else //show a random clue if the clue button is pressed
  {
    if (ClueButton.updateButton())
    {
      randomSeed(millis());
      byte clue = random(0, 2);
      while(ClueButton.updateButton())
       {
        u8g2.clearBuffer();          // clear the internal memory
        u8g2.drawStr(0,10,"a clue");  // write something to the internal memory
        u8g2.drawStr(0, 25, Clues[clue]);
        u8g2.sendBuffer();          // transfer internal memory to the display 
       }   
    }
    else //clear the display
    {
      u8g2.clearDisplay();
    }
  }  
}
