#ifndef wigginState_h
#define wigginState_h



//declare function pointer to ModeFunctions. ModeFunctions manage system behaviour in each mode.
//the variables passed to ModeFunctions are used to trigger any transitions between modes.  
typedef struct State_struct (*ModeFunctions)(struct State_struct current_state, unsigned long current_time, bool button_reading, long time_out);

typedef struct State_struct {
    ModeFunctions modeFunction; //this holds the current mode
    unsigned long mode_started_at; //this holds the time the current mode started

  //  int step_Counter;
 //   int steps_FromHome; //holds stepsfrom home, calculated once upon transition from Wiggin to Return mode
  //  char stepper_Mode; //holds the stepper direction, and used to change the stepper dirn
    
} State;

//Declare system modes. It's confusing that we're declaring a mode as a State type.
//Think of it like this: the state at any time includes the current mode as one of its characteristics.
State IdleMode (State current_state, unsigned long current_time, bool button_reading, long time_out); 
State WigginMode (State current_state, unsigned long current_time, bool button_reading, long time_out);
State ReturnMode (State current_state, unsigned long current_time, bool button_reading, long time_out);

#endif
