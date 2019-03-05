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
#include "Arduino.h"

Modes Setup(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
 Serial.println("setupMode");
 //State_Struct {unsigned long startedAt, int jewelLocation, char *clues, int clueIndex, bool displayingClue, ModeFn updateMode}
 return (State_Struct) {currentTime, currentState.jewelLocation, currentState.clues, currentState.clueIndex, false, &JewelsHidden}; 
 } //End Setup Mode

Modes JewelsHidden(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
      Serial.println("JewelsHiddenMode");
  /*
   * trigger mode change if the jewels are found
   * else, play fail sound if wrong location checked
   * else, show a random clue if the button is pushed
   */
  for (int i = 0; i < 3; i++)
  {
    if (hallSensorStates[i] == HIGH && i == currentState.jewelLocation) //jewels are found
    {
      Serial.println("Jewels Found!");
      return (State_Struct) {currentTime, currentState.jewelLocation, currentState.clues, currentState.clueIndex, false, &JewelsFound};
    }
    else if (hallSensorStates[i] == HIGH)
    {
      Serial.println("The Jewels aren't here!");
      return (State_Struct) {currentTime, currentState.jewelLocation, currentState.clues, currentState.clueIndex, false, &JewelsHidden};
    }
  }
  if (clueButtonState)
  {
      randomSeed(millis());
      int clue_Index = random(0, 2); 
      return (State_Struct) {currentTime, currentState.jewelLocation, currentState.clues, clue_Index, true, &JewelsHidden};
  }
} //End JewelsHidden Mode

Modes JewelsFound(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
  Serial.println("JewelsFoundMode");
  return (State_Struct) {currentTime, currentState.jewelLocation, currentState.clues, currentState.clueIndex, false, &JewelsFound}; 

} //End JewelsFound Mode

Modes GameOver(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState){
   Serial.println("GameOverMode");
  }//End GameOver Mode
