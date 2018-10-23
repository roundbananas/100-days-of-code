//
//  main.cpp
//
//  Created by Carl Turner on 22/10/18.
//
#include <Arduino.h>
#include "Engine.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println("Eat Me");
  Engine engine;
  engine.runEngine();

}