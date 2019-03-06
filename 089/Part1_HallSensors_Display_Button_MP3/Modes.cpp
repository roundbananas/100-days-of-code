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

unsigned long clueDisplayDuration = 2000; //display each clue for this period

AltSoftSerial altSerial; //pins for AltSoftSerial must be TX = 9, RX = 8 on Uno and 46, 48 on Mega
DFMiniMp3<AltSoftSerial, Mp3Notify> mp3(altSerial);

Modes Setup(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
 Serial.println("setupMode");

  pinMode(Mp3BusyPin, INPUT); //LOW means playing, HIGH means not playing

  mp3.begin();
  mp3.reset();
  delay (2000);
    
  mp3.setVolume(6);
  Serial.print("volume ");
  Serial.println(mp3.getVolume());

  Mp3Count = mp3.getTotalTrackCount();
  Serial.print("files ");
  Serial.println(Mp3Count);

  Serial.println("Playing Track 3");
  mp3.playMp3FolderTrack(3);
  delay(2500);

  Serial.println("Playing Track 4");
  mp3.playMp3FolderTrack(4);
  

 //State_Struct {unsigned long startedAt, int jewelLocation, char *clues, int clueIndex, bool displayingClue, ModeFn updateMode}
 return (State_Struct) {currentTime, currentState.jewelLocation, currentState.clues, currentState.clueIndex, false, &JewelsHidden}; 
 } //End Setup Mode

Modes JewelsHidden(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
      Serial.println("JewelsHiddenMode");
  /*
   * trigger mode change if the jewels are found
   *  play fail sound if wrong location checked
   *  show a random clue if the button is pushed
   */

   Serial.println(mp3.getStatus()); //returns 513 if playing

   State_Struct _state;

   _state.startedAt = currentState.startedAt;
   _state.jewelLocation = currentState.jewelLocation;
   _state.clues = currentState.clues;
   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.updateMode = currentState.updateMode;  

    if (!currentState.displayingClue && clueButtonState)
    {
      //1. DEAL WITH THE BUTTON
        randomSeed(currentTime);
        int clue_Index = random(0, 2); 

        _state.startedAt = currentTime;
        _state.clueIndex = clue_Index;
        _state.displayingClue = true;
    }
    else if (currentState.displayingClue && ((currentTime - currentState.startedAt) >= clueDisplayDuration)) //clue timed out
    {
        _state.displayingClue = false;
    }

    //2. DEAL WITH THE SENSORS    
    for (int i = 0; i < 3; i++)
    {
      if (hallSensorStates[i] == HIGH && i == currentState.jewelLocation) //jewels are found
      {
        Serial.println("Jewels Found!");
        _state.updateMode = &JewelsFound; 
         Serial.println("Playing Track 6");
         mp3.playMp3FolderTrack(6);
         delay(2500);
          Serial.println("Playing Track 8");
          mp3.playMp3FolderTrack(8);
      }
      else if (hallSensorStates[i] == HIGH)
      {
        Serial.println("The Jewels aren't here!");
      }
    }
    return (State_Struct) {_state.startedAt, _state.jewelLocation, _state.clues, _state.clueIndex, _state.displayingClue, _state.updateMode};
    
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

    return (State_Struct) {_state.startedAt, _state.jewelLocation, _state.clues, _state.clueIndex, _state.displayingClue, _state.updateMode};

} //End JewelsFound Mode

Modes GameOver(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
   Serial.println("GameOverMode");
  }//End GameOver Mode
