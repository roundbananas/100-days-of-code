/*
 * YYEAAAAHH!!!
 * 
 * Created by Carl Turner 18 Nov 2018
 * roundbananas.com
 * 
 * Test to get Arduino to send data to ESP8266 module
 * 
 * HOW?
 * I'll create a flag on the Arduino.
 * I'll trip the flag every 1 second.
 * When flag is tripped, I'll arduino LED will turn on.
 * 
 * I'll send flag status to ESP module.
 * ESP module will turn on its LED when flag is tripped. 
 * This might give me an idea of any lag too, perhaps.
 * 
 * //HARDWARE
 * Wemos D1 Mini 'style' ESP8266 board (https://escapequotes.net/esp8266-wemos-d1-mini-pins-and-diagram/)
 * 5v - 3.3v logic level converter (https://core-electronics.com.au/tutorials/how-to-use-logic-level-shifters-converters.html)
 * powered using a micro usb cable with a voltage divider to give 5v and 3.3v sources (http://www.ohmslawcalculator.com/voltage-divider-calculator)
 */

//Select which board you're uploading to.
bool Arduino = false; //false means we're uploading to ESP8266 module

int Arduino_LEDpin = 13; //UNO built in led
int ESP_LEDpin = 2; //on wemos style board built in LED is on pin D2

bool flag = 0;
char sendChar = 'N'; //this is what we send. Y = on, N = off
char receivedChar = 'N'; //what we receive .

unsigned long lastTime = 0;
unsigned long period = 1000; //1 ms

void setup() {
  Serial.begin(9600);
  pinMode(Arduino_LEDpin, OUTPUT);
  pinMode(ESP_LEDpin, OUTPUT);
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
  else //ESP module
  {
    if (Serial.available() > 0)
    {
        receivedChar = Serial.read();
    }
   // else { Serial.println("No Serial");}
    
    if (receivedChar == 'Y') 
    {
      Serial.println(receivedChar);
      digitalWrite(ESP_LEDpin, LOW);
     // delay(500); //so we can see the led light up
      receivedChar = 'N';
    }
    digitalWrite(ESP_LEDpin, HIGH);
  }
}
