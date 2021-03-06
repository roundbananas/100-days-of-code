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
#include "PinChangeInterrupt.h" //https://github.com/NicoHood/PinChangeInterrupt


class Engine
{
  private:
    /******** CONSTANTS *********/
	//GAME SETTINGS (constants)
		const static int m_NumButtons = 1;
	    const static int m_NumDisplays = 1;
	    const static int m_NumSensors = 3;

	  	char *clueOptions[3] = {"NOT volcano", "NOT Mine", "NOT Swamp"};
	  	char *msgSystem[4] = {" ", "Starting...", "Wizard's Wrath", "v0.1"};
	  	char *msgCredits[4] = {" ", "Steve Grasso", "Carl Turner", "2019"};
	  	char *msgGame[4] = {" ", "Press Button to Start", "Go!", "GAME OVER"};
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

  	/******** GAME VARIABLES *********/
		volatile bool m_SensorStates[3] = {0}; //declared as volatile cos that's what the pinchange interrupt requires
    	State m_state;


/******** GAME OBJECTS *********/
	    //declare pointers to game object types we want to create
	    ButtonMom *m_Buttons = nullptr;
	    //ButtonMom m_Button;
	    U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI *m_OledDisplay = nullptr;

		typedef void (*SensorFn)();	//declare *SensorFn(), a pointer to a function that returns void.

		//updateSensor functions are called when a 'CHANGE' is registered by the sensor
		SensorFn updateSensor1() 		//define updateSensor1, a function that returns void
		{ 
		    m_SensorStates[0] = !m_SensorStates[0]; 
		} 

		SensorFn updateSensor2() 
		{
		    m_SensorStates[1] = !m_SensorStates[1];
		} 

		SensorFn updateSensor3() 
		{
		    m_SensorStates[2] = !m_SensorStates[2];
		} 

		//define updateHAllSensors[], an array whose elements are functions that return void
		SensorFn updateHallSensors[m_NumSensors] = {updateSensor1(),updateSensor2(), updateSensor3()};


	void CreateSensors(int numSensors, byte sensorPins[])
	{
	  //setup to the interrupt to toggle sensor states
	  for (int i = 0; i < numSensors; i++)
	  {
	  	m_SensorStates[i] = LOW;	
	    pinMode(sensorPins[i], INPUT_PULLUP);
	  	attachPCINT(digitalPinToPCINT(sensorPins[i]), updateHallSensors[i], CHANGE);
	  }
	}


	/* HEPLERS */
	/*
 * DISPLAY HELPER FUNCTIONS
 */


	/*
	 * GAME SETUP HELPER FUNCTIONS
	 */
	int HideTheJewels(int randomReading)
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

/*
	
	 * MP3 HELPER FUNCTIONS
	 
	 //long tracks
	 void PlayIntro() {mp3.playMp3FolderTrack(1);};
	 void PlayBackground1() { mp3.playMp3FolderTrack(2);}; //sd:/mp3/0001.mp3
	 void PlayBackground2() { mp3.playMp3FolderTrack(3);};
	 void PlayWinnerSong() {mp3.playMp3FolderTrack(4);};
	 void PlayWizardWrathSpeach() { mp3.playMp3FolderTrack(5);};

	 //'advertisement' tracks (interrupt current track while they play)
	 void PlayGotClue() {mp3.playAdvertisement(1);};          //sd:/advert/0001.mp3
	 void PlayFoundJewels() { mp3.playAdvertisement(2);};
	 void PlayWrongJewels() {mp3.playAdvertisement(3);};
	 
	 void PlayWizardScream() {  mp3.playAdvertisement(4);};
	 void PlayWizardLightning() {mp3.playAdvertisement(5);};
*/

  	/******** GAME ENGINE FUNCTIONS *********/
	    void m_Input(unsigned long t);
	    void m_Update(unsigned long t);
	    void m_Render();

  public:
    Engine();
    void runEngine();
    
};
#endif