unsigned int value = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(250000);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print('A');
Serial.println(value);
//Serial.println("");
value++;
delay(1000);
}
