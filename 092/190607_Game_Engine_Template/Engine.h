/*
*	Engine.h
*
*	Created by Carl Turner 7 June 2019
*
*/

#ifndef Engine_h
#define Engine_h

#include "Arduino.h"
#include "Objects.h"
#include "ButtonMom.h"
#include <U8g2lib.h>
#include "State.h"

class Engine
{
  private:
    /******** CONSTANTS *********/
	//GAME SETTINGS (constants)
		const static int m_NumButtons = 1;
	    const static int m_NumDisplays = 1;
	    const static int m_NumSensors = 3;

	  	char *clueOptions[3] = {"NOT volcano", "NOT Mine", "NOT Swamp"};
		unsigned long clueDisplayDuration = 2000; //display each clue for this period
		unsigned long lightningFrequency = 7000;
		int musicVolume = 1;
		int voiceVolume = 3;
		uint16_t Mp3Count;

	//HARDWARE SETTINGS (pin assignments)
	  	byte m_buttonPins[m_NumButtons] = {5};

		//NOTE with PinChangeInterrupt library, all pins are usable on Uno, 
		//But on Arduino Mega only: 10, 11, 12, 13, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64),
		// A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
		byte m_SensorPins[m_NumSensors] = {A8, A9, A10};

		byte m_OLED_clk = 13;   //to D0/SCK/SCL on display
		byte m_OLED_data = 11;  //to D1/MOSI/SDA on display
		byte m_OLED_cs = 10;    //to CS on display
		byte m_OLED_dc = 7;     //to DC on display
		byte m_OLED_reset = 6;  //to RES on display

		int Mp3BusyPin = 3;

  	/******** GAME OBJECTS *********/
	    //declare pointers to game object types we want to create
	    ButtonMom *m_Buttons = nullptr;
	    U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI *m_OledDisplay = nullptr;


  	/******** GAME VARIABLES *********/
		volatile bool m_SensorStates[3] = {0}; //declared as volatile cos that's what the pinchange interrupt requires
    	State state;


  	/******** GAME ENGINE FUNCTIONS *********/
	    void m_Input(unsigned long t);
	    void m_Update(unsigned long t);
	    void m_Render();

  public:
    Engine();
    void runEngine();
    
};
#endif