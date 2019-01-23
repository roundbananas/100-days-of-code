/*
 * YYEAAAAHH!!!
 * Created by Carl Turner 5 Jan 2019
 * roundbananas.com
 * 
 * Test to get Arduino Uno to send data to Due module
 * 
 * HOW?
 * I'll create a flag on the Arduino.
 * I'll trip the flag every 1 second.
 * When flag is tripped, I'll arduino LED will turn on.
 * 
 * I'll send flag status to Due module.
 * Due module will turn on an LED when flag is tripped. 
 * This might give me an idea of any lag too, perhaps.
 * 
 * //HARDWARE
 * 1. Connect grounds of level converter, Due and Uno.
 * 2. Uno TX -> converter RXI (I = 'IN') : converter RXO (O = 'OUT') -> Due RX1
 * 3. external led on Pin 2 of Due
 * 
 *  * NOTE the logic level converter, it's very confusing to hook up:
 * 
 *    BOARD 1       CONVERTER         BOARD 2
 *    TX       -->  RXI...RXO   -->   RX 
 *    RX       <--  TXO...TXI   <--   TX 
 * 
 * 
 * 5v - 3.3v logic level converter (https://core-electronics.com.au/tutorials/how-to-use-logic-level-shifters-converters.html)
 * powered using a micro usb cable with a voltage divider to give 5v and 3.3v sources (http://www.ohmslawcalculator.com/voltage-divider-calculator)
 * https://www.freetronics.com.au/pages/level-logic-level-converter-module-quickstart-guide#.XDBCA88zYW8
  */

//Select which board you're uploading to.
bool Arduino = false; //false means we're uploading to ESP8266 module

int Arduino_LEDpin = 13; //UNO built in led
int DUE_LEDpin = 2; //on wemos style board built in LED is on pin D2

bool flag = 0;
char sendChar = 'N'; //this is what we send. Y = on, N = off
char receivedChar = 'N'; //what we receive .

unsigned long lastTime = 0;
unsigned long period = 1000; //1 ms

void setup() {
  Serial.begin(250000);
  if (!Arduino) Serial1.begin(250000);

  pinMode(Arduino_LEDpin, OUTPUT);
  pinMode(DUE_LEDpin, OUTPUT);
  Serial.print("Starting Loop");
}

void loop() {
  unsigned long currentTime = millis();
  
  if (Arduino)
  {
    if (currentTime - lastTime >= period)
    {
      flag = !flag;
      if (flag) sendChar = 'Y';
      else sendChar = 'N';
      
      lastTime = currentTime;
    }
    Serial.println(sendChar);  //send data to ESP module
    digitalWrite(Arduino_LEDpin, flag); //update the arduino LED
  }
  else //Due module
  {
    if (Serial1.available() > 0)
    {
        receivedChar = Serial1.read();
    }
   // else { Serial.println("No Serial");}
    
    if (receivedChar == 'Y') 
    {
    //  Serial.println(receivedChar);
      digitalWrite(DUE_LEDpin, HIGH);
      receivedChar = 'N';
    }
    else digitalWrite(DUE_LEDpin, LOW);
  }
  
}
