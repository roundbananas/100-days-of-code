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
    
    _state.updateMode = currentState.updateMode; 

    _state.mode_StartedAt = currentState.mode_StartedAt;
    _state.jewelLocation = currentState.jewelLocation;
    _state.clues = currentState.clues;

    _state.lastClue_At = currentState.lastClue_At;
    _state.lastLightning = currentState.lastLightning;
    _state.lastPageAt = currentState.lastPageAt;

    _state.clueIndex = currentState.clueIndex;
    _state.displayingClue = currentState.displayingClue;

    _state.currentPage = currentState.currentPage;
    _state.displayingPage = currentState.displayingPage;

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
        _state.currentPage = 10; //GO!
    	_state.displayingPage = true;
    }
    else 
    {
    	//Update display content
    	if (currentTime - currentState.mode_StartedAt > 10000)
    	{
            _state.currentPage = 2; //Press button to start
            _state.displayingPage = true;
    	}
    	else if (currentTime - currentState.mode_StartedAt > 2000)
    	{
            _state.currentPage = 1; //Title page
            _state.displayingPage = true;
    	}
    	else
    	{
    		_state.currentPage = 0; //Starting...
    		_state.displayingPage = true;
    	}
    	
    }
    
	return (State_Struct) {	_state.jewelLocation, 
							_state.clues, 
							_state.mode_StartedAt,	
							_state.lastClue_At, 
							_state.lastLightning,
                            _state.lastPageAt, 

							_state.clueIndex, 
							_state.displayingClue, 

							_state.currentPage,
    						_state.displayingPage,

							_state.MP3CurrentTrack,
							_state.Mp3Playing, 
							_state.Mp3Ready, 		
							_state.updateMode};
}

State JewelsHidden(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState)
{
	Serial.print ("JewelsHidden Mode");
	State_Struct _state;

	_state.updateMode = currentState.updateMode; 

    _state.mode_StartedAt = currentState.mode_StartedAt;
    _state.jewelLocation = currentState.jewelLocation;
    _state.clues = currentState.clues;

    _state.lastClue_At = currentState.lastClue_At;
    _state.lastLightning = currentState.lastLightning;
    _state.lastPageAt = currentState.lastPageAt;

    _state.clueIndex = currentState.clueIndex;
    _state.displayingClue = currentState.displayingClue;

    _state.currentPage = currentState.currentPage;
    _state.displayingPage = currentState.displayingPage;

    _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
    _state.Mp3Playing = currentState.Mp3Playing;
    _state.Mp3Ready = currentState.Mp3Ready;

    /*
    * trigger mode change if the jewels are found
    *  play fail sound if wrong location checked
    *  show a random clue if the button is pushed
    */

//Keep displaying the last msg from SetupMode for a few seconds, before displaying anyhthing else
        if (currentTime - currentState.mode_StartedAt <= 3000)
        {
            _state.currentPage = 10; //GO!
            _state.displayingPage = true;
        }
        //Handle clues
        else if (currentTime - currentState.lastPageAt > 2000)
        {
            if(!currentState.displayingClue && clueButtonState)    //player wants a clue
            {  
                //1. DEAL WITH THE BUTTON
                randomSeed(currentTime);
                int clue_Index = random(0, 2); 

                _state.lastClue_At = currentTime;
                _state.clueIndex = clue_Index;
                _state.displayingClue = true;
                _state.currentPage = 12; //CLUE
                _state.displayingPage = true;


                //PlayGotClue();
            }
            else if (currentState.displayingClue && ((currentTime - currentState.lastClue_At) >= 2000)) //clue timed out
            {
                _state.displayingClue = false;
            }
            else if(!currentState.displayingClue)
            {
                _state.currentPage = 11; //Press for clue!
                _state.displayingPage = true;
            }
        }
            //Handle the sensors
                for (int i = 0; i < numSensors; i++)
                {
                  if ((hallSensorStates[i] == LOW) && (i == currentState.jewelLocation)) //jewels are found
                  {
                    Serial.println("Jewels Found!");
                    _state.updateMode = &JewelsFound; 
                    _state.mode_StartedAt = currentTime;
                    
                    _state.currentPage = 21; //Moment of truth - jewels found
                    _state.displayingPage = true;
                      
                  }
                  else if (hallSensorStates[i] == LOW)
                  {
                    Serial.println("The Jewels aren't here!");
                    //PlayWrongJewels();
                    _state.currentPage = 20; //Moment of truth - no jewels
                    _state.displayingPage = true;
                    _state.lastPageAt = currentTime;
                  }
                }

    return (State_Struct) { _state.jewelLocation, 
                            _state.clues, 
                            _state.mode_StartedAt,  
                            _state.lastClue_At, 
                            _state.lastLightning,
                            _state.lastPageAt, 

                            _state.clueIndex, 
                            _state.displayingClue, 

                            _state.currentPage,
                            _state.displayingPage,

                            _state.MP3CurrentTrack,
                            _state.Mp3Playing, 
                            _state.Mp3Ready,        
                            _state.updateMode};
}

