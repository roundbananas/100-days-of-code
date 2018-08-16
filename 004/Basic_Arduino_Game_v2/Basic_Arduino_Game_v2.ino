/*
 * Carl Turner 2018
 * roundbanans.com
 * #100-days-of-code
 * R1D3
 * 
 * Simple Arduino Game
 * An experiment in learning to work with multiple files.
 * 
 */
#include "Button.h"
#include "State.h"
#include "Enemy.h"

int startButtonPin = A5;
Button startButton(A5);

int fireButtonPin = A4;
Button fireButton(A4);

State state;

int timeOut = 4000;
int beatLevelScore = 6;


void setup() {
  Serial.begin(9600);
  pinMode(startButtonPin, INPUT);
  pinMode(fireButtonPin, INPUT);
 
  state.modeFn = &IdleMode;
  state.mode_started_at = millis();
  state.score = 0;
  state.current_level = 1;

  Serial.print(" ");
  Serial.print("Welcome to the \n Simple Arduino Game!\n ");
  delay(100);
  Serial.print("\n You need 3 points to pass each level");
  delay(100);
  Serial.print("\n Press 'fire' to get points\n");
  delay(100);
  Serial.println("\n Press 'start' to start, in.. 3 seconds");
  delay(1000);
  Serial.println(" 2 seconds");
  delay(1000);
  Serial.println(" 1 second\n\n");
  delay(1000);
}

void loop() {
  unsigned long t = millis();

  state = state.modeFn(state, t, startButton.UpdateButton(), fireButton.UpdateButton(), startButton.UpdateButton()); //we'll just use startbutton as another fire button for now

  //add score etc here eventually
  Serial.print("Score: ");
  Serial.println(state.score);
  Serial.print("Level: ");
  Serial.println(state.current_level);
  Serial.println(" ");
  Render(state);

}

void Render(State current_state){
    
    if(state.modeFn == IdleMode){
      Serial.println("Press 'Start' button");
      }
    if(state.modeFn == PlayingMode){
      Serial.println("FIRE YOUR WEAPON!!");
      }
      if(state.modeFn == BeatLevelMode){
      Serial.println("YOU BEAT THE LEVEL!");
      }
      if(state.modeFn == GameOverMode){
      Serial.println("GAME OVER (You ran out of time)");
      }
}


