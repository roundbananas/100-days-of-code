#include "Engine.h"
#include <LiquidCrystal.h>


LiquidCrystal g_TextDisplay(12, 11, 5, 4, 3, 2);
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  g_TextDisplay.begin(16, 2); //16 columns and 2 rows in our LCD display

}

void loop() {
  Engine engine;
  engine.runEngine();

}
