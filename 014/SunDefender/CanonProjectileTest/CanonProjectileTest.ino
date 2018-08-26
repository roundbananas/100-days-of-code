//
//  CanonProjectileTest.ino
//  SunDefender
//
//  Created by Carl Turner on 26/8/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#include <Adafruit_DotStar.h>
#include <SPI.h>         

#define NUMPIXELS 25 // Number of LEDs in strip
#define DATAPIN    A0
#define CLOCKPIN   A1
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup() {
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

int      head  = 0, tail = -5; // Index of first 'on' and 'off' pixels

void loop() {

 strip.setPixelColor(head, 0, 0, 255);
 strip.setPixelColor(tail+4, 0, 0, 35);
 strip.setPixelColor(tail+3, 0, 0, 25);
 strip.setPixelColor(tail+2, 0, 0, 15);
 strip.setPixelColor(tail + 1, 0, 0, 5);
 strip.setPixelColor(tail, 0);     // 'Off' pixel at tail

 strip.show();                     // Refresh strip
 delay(50);                        // Pause 

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index
}
