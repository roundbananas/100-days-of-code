/*
 *     Created by Carl Turner on 3/1/19.
 *   This test will run three sevSegDisplays, counting on each one.
 */
 #include "Engine.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  Engine engine;
  engine.runEngine();

}
