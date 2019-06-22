/*
*	Modes.cpp
*
*	Created by Carl Turner 7 June 2019
*/

/*
 * MODE: Setup
 * The program randomly assigns one of three locations as having the 'jewels'.
 * When setup is complete, trigger JewelsHidden mode.
 * 
 * MODE: JewelsHidden
 * When the clueButton is pushed, a clue is displayed on the OLED.
 * 
 * There are three hall sensors, one for each of location.
 * When a hall sensor corresponding to false jewel location is triggered, let player know.
 * 
 * When the hall sensor corresponding the jewel location is triggered, the jewels have been 'found':
 * - go to Jewels_Found mode
 * 
 * MODE: JewelsFound 
 * - does nothing yet 
 * 
 */

#include "State.h"

State Setup(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState)
{
	Serial.print ("Setup Mode");
	State_Struct _state;
	_state.updateMode = &JewelsHidden; 


	_state.mode_StartedAt = currentState.mode_StartedAt;
   _state.jewelLocation = currentState.jewelLocation;
   _state.clues = currentState.clues;

   _state.lastClue_At = currentState.lastClue_At;
   _state.lastLightning = currentState.lastLightning;

   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
   _state.Mp3Playing = currentState.Mp3Playing;
   _state.Mp3Ready = currentState.Mp3Ready;

   for (int i = 0; i < numSensors; i++) _state.sensorStates[i] = currentState.sensorStates[i];
   _state.updateMode = currentState.updateMode;  

	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning, 
							_state.clueIndex, 
							_state.displayingClue, 
							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
							_state.sensorStates, 
							_state.updateMode};
}

State JewelsHidden(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState)
{
	Serial.print ("JewelsHidden Mode");
		State_Struct _state;
	_state.updateMode = &JewelsFound; 


	_state.mode_StartedAt = currentState.mode_StartedAt;
   _state.jewelLocation = currentState.jewelLocation;
   _state.clues = currentState.clues;

   _state.lastClue_At = currentState.lastClue_At;
   _state.lastLightning = currentState.lastLightning;

   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
   _state.Mp3Playing = currentState.Mp3Playing;
   _state.Mp3Ready = currentState.Mp3Ready;

   for (int i = 0; i < numSensors; i++) _state.sensorStates[i] = currentState.sensorStates[i];
   _state.updateMode = currentState.updateMode;  

	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning, 
							_state.clueIndex, 
							_state.displayingClue, 
							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
							_state.sensorStates, 
							_state.updateMode};

}
State JewelsFound(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState)
{
	Serial.print ("JewelsFound Mode");
	State_Struct _state;
	_state.updateMode = &GameOver; 


	_state.mode_StartedAt = currentState.mode_StartedAt;
   _state.jewelLocation = currentState.jewelLocation;
   _state.clues = currentState.clues;

   _state.lastClue_At = currentState.lastClue_At;
   _state.lastLightning = currentState.lastLightning;

   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
   _state.Mp3Playing = currentState.Mp3Playing;
   _state.Mp3Ready = currentState.Mp3Ready;

   for (int i = 0; i < numSensors; i++) _state.sensorStates[i] = currentState.sensorStates[i];
   _state.updateMode = currentState.updateMode;  

	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning, 
							_state.clueIndex, 
							_state.displayingClue, 
							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
							_state.sensorStates, 
							_state.updateMode};
}
State GameOver(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState)
{
	Serial.print ("GameOver Mode");
	State_Struct _state;
	_state.updateMode = &JewelsHidden; 


	_state.mode_StartedAt = currentState.mode_StartedAt;
   _state.jewelLocation = currentState.jewelLocation;
   _state.clues = currentState.clues;

   _state.lastClue_At = currentState.lastClue_At;
   _state.lastLightning = currentState.lastLightning;

   _state.clueIndex = currentState.clueIndex;
   _state.displayingClue = currentState.displayingClue;
   _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
   _state.Mp3Playing = currentState.Mp3Playing;
   _state.Mp3Ready = currentState.Mp3Ready;

   for (int i = 0; i < numSensors; i++) _state.sensorStates[i] = currentState.sensorStates[i];
   _state.updateMode = currentState.updateMode;  

	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning, 
							_state.clueIndex, 
							_state.displayingClue, 
							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
							_state.sensorStates, 
							_state.updateMode};

}
