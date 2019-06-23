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

//typedef void (*SensorFn)();	//declare *SensorFn(), a pointer to a function that returns void.

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
	  	char *msgGame[9] = {" ", "Press Button to Start", "Go!", "YOU FOUND THE JEWELS!", "No Jewels Here", "GAME OVER", "Press for Clue", "Get back to start!", "Winner press button"};
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
		//byte m_SensorPins[m_NumSensors] = {A8, A9, A10};
		byte m_SensorPins[m_NumSensors] = {50, 51, 52};

		 byte m_OLED_clk = 13;   //to D0/SCK/SCL on display
		 byte m_OLED_data = 11;  //to D1/MOSI/SDA on display
		 byte m_OLED_cs = 10;    //to CS on display
		 byte m_OLED_dc = 7;     //to DC on display
		 byte m_OLED_reset = 6;  //to RES on display

		int Mp3BusyPin = 3;

  	/******** GAME VARIABLES *********/
		volatile bool m_Sensor1State = 0;
		volatile bool m_Sensor2State = 0;
		volatile bool m_Sensor3State = 0;
		bool m_SensorStates[3] = {m_Sensor1State, m_Sensor2State, m_Sensor3State}; //declared as volatile cos that's what the pinchange interrupt requires
    	State m_state;


/******** GAME OBJECTS *********/
	    //declare pointers to game object types we want to create
	    ButtonMom *m_Buttons = nullptr;
	    //ButtonMom m_Button;
	    U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI *m_OledDisplay = nullptr;


	/*
	 * GAME SETUP HELPER FUNCTIONS
	 */
	int HideTheJewels(int randomReading);

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

	    void m_SetPage(byte page, bool displayClue, char *clue, U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI *display);

  public:
    //Engine();
    Engine(void* interruptDispatch1, void* interruptDispatch2, void* interruptDispatch3);
    void runEngine();
   // int getNumSensors();
   //byte getSensorPin(int index);
	//updateSensor functions are called when a 'CHANGE' is registered by the sensor
		 void updateSensor1(); 		//define updateSensor1, a function that returns void
		 void updateSensor2();
		 void updateSensor3();
    
};
#endif