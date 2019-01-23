/*
 * FOR SOME REASON THIS PROGRAM EXECUTES SETUP, BUT NEVER STARTS THE MAIN LOOP?? 
 *  
 *     Created by Carl Turner on 3/1/19.
 *   This test will run three sevSegDisplays, updating the values displayed with data received over serial.
 */
 #include "Engine.h"

void setup() {
  Serial.begin(250000);
     Serial.println("Setup");
    Serial1.begin(250000);
   
}

void loop() {
    Serial.println("Loop");

  Engine engine;
  engine.runEngine();

}