State JewelsFound(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState)
{
	Serial.print ("JewelsFound Mode");
	State_Struct _state;

    _state.updateMode = currentState.updateMode; 

    _state.mode_StartedAt = currentState.mode_StartedAt;
    _state.jewelLocation = currentState.jewelLocation;
    _state.clues = currentState.clues;

    _state.lastClue_At = currentState.lastClue_At;
    _state.lastLightning = currentState.lastLightning;
    _state.lastPageAt = currentState.lastPageAt;

    _state.clueIndex = currentState.clueIndex;
    _state.displayingClue = currentState.displayingClue;

    _state.currentPage = currentState.currentPage;
    _state.displayingPage = currentState.displayingPage;

    _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
    _state.Mp3Playing = currentState.Mp3Playing;
    _state.Mp3Ready = currentState.Mp3Ready;

    if (currentTime - currentState.mode_StartedAt <= 4000)
        {
            _state.displayingClue = false;
            _state.currentPage = 21; //Moment of truth - jewels found
            _state.displayingPage = true;
        }
        else if (clueButtonState)
        {
            _state.updateMode = &GameOver;
            _state.mode_StartedAt = currentTime;
        }
        else
        {
            _state.currentPage = 22; //Race home
            _state.displayingPage = true;
             
        }

    return (State_Struct) { _state.jewelLocation, 
                            _state.clues, 
                            _state.mode_StartedAt,  
                            _state.lastClue_At, 
                            _state.lastLightning,
                            _state.lastPageAt, 

                            _state.clueIndex, 
                            _state.displayingClue, 

                            _state.currentPage,
                            _state.displayingPage,

                            _state.MP3CurrentTrack,
                            _state.Mp3Playing, 
                            _state.Mp3Ready,        
                            _state.updateMode};
}
State GameOver(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState)
{
	Serial.print ("GameOver Mode");
	State_Struct _state;

    _state.updateMode = currentState.updateMode; 

    _state.mode_StartedAt = currentState.mode_StartedAt;
    _state.jewelLocation = currentState.jewelLocation;
    _state.clues = currentState.clues;

    _state.lastClue_At = currentState.lastClue_At;
    _state.lastLightning = currentState.lastLightning;
    _state.lastPageAt = currentState.lastPageAt;

    _state.clueIndex = currentState.clueIndex;
    _state.displayingClue = currentState.displayingClue;

    _state.currentPage = currentState.currentPage;
    _state.displayingPage = currentState.displayingPage;

    _state.MP3CurrentTrack = currentState.MP3CurrentTrack;
    _state.Mp3Playing = currentState.Mp3Playing;
    _state.Mp3Ready = currentState.Mp3Ready;

    if (currentTime - currentState.mode_StartedAt <= 5000)
    {
        _state.currentPage = 50; //Game Over
        _state.displayingPage = true;
    }
    else
    {

        _state.currentPage = 52; //Press button to play Again
        _state.displayingPage = true;
        if(clueButtonState)
        {
            _state.updateMode = &Setup;
            _state.mode_StartedAt = currentTime;
            _state.displayingPage = false;
            delay(1000);    //prevents registering a double press of button and jumping straight into playing mode again.
        }
    }

    return (State_Struct) { _state.jewelLocation, 
                            _state.clues, 
                            _state.mode_StartedAt,  
                            _state.lastClue_At, 
                            _state.lastLightning,
                            _state.lastPageAt, 

                            _state.clueIndex, 
                            _state.displayingClue, 

                            _state.currentPage,
                            _state.displayingPage,

                            _state.MP3CurrentTrack,
                            _state.Mp3Playing, 
                            _state.Mp3Ready,        
                            _state.updateMode};

}
