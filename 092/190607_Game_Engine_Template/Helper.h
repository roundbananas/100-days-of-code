/*
*	Helper.h
*
*	Created by Carl Turner 7 June 2019
*
* Defines helper functions specific to a certain game, that would just clutter the Engine.
*/

#ifndef Helper_h
#define Helper_h

#include "Arduino.h"


/*
 * DISPLAY HELPER FUNCTIONS
 */
void startDisplay(U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2)
{
  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_t0_16_mr); // choose a suitable font
  u8g2.drawStr(0,10,"Starting Display");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay (1000);
}

/*
 * SENSOR HELPER FUNCTIONS
 */
//Create an array of update sensor functions, so it's easier to loop through and attach pin interrupts
	//I'm trying to optimise this process. It could be better.
	typedef bool (*SensorFn)();	//declare *SensorFn(), a pointer to a function that returns void.

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
	SensorFn updateHallSensors[] = {updateSensor1(),updateSensor2(), updateSensor3()};


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
      state.clues.possibleClues[0] = clueOptions[1];
      state.clues.possibleClues[1] = clueOptions[2];
      Serial.println("Volcano");
      break;
    case 1: //mine has jewels
      state.clues.possibleClues[0] = clueOptions[0];
      state.clues.possibleClues[1] = clueOptions[2];
      Serial.println("Mine");
      break;
    case 2: //swamp has jewels
      state.clues.possibleClues[0] = clueOptions[0];
      state.clues.possibleClues[1] = clueOptions[1];
      Serial.println("Swamp");
      break;  
  }  
  return location;
}






/*
 * MP3 HELPER FUNCTIONS
 */
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


#endif