

#ifndef Header_h
#define Header_h
#include "Arduino.h"
#include <LiquidCrystal.h>
extern LiquidCrystal lcd;
class Header
{
  public:
  Header(){}
  
  void blah()
  {
 
      lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  }
  
};

#endif
