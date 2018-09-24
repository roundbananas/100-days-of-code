// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include "Arduino.h"
#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 25 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    6
#define CLOCKPIN   7
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif
Serial.begin(9600);
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = -2; // Index of first 'on' and 'off' pixels
uint32_t color = 0x008000;      // 'On' color (starts red)

int      head2  = 25, tail2 = 27; // Index of first 'on' and 'off' pixels
uint32_t color2 = 0xFF0000;      // 'On' color (starts red)

void loop() {

  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.setPixelColor(head2, color2); // 'On' pixel at head
  strip.setPixelColor(tail2, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(100);                        // Pause 20 milliseconds (~50 FPS) 

if (head > head2)
  {
    color = 0xffa500;
    color2 = 0xffa500;
    explode();
  }
//  else{
  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index

  if(--head2 <= 0)          // Increment head index.  Off end of strip?
    head2 = 25;                       //  Yes, reset head index to start
    
  if(--tail2 <= 0) tail2 = 25; // Increment, reset tail index
//  }
  Serial.println(head);
}

void explode()
{
  for (int i=head; i < (head + 3); i++)
  {
    strip.setPixelColor(i, 0xffa500); 
    strip.show();
    //delay(1);
     
  }
  for (int i=head2; i > (head2 - 3); i--)
  {
    strip.setPixelColor(i, 0xffa500); 
    strip.show();
   // delay(1);
     
  }
  for (int i=0; i < NUMPIXELS; i++)
  {
  strip.setPixelColor(i, 0x000000); 
    strip.show();
  }
  

}
