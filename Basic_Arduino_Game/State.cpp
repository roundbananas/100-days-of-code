/*
 * Carl Turner 2018
 * roundbanans.com
 * 
 * defines implementations of mode functions
 */

#include "State.h" //include the forward declarations of the structures and functions we'll use
#include "Arduino.h"

extern int timeOut;
extern int beatLevelScore;

State IdleMode (State current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading){
 // Serial.println("IdleMode");

  //Update the state
  State new_state; //create a temporary variable to hold the updated state
  new_state.modeFn = current_state.modeFn;
  new_state.mode_started_at = current_state.mode_started_at;
  new_state.score = current_state.score;
  new_state.current_level = current_state.current_level;
  if(!start_button_reading) //if the button is pushed transition to PlayingMode
  {
     Serial.println("Transition to PlayingMode");
     new_state.modeFn = &PlayingMode;
     new_state.mode_started_at = current_time;
  }
  return new_state;
}

State PlayingMode (State current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading){
 // Serial.println("PlayingMode");

  //Update the state
  State new_state; //create a temporary variable to hold the updated state
  new_state.modeFn = current_state.modeFn;
  new_state.mode_started_at = current_state.mode_started_at;
  new_state.score = current_state.score;
  new_state.current_level = current_state.current_level;
  
  if(!fire_button_reading) //I'm assuming firing adds score for now.
    {
      new_state.score++;
    }

  if(current_state.score >= beatLevelScore) 
  {
    Serial.println("Transition to BeatLevelMode");
    new_state.modeFn = &BeatLevelMode;
    new_state.mode_started_at = current_time;
    new_state.current_level = current_state.current_level;
  }
  if((current_time - current_state.mode_started_at) > timeOut) //change this to a death condition eventually
  {
    Serial.println("Transition to GameOverMode");
    new_state.modeFn = &GameOverMode;
    new_state.mode_started_at = current_time;
    new_state.score = 0;
    new_state.current_level = 0;
  }
  return new_state; 
}

State BeatLevelMode (State current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading){
 // Serial.println("BeatLevelMode");

  //Update the state
  State new_state; //create a temporary variable to hold the updated state
  new_state.modeFn = current_state.modeFn;
  new_state.mode_started_at = current_state.mode_started_at;
  new_state.score = current_state.score;
  new_state.current_level = current_state.current_level;

  if((current_time - current_state.mode_started_at) > timeOut) 
  {
    Serial.println("Transition to PlayingMode");
    new_state.modeFn = &PlayingMode;
    new_state.mode_started_at = current_time;
    new_state.score = 0;
    new_state.current_level++;
  }
  return new_state; 
}

State GameOverMode (State current_state, unsigned long current_time, bool start_button_reading, bool fire_button_reading){
 // Serial.println("GameOverMode");

  //Update the state
  State new_state;
  new_state.modeFn = current_state.modeFn;
  new_state.mode_started_at = current_state.mode_started_at;
  new_state.score = current_state.score;
  new_state.current_level = current_state.current_level;

  if((current_time - current_state.mode_started_at) > timeOut) 
  {
    Serial.println("Transition to IdleMode");
    new_state.modeFn = &IdleMode;
    new_state.mode_started_at = current_time;
    new_state.score = 0;
    new_state.current_level = 0;
  }
  return new_state; 
}
