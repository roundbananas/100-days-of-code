/*
 * Carl Turner 2018
 * roundbanans.com
 * #100-days-of-code
 * R1D1
 * 
 * Critical function prototype
 * Display/print an item from an IonDB dictionary.
 * On button hold, display next item in the dictionary.
 * On button release, revert to previous item.
 * 
 * How:
 * 1. Create dictionary with two items. A dictionary includes pairs of keys and values.
 * 2. increment/decrement a variable on button press
 * 3. pass the variable as the dictionary key, to retrieve the desired dictionary value.
 */

#include <IonDB.h>
#include "momButton.h"

  int buttonPin = A5;
  MomButton button(buttonPin);

//Instantiate a dictionary
  Dictionary<int, ion_value_t> *dict = new SkipList <int, ion_value_t> (-1, key_type_numeric_signed, sizeof(int), sizeof("one"), 7);

void setup() {
  Serial.begin(9600);

  //button used to toggle between pages
  pinMode(buttonPin, INPUT);
  
  //Insert two item pairs, each with a key and a value
  dict->insert(1, "Page 1");
  dict->insert(2, "Page 2");
}

void loop() {
  int i = 1;

  if(button.UpdateButton() == 0)
    { 
      switch (i){
        case 1:
         i++;
        break;
        
        case 2:
         i--;
        break;
      }  
    }
    
  //retrieve value of type ion_value_t by providing a key
  ion_value_t my_value = dict->get(i);

  //cast the returned value to type string using Arduino String constructor
  String string_value = String((char *) my_value);

  Serial.print("Current page is: ");
  Serial.println(string_value);
  Serial.println("  ");
  delay (100);
}

