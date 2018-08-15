/*
 * Carl Turner 2018
 * roundbanans.com
 * 
 *forward declarations for
 * - state names
 * - state variables (struct)
 * - mode functions 
 * 
*/

#ifndef State_h
#define State_h

//list of all possible game modes. The enum GameState isn't used yet in this program.
enum GameState
{
  IDLE_MODE,        //go to PlayingMode on button1 push
  PLAYING_MODE,     //go to BeatLevelMode on beatLevel = true, go to GameOverMode if gameOver = true, go to IdleMode on timeOut
  BEAT_LEVEL_MODE,  //go to PlayingMode on button1 push, go to IdleMode on timeOut
  GAME_OVER_MODE,   //go to IdleMode on timeOut
};

//forward declaration of ModeFn type, which is a type used in the State_struct
typedef struct State_struct (*ModeFn)(struct State_struct current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading);

typedef struct State_struct {
  ModeFn modeFn;                  //holds the current mode
  unsigned long mode_started_at;  //holds the time the current mode started

  //include other relevant variables that define the state
  int score;
  int current_level;
} State; //alias for State_struct

//forward declarations for modes. Implementations are defined in GameModel.cpp
State IdleMode (State current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading);
State PlayingMode (State current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading);
State BeatLevelMode (State current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading);
State GameOverMode (State current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading);

#endif
