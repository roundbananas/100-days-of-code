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
	//Declare and initialise variables that'll represent the new state
	State_Struct _state;

	_state.updateMode = &Setup; 

	_state.mode_StartedAt = currentState.mode_StartedAt;
    _state.jewelLocation = currentState.jewelLocation;
    _state.clues = currentState.clues;

    _state.lastClue_At = currentState.lastClue_At;
    _state.lastLightning = currentState.lastLightning;

    _state.clueIndex = currentState.clueIndex;
    _state.displayingClue = currentState.displayingClue;

   	_state.msgSystemIndex = currentState.msgSystemIndex;
    _state.displayingSystemMsg = currentState.displayingSystemMsg;

    _state.msgCreditsIndex = currentState.msgCreditsIndex;
    _state.displayingCreditMsg = currentState.displayingCreditMsg;

    _state.msgGameIndex = currentState.msgGameIndex;
    _state.displayingGameMsg = currentState.displayingGameMsg;

    _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
    _state.Mp3Playing = currentState.Mp3Playing;
    _state.Mp3Ready = currentState.Mp3Ready;

    //NOW LET'S DO OUR SETUP BEHAVIOUR AND UPDATE RELEVANT STATE VARIABLES
    //BEFORE RETURNING THE UPDATED STATE

    //Handle input
    if(clueButtonState)
    {
    	_state.updateMode = &JewelsHidden;
    	_state.mode_StartedAt = currentTime;
    	_state.msgSystemIndex = 0;
    	_state.displayingSystemMsg = false;
    	_state.msgGameIndex = 2;
    	_state.displayingGameMsg = true;
    }
    else 
    {
    	//Handle display status
    	if (currentTime - currentState.mode_StartedAt > 6000)
    	{
    		_state.msgSystemIndex = 0;
    		_state.displayingSystemMsg = false;
    		_state.msgGameIndex = 1;
    		_state.displayingGameMsg = true;
    	}
    	else if (currentTime - currentState.mode_StartedAt > 2000)
    	{
    		_state.msgSystemIndex = 2;
    		_state.displayingSystemMsg = true;
    	}
    	else
    	{
    		_state.msgSystemIndex = 1;
    		_state.displayingSystemMsg = true;
    	}
    	
    }
    
	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning, 

							_state.clueIndex, 
							_state.displayingClue, 

							_state.msgSystemIndex,
    						_state.displayingSystemMsg,

    						_state.msgCreditsIndex,
    						_state.displayingCreditMsg,

    						_state.msgGameIndex,
    						_state.displayingGameMsg,

							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
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

   	_state.msgSystemIndex = currentState.msgSystemIndex;
    _state.displayingSystemMsg = currentState.displayingSystemMsg;

    _state.msgCreditsIndex = currentState.msgCreditsIndex;
    _state.displayingCreditMsg = currentState.displayingCreditMsg;

    _state.msgGameIndex = currentState.msgGameIndex;
    _state.displayingGameMsg = currentState.displayingGameMsg;

    _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
    _state.Mp3Playing = currentState.Mp3Playing;
    _state.Mp3Ready = currentState.Mp3Ready;

	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning, 

							_state.clueIndex, 
							_state.displayingClue, 

							_state.msgSystemIndex,
    						_state.displayingSystemMsg,

    						_state.msgCreditsIndex,
    						_state.displayingCreditMsg,

    						_state.msgGameIndex,
    						_state.displayingGameMsg,

							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
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

   	_state.msgSystemIndex = currentState.msgSystemIndex;
    _state.displayingSystemMsg = currentState.displayingSystemMsg;

    _state.msgCreditsIndex = currentState.msgCreditsIndex;
    _state.displayingCreditMsg = currentState.displayingCreditMsg;

    _state.msgGameIndex = currentState.msgGameIndex;
    _state.displayingGameMsg = currentState.displayingGameMsg;

    _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
    _state.Mp3Playing = currentState.Mp3Playing;
    _state.Mp3Ready = currentState.Mp3Ready;

	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning, 

							_state.clueIndex, 
							_state.displayingClue, 

							_state.msgSystemIndex,
    						_state.displayingSystemMsg,

    						_state.msgCreditsIndex,
    						_state.displayingCreditMsg,

    						_state.msgGameIndex,
    						_state.displayingGameMsg,

							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
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

   	_state.msgSystemIndex = currentState.msgSystemIndex;
    _state.displayingSystemMsg = currentState.displayingSystemMsg;

    _state.msgCreditsIndex = currentState.msgCreditsIndex;
    _state.displayingCreditMsg = currentState.displayingCreditMsg;

    _state.msgGameIndex = currentState.msgGameIndex;
    _state.displayingGameMsg = currentState.displayingGameMsg;

    _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
    _state.Mp3Playing = currentState.Mp3Playing;
    _state.Mp3Ready = currentState.Mp3Ready;

	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning, 

							_state.clueIndex, 
							_state.displayingClue, 

							_state.msgSystemIndex,
    						_state.displayingSystemMsg,

    						_state.msgCreditsIndex,
    						_state.displayingCreditMsg,

    						_state.msgGameIndex,
    						_state.displayingGameMsg,

							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
							_state.updateMode};

}
