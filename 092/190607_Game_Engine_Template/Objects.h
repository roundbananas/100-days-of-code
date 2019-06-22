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

ButtonMom* createButtons(int NumButtons, int buttonPins[]);	//forward declare a function that returns a pointer to desired type

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI* createOledDisplay(int NumDisplays, const u8g2_cb_t *rotation, uint8_t clock, uint8_t data, uint8_t cs, uint8_t dc, uint8_t reset = U8X8_PIN_NONE);

//**WHAT TYPE DOES PINCHANGE INTERRUPT RETURN?

#endif

ButtonMom* createButtons(int NumButtons, int buttonPins[])
{
	ButtonMom *buttons = new ButtonMom[NumButtons];	//dynamically allocate an array of ButtonMom objects, with number of objects = NumButtons

	for (int i = 0; i < NumButtons; i++)	//spawn/initialise each button
		buttons[i].spawn(buttonPins[i]);

	return buttons; 
}

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI* createOledDisplay(int NumDisplays, const u8g2_cb_t *rotation, uint8_t clock, uint8_t data, uint8_t cs, uint8_t dc, uint8_t reset = U8X8_PIN_NONE)
{
	U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI *displays = new U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI[NumDisplays](0,0,0,0,0,0);
	for (int i = 0; i < NumDisplays; i++) //for now just one display
		displays[i] = U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI(U8G2_R0, /* clock=*/ clock, /* data=*/ data, /* cs=*/ cs, /* dc=*/ dc, /* reset=*/ reset);

	return displays;
}


//**SETUP SENSOR PINS AND INTERRUPTS