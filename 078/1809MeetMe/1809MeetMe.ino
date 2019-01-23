/*
 *  Working Version 3 Jan 2019 (except for 7seg flicker).
 *  Standalone on Mega board.
 */
#include "Engine.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  Engine engine;
  engine.runEngine();

}
