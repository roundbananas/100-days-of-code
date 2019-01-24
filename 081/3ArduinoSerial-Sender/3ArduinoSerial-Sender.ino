/*
*     Created by Carl Turner on 23/1/19.
*     
*     Basic test setup for serial communication between three arduinos
*     This code below sends a marker character, followed by an integer.
*     
*     SENDER: MEGA Serial on pin 1 (TX0) and Serial1 on pin 18 (TX1),
*     RECEIVER 1: a minimalist Arduino Uno with a 4-digit sevSeg display 
*     RECEIVER 2: a second Arduino Uno with two single digit sevSeg displays
*     
*     Why am I doing this?
*     I've designed an arcade game, with lots of LED strips, 
*     that needs a lot of pins (hence it's driven by Mega).
*     BUT I found that rendering the LEDs was so slow that it caused
*     sevSeg displays to flicker (they need a refresh rate of at least 
*     ~60hz I think).
*     My hope is I can work around this issue by having the sevSeg displays constantly
*     refreshed separately by the two Unos (two because of number of pins required), while
*     the game and Leds run off the Mega. My understanding is that updating the values to 
*     display every now and then over serial will de-couple the sevSeg behaviour from the LED
*     behaviour.
*     This is a messy workaround. I'm sure there's a better way.
*/

//What are we going to send?
unsigned int value = 0;
unsigned int score = 1;

//periodically turn off and reset the main 4 digit display
unsigned long onDuration = 8000;  
unsigned long offDuration = 2000;
unsigned long lastToggle = 0;
bool isON = true;

void setup() {
  //I want to do it fast, so choose a fast baud rate.
  Serial.begin(250000);
  Serial1.begin(250000);
}

void loop() {
  //Serial.print sends data to the serial port as ASCII text.
  //Numbers are sent using an ASCII character for each digit.
  //This means the integer 123 is sent as the 49, 50 and 51 
  //(representing the digits 1, 2 and 3 respectively).
  //See https://www.arduino.cc/en/Reference/ASCIIchart

  unsigned long currentTime = millis();
  if (isON)
  {
    if (currentTime - lastToggle > onDuration)
    {
      Serial.print('B');      
      score = 1; //reset, not to 0 because we're multiplying it by 2 below to see change.
      isON = false;
      lastToggle = currentTime;
    }
    else
    {
      Serial.print('A');      
      Serial.println(score); 
      score *= 2;
    }
  } // end if isON
  else
  {
    if (currentTime - lastToggle > offDuration)
    {
      isON = true;
      lastToggle = currentTime;
    }
  } // end else
  
  Serial1.print('B');      
  Serial1.println(value); 
  Serial1.print('C');      
  Serial1.println(value + 2);

  value++;
  if (value > 13) value = 0;
  delay(1000);
}
