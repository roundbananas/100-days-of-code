// code for Mega to work with DemoSimpleSoftSerial


char msg[16] = "< ABCDEFG>HJ"; // 12 characters

byte sendByte = 'a';

//===========

void setup() {
  Serial.begin(9600);
  Serial.println("Starting DemoPartner,ino"); 

  Serial1.begin(9600);
}

//===========

void loop() {

  getText();
//  delay(25);
  sendText();
  delay(1000);

}

//===========

void getText() {

  if (Serial1.available() > 0) {
    while (Serial1.available() > 0) {
       byte bb = Serial1.read();
       Serial.print((char) bb);
    }
    Serial.println();
  }
}

//===========

void sendText() {

   msg[1] = sendByte;
   Serial1.write(msg, 10);
   sendByte += 1;
   if (sendByte > 'z') {
     sendByte = 'a';
   }
}


