/*
*	Engine.cpp
*
*	Created by Carl Turner 7 June 2019
*/

#include "Engine.h"
#include "Helper.h"
#include "Objects.h"

Engine::Engine()	//this works like a setup() function. Setup the game.
{  
	//create and initialise game objects
	m_Buttons = createButtons(m_NumButtons, m_buttonPins[]);	//call the createButtons function to initialise the buttons, and assign the buttons to our variable m_Buttons
	m_OledDisplay = createOledDisplay(m_NumDisplays, U8G2_R0, m_OLED_clk, m_OLED_data, m_OLED_cs, m_OLED_dc, m_OLED_reset);
	startDisplay(m_OledDisplay);

	//attach pin interrupts
	CreateSensors(m_NumSensors, m_SensorPins);

	//initialise the state
	  	state.jewelLocation = HideTheJewels(analogRead(A5));	//this also initialises clues

		state.mode_StartedAt = millis();
		state.lastClue_At = millis();
		state.lastLightning = millis();

		state.clueIndex = 0;
	  	state.displayingClue = false;

	  	//state.MP3CurrentTrack = ?;
	  	state.Mp3Playing = false;
	  	state.Mp3Ready = false;
	  	for (int i = 0; i< m_NumSensors; i++) state.sensorStates[i] = LOW;
		state.updateMode = &Setup;

}

void Engine::runEngine()
{
	while (true)
	{
		unsigned long t = millis();
		m_Input(t);
		m_Update(t);
		m_Render();
	}
}

Engine::m_Input(unsigned long t)
{
	//do nothing for now. I've read input directly into updateMode() in m_Update().
}

Engine::m_Update(unsigned long t)
{
	//syntax  updateMode(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState);
	state = state.updateMode(state, t, m_NumSensors, m_SensorStates, clueButton.updateButton());
}

Engine::m_Render()
{  
  m_OledDisplay.sendBuffer();          // transfer internal memory to the display
  Serial.println("");
}