/*
*	Objects.h
*
*	Created by Carl Turner 7 June 2019
*/

#ifndef Objects_h
#define Objects_h

#include "ButtonMom.h"
#include <U8g2lib.h>
#include "PinChangeInterrupt.h" //https://github.com/NicoHood/PinChangeInterrupt


//ButtonMom* createButtons(int NumButtons, byte buttonPins[]);	//forward declare a function that returns a pointer to desired type

ButtonMom* createButtons(int NumButtons, byte buttonPins[]);
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI* createOledDisplay(uint8_t clock, uint8_t data, uint8_t cs, uint8_t dc, uint8_t reset = U8X8_PIN_NONE);


		

bool* CreateSensors(int numSensors, byte sensorPins[]);
void updateSensor1();
void updateSensor2();
void updateSensor3();

#endif


