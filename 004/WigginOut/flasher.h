/*
 * Flasher.h - for individually flashing addressable APA102 LEDs
 * Using the constructor - Flasher(int number, int colH, int colS, int colV, long on, long off) - we can create 
 * individual objects for each of the separate leds on the strip. Then we can control the colour and blink rate
 * of each one separately using two lines of code in our ino file AND do a bunch of other stuff simultaneously 
 * (because the blinking is handled by the class' Update() function, it doesn't block the main program).
 */
#ifndef flasher_h
#define flasher_h

#include "Arduino.h"
#include "FastLED.h"

//named constants for LED setup. 
//Using named constants is easier to read and lets us change the values in one spot.
#define NUM_LEDS 3
#define DATA_PIN 5
#define CLOCK_PIN 6

//allocate some memory, in the form of an array, to store and manipulate led data
extern struct CRGB leds[];

//this class will enable us to control individual leds on the APA02 strip.
//If we had multiple strips we could create multiple classes, eg Flasher1, Flasher2.. AND we'd need to create an
// additional set of NUM_LEDS, DATA_PIN and CLOCK_PIN values for each strip and set each strip up separately
// using an extra line of code - FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS) - in setup();
class Flasher
{
  //Class member variables
  int ledNumber;  //this refers to the position of the led on the strip. The first one is position '0'.
  int colourH;    //used to set HSV colour of led
  int colourS;    //used to set HSV colour of led
  int colourV;    //used to set HSV colour of led
  long OnDuration;
  long OffDuration;

  //these maintain the current state
  bool ledOn;   //used to set the LED state
  unsigned long previousMillis; //will store last time LED was updated

  //Constructor - creates a flasher
  // and initialises the member variables and state
  public:
  Flasher(int number, int colH, int colS, int colV, long on, long off)
  {
      ledNumber = number;

      colourH = colH;
      colourS = colS;
      colourV = colV;

      OnDuration = on;
      OffDuration = off;

      ledOn = false;
      previousMillis = 0;
  }

  void UpdateLed()
  {
    //check if it's time to update the state of the LED
    unsigned long currentMillis = millis();

    if((ledOn == true) && (currentMillis - previousMillis >= OnDuration))
    {
      ledOn = false; //change the state to off
      previousMillis = currentMillis; // remember the time
      leds[ledNumber] = CRGB::Black;     // change colour of actual led to black (off)
      FastLED.show(); //update the actual LED
    }
    else if ((ledOn == false) && (currentMillis - previousMillis >= OffDuration))
    {
      ledOn = true; //change state to on
      previousMillis = currentMillis;
     leds[ledNumber] = CRGB::Red;
    //  leds[ledNumber].setHSV( colourH, colourS, colourV); 
      FastLED.show(); //update the actual LED
    }
  }
  
    void GoBlack()
  {
    leds[ledNumber] = CRGB::Black;   
    FastLED.show(); //update the actual LED
  }
};

#endif
