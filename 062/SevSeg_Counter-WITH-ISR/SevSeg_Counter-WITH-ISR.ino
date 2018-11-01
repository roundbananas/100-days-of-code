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
#include <avr/io.h>
#include <avr/interrupt.h>

SevSeg sevseg; //Instantiate a seven segment controller object

void setup() {
  Serial.begin(9600);
  byte numDigits = 4;
  byte digitPins[] = {28, 29, 30, 31};
  byte segmentPins[] = {32, 33, 34, 35, 36, 37, 38, 39};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(100);

  //Code for interrupt using Compare Match and Clear Timer on Compare (CTC) (see datasheet Section 12.6, from p.92)
 cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count (datasheet Section 12.2.1, p.88):
    OCR1A = 10; //3499 this will cause interrupt every 0.0004375 seconds. If we go too much lower I found this stepper doesn't physically have time to move.
    // turn on CTC mode: 
    /*Note in the datasheet Table 12-5, p.110: 
     * Column two heading "WGM13:10" refers to WGM13, WGM12, WGM11 and WGM10. 
     * The four digit numbers in that column relate to those four register positions (ie WGMx).  
     * I found this confusing until I realised the meaning of the notation!
     */
    TCCR1B |= (1 << WGM12);
 // Set CS12/11/10 bits for prescaler (Datasheet Table 12-6, p.111)
       TCCR1B |= (1 << CS11); //Prescalar 8
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();

}

void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;
  
  if (millis() >= timer) {
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    timer += 100; 
    if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(deciSeconds, 1);
    Serial.println(deciSeconds);
  }
}

//Code for interrupt when counter matches compare value. This function will be called every time the timer count reaches OCR1A. 
ISR(TIMER1_COMPA_vect) ///Datasheet Table 9-1, p.48. Note for ATTiny it's "TIM1..."; for ATMega328 it's "TIMER1..." 
{
    sevseg.refreshDisplay();
}

/// END ///
