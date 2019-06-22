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


//volatile bool m_Sensor1State = LOW;
//volatile bool m_Sensor2State = LOW;
//volatile bool m_Sensor3State = LOW;
//volatile bool m_SensorStates[3] = {m_Sensor1State, m_Sensor2State, m_Sensor3State}; //declared as volatile cos that's what the pinchange interrupt requires


//updateSensor functions are called when a 'CHANGE' is registered by the sensor
		 void updateSensor1() 		//define updateSensor1, a function that returns void
		{ 
		    m_SensorStates[0] = !m_SensorStates[0]; 
		} 

		 void updateSensor2() 
		{
		    m_SensorStates[1] = !m_SensorStates[1];
		} 

		 void updateSensor3() 
		{
		    m_SensorStates[2] = !m_SensorStates[2];
		} 

bool* CreateSensors(int numSensors, byte sensorPins[])
{
	bool *sensorStates = new bool[numSensors];
	for (int i = 0; i < numSensors; i++)
	 {
	   sensorStates[i] = LOW;	
	   pinMode(sensorPins[i], INPUT_PULLUP);
	 }
	  	attachPCINT(digitalPinToPCINT(sensorPins[0]), updateSensor1, CHANGE);
		attachPCINT(digitalPinToPCINT(sensorPins[1]), updateSensor2, CHANGE);
	 	attachPCINT(digitalPinToPCINT(sensorPins[2]), updateSensor3, CHANGE);

	 return sensorStates;
}
