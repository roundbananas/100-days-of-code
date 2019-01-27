/*
 *  Working Version 26 Jan 2019 (except slight issue with player 3 boost led. And 7 segs commented out. No serial comms included yet.).
 *  Standalone on Mega board.
 */
#include "Engine.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  
  Engine engine;
  engine.runEngine();

}
