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
	m_Buttons = createButtons(m_NumButtons, m_buttonPins);	//call the createButtons function to initialise the buttons, and assign the buttons to our variable m_Buttons
    //U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI m_OledDisplay(U8G2_R0, m_OLED_clk, m_OLED_data, m_OLED_cs, m_OLED_dc, m_OLED_reset);

	m_Buttons->spawn(m_buttonPins[0]);
	m_OledDisplay = createOledDisplay(m_OLED_clk, m_OLED_data, m_OLED_cs, m_OLED_dc, m_OLED_reset);

	  m_OledDisplay->begin();
	  m_OledDisplay->clearBuffer();          // clear the internal memory
  m_OledDisplay->setFont(u8g2_font_t0_16_mr); // choose a suitable font
  m_OledDisplay->drawStr(0,10,"Starting Display");  // write something to the internal memory
  m_OledDisplay->sendBuffer();          // transfer internal memory to the display
  delay (1000);

	//attach pin interrupts
	CreateSensors(m_NumSensors, m_SensorPins);

	//initialise the state
	  	m_state.jewelLocation = HideTheJewels(analogRead(A5));	//this also initialises clues

		m_state.mode_StartedAt = millis();
		m_state.lastClue_At = millis();
		m_state.lastLightning = millis();

		m_state.clueIndex = 0;
	  	m_state.displayingClue = false;

	  	//state.MP3CurrentTrack = ?;
	  	m_state.Mp3Playing = false;
	  	m_state.Mp3Ready = false;
		m_state.updateMode = &Setup;

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

void Engine::m_Input(unsigned long t)
{
	//do nothing for now. I've read input directly into updateMode() in m_Update().
}

void Engine::m_Update(unsigned long t)
{
	//syntax  updateMode(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState);
	m_state = m_state.updateMode(m_state, t, m_NumSensors, m_SensorStates, m_Buttons[0].updateButton());
}

void Engine::m_Render()
{  
  m_OledDisplay->sendBuffer();          // transfer internal memory to the display
  Serial.println("");
}
