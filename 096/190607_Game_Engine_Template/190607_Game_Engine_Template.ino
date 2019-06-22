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



void triggerInterrupt1(); 
void triggerInterrupt2();
void triggerInterrupt3();

Engine *myEngine = nullptr;


void setup() {
  Serial.begin(9600);
  Serial.println("setup");
}

void loop() {
  Serial.println("loop");
  myEngine = createEngine(&triggerInterrupt1, &triggerInterrupt2, &triggerInterrupt3);
  myEngine->runEngine();

}

Engine* createEngine(void* interruptDispatch1, void* interruptDispatch2, void* interruptDispatch3)
{
	Engine *engine = new Engine(interruptDispatch1, interruptDispatch2, interruptDispatch3);
	return engine;
}

void triggerInterrupt1()
{
	Serial.print("Interrup 1");
	myEngine->updateSensor1();
}
void triggerInterrupt2()
{
	Serial.print("Interrup 2");
	myEngine->updateSensor2();
}
void triggerInterrupt3()
{
	Serial.print("Interrup 3");
	myEngine->updateSensor3();
}