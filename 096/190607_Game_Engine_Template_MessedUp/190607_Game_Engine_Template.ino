/*
*	Game Engine Template.ino
*
*	Created by Carl Turner 7 June 2019
*
*	STRUCTURE OF THE ENGINE
*
*	File						Purpose
*	Game Engine Template.ino	
*	Engine.h					declares game variables and functions
*		Engine.cpp				defines game functions that constitute the main game loop, including: 
									Engine() constructor (which is effectively a game setup routine) 
									Update() which takes 'read input' functions as parameters (could alternatively split input out into a separate input() function if needed)
									Render() which handles displaying game state to the user
*	Objects.h					declares and defines functions that create game objects (i.e. instantiate enemies, players as well as MP3 players, buttons etc)
*	State.h						declares state struct (and contained variables that represent the state)
*	Modes.cpp					defines mode functions that describe program behaviour in each game mode
*	
*/

#include "Engine.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  Engine engine;
  engine.runEngine();

}