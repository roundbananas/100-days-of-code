/*
 * Carl Turner 2018
 * roundbanans.com
 * #100-days-of-code
 * R1D2
 * 
 * Critical function prototype
 * Display/print an item from an IonDB dictionary.
 * On button1 press, display next item in the dictionary.
 * On button2 press, display last item in the dictionary.
 * 
 * How:
 * 1. Create dictionary with four items. A dictionary includes pairs of keys and values.
 * 2. increment a variable on button1 press / decrement a variable on button2 press
 * 3. pass the variable as the dictionary key, to retrieve the desired dictionary value.
 * 4. if variable reaches upper or lower limit (length of dictionary) go to first or last item, respectively.
 * 
 * Hardware Setup:
 * Arduino UNO.
 * Two momentary buttons, each with:
 * - pull up resistor on + side (hence a reading of LOW, or 0, equates to button press),
 * - 1uF capacitor between -ve and +ve sides (supposedly helps debouncing).
 */

#include <IonDB.h>      // dictionary library
#include "momButton.h"  // button class, including debounce for momentary button hardware

//set pin numbers. They won't change, so use const.
 const int button1Pin = A4;
 const int button2Pin = A5;

//Instantiate one button for 'forward' and one for 'back'
  MomButton buttonBack(button1Pin);
  MomButton buttonFwd(button2Pin);

//Instantiate a dictionary
//in brackets the terms are: (dictionary ID, key type, key size, value size, dictionary size)
  Dictionary<int, ion_value_t> *dict = new SkipList <int, ion_value_t> (-1, key_type_numeric_signed, sizeof(int), sizeof("one"), 7);

//I can't figure out how to get the size (ie number of items) in dictionary, so I'll just create my own variable to track it.
//not ideal but it will be fine if we don't add/delete items to the dictionary after creating it.
  int  dictionarySize;

// declare and initialise a variable we'll use to track where we are in the dictionary.
  int i = 1;

// declare a variable to help track when I last pushed the button
  unsigned long lastTime; 

void setup() {
  Serial.begin(9600);

  //set pin modes for each button
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  //Insert four dictionary item pairs, each with a key and a value
  dict->insert(1, "Page 1");
  dict->insert(2, "Page 2");
  dict->insert(3, "Page 3");
  dict->insert(4, "Page 4, last page");

  dictionarySize = 4;

 //initialise lastTime variable;
  lastTime = millis();
}

void loop() {
  //grab the current time
  unsigned long currentTime = millis();

  //read the button at specified intervals, otherwise what we think 
  //is one press will register as multiple presses 
  //(our hands a slow compared to the program loop)
  int readInterval = 500; //500 seems to 'feel' ok when pressing the buttons.

  //increment or decrement the tracking variable, IF we have a button press AND we've exceeded our readInterval
  if(buttonBack.UpdateButton() == 0 && ((currentTime - lastTime) >= readInterval))
    {i--;
     if(i < 1){
        i = dictionarySize;   
      }
     lastTime = currentTime;
    }
  if(buttonFwd.UpdateButton() == 0 && ((currentTime - lastTime) >= readInterval))
    {
      i++; 
      if(i > dictionarySize){
        i = 1;   
      }
     lastTime = currentTime;
    } 

  //retrieve value of type ion_value_t by providing a key
  ion_value_t my_value = dict->get(i);

  //cast the returned value to type string using Arduino String constructor
  String string_value = String((char *) my_value);

  Serial.print("Current page is: ");
  Serial.println(string_value);
  Serial.println("  "); //make serial output easier to read
}

