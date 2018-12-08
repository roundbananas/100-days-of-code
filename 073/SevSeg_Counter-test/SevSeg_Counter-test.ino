/* SevSeg Counter Example
 
 Copyright 2017 Dean Reading
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
 */

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object
SevSeg one_red;
SevSeg one_blue;

void setup() {
  Serial.begin(9600);
  byte numDigits = 4;
  byte digitPins[] = {25, 27, 29, 31};
  byte segmentPins[] = {37, 39, 41, 43, 45, 47, 49, 51};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(100);

  byte one_numDigits = 1;
  byte one_hardwareConfig = COMMON_ANODE;
  byte one_red_digitPins[] = {33};
  byte one_red_segmentPins[] = {26, 28, 30, 32, 34, 36, 38, 40};
  byte one_blue_digitPins[] = {35};  
  byte one_blue_segmentPins[] = {42, 44, 46, 48, 50, 52, 53};
    
  one_red.begin(one_hardwareConfig, one_numDigits, one_red_digitPins, one_red_segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  one_red.setBrightness(100);

  one_blue.begin(one_hardwareConfig, one_numDigits, one_blue_digitPins, one_blue_segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  one_blue.setBrightness(100);
}

void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;
  
  if (millis() >= timer) {
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    timer += 1000; 
    if (deciSeconds == 10) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(deciSeconds, 0);
    one_red.setNumber(deciSeconds, 0);
    one_blue.setNumber(deciSeconds, 0);
    Serial.println(deciSeconds);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
  one_red.refreshDisplay();
  one_blue.refreshDisplay();
  
}

/// END ///
