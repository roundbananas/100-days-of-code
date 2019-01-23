void setup() {
  // put your setup code here, to run once:
Serial.begin(250000);
}

void loop() {
  // put your main code here, to run repeatedly:
 if (Serial.available ()>0)
  {
      Serial.println(Serial.read ());
  }
 // if(!Serial1.available()) Serial.println("No Serial");
}
