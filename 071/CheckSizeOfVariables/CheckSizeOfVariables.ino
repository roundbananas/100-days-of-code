void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
delay (1000);

Serial.print("bool:\t\t"); Serial.print(sizeof(bool)); Serial.println(" bytes");
Serial.print("char:\t\t"); Serial.print(sizeof(char)); Serial.println(" bytes");
Serial.print("int:\t\t"); Serial.print(sizeof(int)); Serial.println(" bytes");
Serial.print("long:\t\t"); Serial.print(sizeof(long)); Serial.println(" bytes");
Serial.print("ulong:\t\t"); Serial.print(sizeof(unsigned long)); Serial.println(" bytes");
Serial.print("float:\t\t"); Serial.print(sizeof(float)); Serial.println(" bytes");
Serial.print("double:\t\t"); Serial.print(sizeof(double)); Serial.println(" bytes");
Serial.print("string:\t\t"); Serial.print(sizeof(String)); Serial.println(" bytes");

}

void loop() {
  // put your main code here, to run repeatedly:

}
