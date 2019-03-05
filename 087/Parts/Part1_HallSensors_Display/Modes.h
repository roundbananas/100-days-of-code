/*
 * Modes.h
 * 
 * Declares functions that control behaviour during game Modes.
 * Declares State, comprised on several key variables.
 * 
 * By Carl Turner 4 March 2019
 * roundbananas.com
 * 
 * Triggers
 * byte jewelLocation       for checking any hall readings
 * bool hallSensor[i]       if i != jewelLocation, triggers fail song. If i = jewelLocation, trigger success song and Jewels_Found mode
 * bool clueButton          for OLED display timer
 * bool setupComplete       setup --> Jewels_Not_Found        
 * ul   lastClueRequestAt   for OLED display timer
 */

 #ifndef Modes_h
 #define Modes_h

typedef struct { char *clue1; char *clue2;} Clues;

typedef struct State_Struct (*ModeFn)(struct State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState);

typedef struct State_Struct {
  unsigned long startedAt;          //might use in future to trigger additional audio
  int jewelLocation;               //can be 0, 1 or 2
  Clues clues;                    //holds two possible clues, given the current jewelLocation
  int clueIndex;                //holds index to current clue to display
  bool displayingClue;
  ModeFn updateMode;              //defines behaviour during each game mode
} Modes;

Modes Setup(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState);
Modes JewelsHidden(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState);
Modes JewelsFound(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState);
Modes GameOver(State_Struct currentState, unsigned long currentTime, bool hallSensorStates[], bool clueButtonState);

 #endif
