/*
*	Engine.cpp
*
*	Created by Carl Turner 7 June 2019
*/

#include "Engine.h"
#include "Helper.h"
#include "Objects.h"

//Engine::Engine()	//this works like a setup() function. Setup the game.
//{  
//	Serial.println("Default Engine constructor");

//}

Engine::Engine(void* interruptDispatch1, void* interruptDispatch2, void* interruptDispatch3)
{
	Serial.println("Custom Engine constructor");
	//create sensors
	 for (int i = 0; i < m_NumSensors; i++)
	{	
	pinMode(m_SensorPins[i], INPUT_PULLUP);
	}
	attachPCINT(digitalPinToPCINT(m_SensorPins[0]), interruptDispatch1, CHANGE);
	attachPCINT(digitalPinToPCINT(m_SensorPins[1]), interruptDispatch2, CHANGE);
	attachPCINT(digitalPinToPCINT(m_SensorPins[2]), interruptDispatch3, CHANGE);

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

	//initialise the state
	  	m_state.jewelLocation = HideTheJewels(analogRead(A5));	//this also initialises clues

		m_state.mode_StartedAt = millis();
		m_state.lastClue_At = millis();
		m_state.lastLightning = millis();
		m_state.lastShortMsg_At = millis();

		m_state.clueIndex = 0;
	  	m_state.displayingClue = false;

	  	m_state.msgSystemIndex = 1;
	  	m_state.displayingSystemMsg = false;

	  	m_state.msgCreditsIndex = 0;
	  	m_state.displayingCreditMsg = false;

	  	m_state.msgGameIndex = 0;
	  	m_state.displayingGameMsg = false;

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
	m_OledDisplay->clearBuffer(); 
	m_OledDisplay->setFont(u8g2_font_t0_16_mr); 
	if(m_state.displayingSystemMsg) m_OledDisplay->drawStr(0,10,msgSystem[m_state.msgSystemIndex]);
	if(m_state.displayingGameMsg) m_OledDisplay->drawStr(0,50,msgGame[m_state.msgGameIndex]);
	if(m_state.displayingCreditMsg) m_OledDisplay->drawStr(0,40, msgCredits[m_state.msgCreditsIndex]); 
	if(m_state.displayingClue)
	{
		m_OledDisplay->clearBuffer(); 
		m_OledDisplay->drawStr(0,50,m_state.clues.possibleClues[m_state.clueIndex]);
	}
  	m_OledDisplay->sendBuffer();          // transfer internal memory to the display
  	Serial.println("");
}

//HELPERS
 void Engine::updateSensor1() 		//define updateSensor1, a function that returns void
{ 
	Serial.println("S1 B4");
	Serial.println(m_Sensor1State);
   // m_Sensor1State = !m_Sensor1State; 
    m_SensorStates[0] = !m_SensorStates[0];
    Serial.println("S1 after");
	Serial.println(m_Sensor1State);
} 

 void Engine::updateSensor2() 
{
	Serial.println("S2 B4");
    // m_Sensor2State = !m_Sensor2State; 
     m_SensorStates[1] = !m_SensorStates[1];
    Serial.println("S2 After");
} 

 void Engine::updateSensor3() 
{
    // m_Sensor3State = !m_Sensor3State; 
     m_SensorStates[2] = !m_SensorStates[2];
     Serial.println("S3 After");
} 

/*
void Engine::CreateSensors(int numSensors, byte sensorPins[], SensorFn updateSensors[])
{
	  //setup to the interrupt to toggle sensor states
	  for (int i = 0; i < 1; i++)
	  {
	  	//m_SensorStates[i] = LOW;	
	    pinMode(sensorPins[i], INPUT_PULLUP);
	  	attachPCINT(digitalPinToPCINT(sensorPins[i]), updateSensors[i], CHANGE);
	  }
}
*/
/*
int Engine::getNumSensors()
{
return m_NumSensors;
}
byte Engine::getSensorPin(int index)
{
return m_SensorPins[index];
}
*/
int Engine::HideTheJewels(int randomReading)
	{
	  randomSeed(randomReading);
	  int location = random(0,3);   //returns a random number either 0, 1 or 2 (not inclusive of max bound).
	      Serial.println(location);

	  //assign possible clues to state 
	  switch (location)
	  {
	    case 0: //volcano has jewels
	      m_state.clues.possibleClues[0] = clueOptions[1];
	      m_state.clues.possibleClues[1] = clueOptions[2];
	      Serial.println("Volcano");
	      break;
	    case 1: //mine has jewels
	      m_state.clues.possibleClues[0] = clueOptions[0];
	      m_state.clues.possibleClues[1] = clueOptions[2];
	      Serial.println("Mine");
	      break;
	    case 2: //swamp has jewels
	      m_state.clues.possibleClues[0] = clueOptions[0];
	      m_state.clues.possibleClues[1] = clueOptions[1];
	      Serial.println("Swamp");
	      break;  
	  }  
	  return location;
	}