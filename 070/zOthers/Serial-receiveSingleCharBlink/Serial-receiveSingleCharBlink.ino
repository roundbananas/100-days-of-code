// From http://forum.arduino.cc/index.php?topic=396450.0
//this works on ESP8266
// Example 1 - Receiving single characters

char receivedChar;
boolean newData = false;

int ESP_LEDpin = 2; //on wemos style board built in LED is on pin D2

void setup() {
    Serial.begin(9600);
    pinMode(ESP_LEDpin, OUTPUT);
    Serial.println("<Arduino is ready>");
}

void loop() {
    recvOneChar();
    showNewData();
    blinkLED();
}

void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChar);
        //newData = false;
    }
}

void blinkLED() {
  if (newData == true) 
  {
    digitalWrite(ESP_LEDpin, LOW);
    delay(1000); //so we can see the led light up
    newData = false;
  }
  digitalWrite(ESP_LEDpin, HIGH);
}
