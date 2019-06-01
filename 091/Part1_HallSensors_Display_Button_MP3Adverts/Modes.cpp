/*
 * Modes.cpp
 * 
 * Defines functions that control behaviour during game Modes.
 * 
 * By Carl Turner 4 March 2019
 * roundbananas.com
 * 
 */

#include "Modes.h"

#include <AltSoftSerial.h> //check: specific rx tx pins required. https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
#include <DFMiniMp3.h>
#include "Mp3Notify.h"

uint16_t Mp3Count;
int Mp3Track; //will move this to be a state variable once I have tested it
int Mp3BusyPin = 3;
bool Mp3Playing = false;
bool Mp3Ready = false;

int musicVolume = 1;
int voiceVolume = 3;

unsigned long clueDisplayDuration = 2000; //display each clue for this period

unsigned long lastLightning;
unsigned long lightningFrequency = 7000;

AltSoftSerial altSerial; //pins for AltSoftSerial must be TX = 9, RX = 8 on Uno and 46, 48 on Mega
DFMiniMp3<AltSoftSerial, Mp3Notify> mp3(altSerial);

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

/*
 * MODES
 */

Modes Setup(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
 Serial.println("setupMode");

   State_Struct _state;
   _state.startedAt = currentState.startedAt;
   _state.jewelLocation = currentState.jewelLocation; 
   _state.clues = currentState.clues;
   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.lastClue_At = currentState.lastClue_At;
   _state.updateMode = currentState.updateMode;  

   if(!Mp3Ready)
   {
    pinMode(Mp3BusyPin, INPUT); //LOW means playing, HIGH means not playing
    Mp3Ready = true;
    mp3.begin();
    mp3.reset();
    delay (2000);
      
    mp3.setVolume(musicVolume);
    Serial.print("volume ");
    Serial.println(mp3.getVolume());

    Mp3Count = mp3.getTotalTrackCount();
    Serial.print("files ");
    Serial.println(Mp3Count);

    PlayIntro();
    
    delay (2000);
   }
   else if (clueButtonState)
    {
      _state.updateMode = &JewelsHidden; 
      lastLightning = millis();
     

      Serial.println("Scream");
      
     
       PlayBackground1();
        delay(500);
        PlayWizardScream();
    }  

 //State_Struct {unsigned long startedAt, int jewelLocation, char *clues, int clueIndex, bool displayingClue, ModeFn updateMode}
  return (State_Struct) {_state.startedAt, _state.jewelLocation, _state.clues, _state.clueIndex, _state.displayingClue, _state.lastClue_At, _state.updateMode};
 } //End Setup Mode

Modes JewelsHidden(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
      Serial.println("JewelsHiddenMode");
  /*
   * trigger mode change if the jewels are found
   *  play fail sound if wrong location checked
   *  show a random clue if the button is pushed
   */

   State_Struct _state;

   _state.startedAt = currentState.startedAt;
   _state.jewelLocation = currentState.jewelLocation;
   _state.clues = currentState.clues;
   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.updateMode = currentState.updateMode;  

    if (currentTime - lastLightning > lightningFrequency)
    {
      //PlayWizardLightning(); //Need to make this more randomly timed and less frequent perhaps. And mp3 file needs to be very short. 
      lastLightning = millis();
    }

    if (!currentState.displayingClue && clueButtonState)
    {
      //1. DEAL WITH THE BUTTON
        randomSeed(currentTime);
        int clue_Index = random(0, 2); 

        _state.lastClue_At = currentTime;
        _state.clueIndex = clue_Index;
        _state.displayingClue = true;

        mp3.setVolume(voiceVolume);
        PlayGotClue();
    }
    else if (currentState.displayingClue && ((currentTime - currentState.lastClue_At) >= clueDisplayDuration)) //clue timed out
    {
        _state.displayingClue = false;
        mp3.setVolume(musicVolume);
    }

    //2. DEAL WITH THE SENSORS    
    for (int i = 0; i < 3; i++)
    {
      if (hallSensorStates[i] == HIGH && i == currentState.jewelLocation) //jewels are found
      {
        Serial.println("Jewels Found!");
        _state.updateMode = &JewelsFound; 
        _state.startedAt = currentTime;
        // mp3.stop();
        // delay(2000);
         mp3.setVolume(voiceVolume);
         PlayFoundJewels();
         delay(2500);
         PlayWizardWrathSpeach();
         delay(7000);
         mp3.setVolume(musicVolume);
         PlayBackground2();
          
      }
      else if (hallSensorStates[i] == HIGH)
      {
        Serial.println("The Jewels aren't here!");
        mp3.setVolume(voiceVolume);
        PlayWrongJewels();
      }
    }
    
    return (State_Struct) {_state.startedAt, _state.jewelLocation, _state.clues, _state.clueIndex, _state.displayingClue, _state.lastClue_At, _state.updateMode};
    
} //End JewelsHidden Mode

Modes JewelsFound(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
  Serial.println("JewelsFoundMode");
  State_Struct _state;

   _state.startedAt = currentState.startedAt;
   _state.jewelLocation = currentState.jewelLocation; 
   _state.clues = currentState.clues;
   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.updateMode = currentState.updateMode;  

    if (clueButtonState)
    {
      PlayWinnerSong();
      delay(6000);
      _state.updateMode = &GameOver; 

    }

    return (State_Struct) {_state.startedAt, _state.jewelLocation, _state.clues, _state.clueIndex, _state.displayingClue, _state.lastClue_At, _state.updateMode};

} //End JewelsFound Mode

Modes GameOver(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
   Serial.println("GameOverMode");

  State_Struct _state;

   _state.startedAt = currentState.startedAt;
   _state.jewelLocation = currentState.jewelLocation; 
   _state.clues = currentState.clues;
   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.updateMode = currentState.updateMode;  

  if (clueButtonState)
    {
      _state.updateMode = &Setup; 
    }

       return (State_Struct) {_state.startedAt, _state.jewelLocation, _state.clues, _state.clueIndex, _state.displayingClue, _state.lastClue_At, _state.updateMode};
  }//End GameOver Mode
