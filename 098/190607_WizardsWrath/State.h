/*
*	State.h
*
*	Created by Carl Turner 7 June 2019
*/
/*
 * Note: 
 * 	State = instantenous state of the game at any specific point in time.
 *	Mode  = how the game behaves, given a certain State. 
 *
 * TRIGGERS FOR MODE CHANGES
 * byte jewelLocation       for checking any hall readings
 * bool hallSensor[i]       if i != jewelLocation, triggers fail song. If i = jewelLocation, trigger success song and Jewels_Found mode
 * bool clueButton          for OLED display timer
 * bool setupComplete       setup --> Jewels_Not_Found        
 * ul   lastClueRequestAt   for OLED display timer
 */

 #ifndef State_h
 #define State_h

#include "Arduino.h"

//Declare a pointer to an array of char variables, which we need in order to be able to define the State_Struct variable
typedef struct { char *possibleClues[2] = {"null", "null"};} Clues;

//Declare a pointer to a function that returns the a State_Struct type variable (i.e. the state)
//We need to forward declare this so we can define the State_Struct, which contains this function as one of its variables
typedef struct State_Struct (*ModeFn)(struct State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState);

//Define the State_Struct, which will hold the state of the game at any time
typedef struct State_Struct {
	//Keeping track of Game Setup variables. These are unique to each game, but don't change during each game. They could be moved out of State 
  	int jewelLocation;               //can be 0, 1 or 2
  	Clues clues;                    //holds two possible clues, given the current jewelLocation

	//Keeping track of timing
  	unsigned long mode_StartedAt;     
  	unsigned long lastClue_At;		//what time the last clue displayed 
  	unsigned long lastLightning;
    unsigned long lastPageAt;

  	//What's happening at this instant?
  	int clueIndex;                	//holds index of current clue to display
	  bool displayingClue;

    byte currentPage;
    bool displayingPage;

 	  int MP3CurrentTrack;
  	bool Mp3Playing;
  	bool Mp3Ready;
  	ModeFn updateMode;              //What mode are we currently in? This function defines behaviour during each game mode
} State;

//Forward declare functions that update and return the State, depending on the current mode.
//Each of these function definitions may be quite large, so they're defined in Modes.cpp
State Setup(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState);
State JewelsHidden(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState);
State JewelsFound(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState);
State GameOver(State_Struct currentState, unsigned long currentTime, int numSensors, bool hallSensorStates[], bool clueButtonState);


 #endif
