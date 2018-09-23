
#include "Arduino.h"


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0, INPUT);
pinMode(4, INPUT);
pinMode(A1, INPUT);
pinMode(5, INPUT);
}

void loop() {
  int m_PotValue = analogRead(A0);
  m_PotValue = map(m_PotValue, 0, 1023, 0, 255);
  m_PotValue = constrain(m_PotValue, 0, 255);
  
  int button1 = digitalRead(4);
Serial.print ("Player1:    ");
Serial.print (m_PotValue);
Serial.print ("   /   ");
Serial.println (button1);

  int reading2 = analogRead(A1);
  int button2 = digitalRead(5);
Serial.print ("Player2:    ");
Serial.print (reading2);
Serial.print ("   /   ");
Serial.println (button2);
Serial.println ("      ");

delay(500);
}
