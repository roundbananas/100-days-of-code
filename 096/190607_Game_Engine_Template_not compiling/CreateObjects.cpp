/*
*	CreateObjects.cpp
*
*	Created by Carl Turner 16 June 2019
*/

#include "Objects.h"


ButtonMom* createButtons(int NumButtons, byte buttonPins[])
{
	ButtonMom *buttons = new ButtonMom[NumButtons];	//dynamically allocate an array of ButtonMom objects, with number of objects = NumButtons

	for (int i = 0; i < NumButtons; i++)	//spawn/initialise each button
		buttons[i].spawn(buttonPins[i]);

	return buttons; 
}


U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI* createOledDisplay(uint8_t clock, uint8_t data, uint8_t cs, uint8_t dc, uint8_t reset = U8X8_PIN_NONE)
{
	U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI *displays = new U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI(U8G2_R0, /* clock=*/ clock, /* data=*/ data, /* cs=*/ cs, /* dc=*/ dc, /* reset=*/ reset);

	return displays;
}