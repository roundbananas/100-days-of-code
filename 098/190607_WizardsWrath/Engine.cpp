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
		m_state.lastPageAt = millis();

		m_state.clueIndex = 0;
	  	m_state.displayingClue = false;

	  	m_state.currentPage = 1;
	  	m_state.displayingPage = false;

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

	if(m_state.displayingPage)
  	{
  		m_SetPage(m_state.currentPage, m_state.displayingClue, m_state.clues.possibleClues[m_state.clueIndex], m_OledDisplay);       
  	}
  	
	m_OledDisplay->sendBuffer(); // transfer internal memory to the display
 
  	Serial.println("");
}

//HELPERS

void Engine::m_SetPage(byte page, bool displayClue, char *clue, U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI *display)
{
	display->clearBuffer();
	switch (page)
	{
		case 0: //Starting...
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"Starting...");
		break;

		case 1: //Title page
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"WIZARD'S");
		display->drawStr(0,30,"WRATH");
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,40,"(C) Steve Grasso & Carl Turner");
		display->drawStr(0,50,"Cairns 2019");
		break;

		case 2: //Press button to start
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"TO START");
		display->drawStr(0,30,"Press Button");
		break;

		case 3: //Story 1
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"THE STORY");
		display->drawStr(0,30,"blah blah");
		break;

		case 4: //Story 2
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"THE STORY");
		display->drawStr(0,30,"foo foo");
		break;

		case 10: //Go
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"Roll 'em dice");
		break;

		case 11: //Press for clue
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"Press Button For Clue");
		break;

		case 12: //Clue
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"CLUE");
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,30,"NOT IN THE");
		display->drawStr(0,40,clue);
		break;

		case 20: //Moment of truth - no jewels
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"MOMENT OF TRUTH");
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,30,"No Jewels here");
		break;

		case 21: //Moment of truth - jewels
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"MOMENT OF TRUTH");
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,30,"You beauty!");
		display->drawStr(0,50,"Got the JEWELS!");
		break;

		case 22: //race home
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"THE RACE HOME");
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,30,"Press button if");
		display->drawStr(0,40,"you arrive HOME");
		display->drawStr(0,50,"with the Jewels");
		break;

		case 50: //race home
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"GAME OVER");
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,30,"Well Done");
		display->drawStr(0,40,"Champ");
		break;

		case 52: //press to play again
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,10,"PLAY AGAIN?");
		display->setFont(u8g2_font_t0_16_mr);
		display->drawStr(0,30,"Press button");
		break;
	}
}

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

