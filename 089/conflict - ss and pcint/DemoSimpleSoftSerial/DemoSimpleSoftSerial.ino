// program to Demo the use of SimpleSoftSerial
//   assumes that the file sss.ino is in the same directory as this file

//   A Mega is set to receive and send as a partner for this demo (TestPartner.ino)
//     should also work with Leonardo

#include <Servo.h>

Servo myServo;

byte mesg[16];
byte bytesToSend = 6;

unsigned long curMillis = 0;
unsigned long prevSendMillis = 0;
unsigned long sendIntervalMillis = 4000;
unsigned long prevServoMillis = 0;
unsigned long servoIntervalMillis = 200;

byte sendByte = 'A';
byte col = 0;

byte servoPos = 90;
char servoStep = 20;

//==================

void setup() {

  Serial.begin(9600);
  Serial.println("Starting DemoSimpleSoftSerial.ino");
  
  sssBegin();
  
  myServo.attach(8);
  myServo.write(servoPos);

}

//==================

void loop() {
  curMillis = millis();
  sendMessage();

  receiveMessage();

  
  updateServo();
}

//==================

void sendMessage() {

  if (curMillis - prevSendMillis >= sendIntervalMillis) {
      prevSendMillis += sendIntervalMillis;
      
      for (byte n = 0; n < bytesToSend; n++) {
        mesg[n] = sendByte + n;
      }
      sssWrite(mesg, bytesToSend);
      Serial.println("Message Sent"); 

      sendByte += bytesToSend;
      if (sendByte > 'Z') {
        sendByte = 'A';
      }
  }
}

//==================

void receiveMessage() {
     
   if (sssAvailable() > 0) {
       
      byte bb = sssRead();
      Serial.print((char) bb);
      Serial.print(" ");
      
      if (bb == '>') {
        Serial.println();
      }
    }
}

//==================

void updateServo() {
  if (curMillis - prevServoMillis >= servoIntervalMillis) {
    prevServoMillis += servoIntervalMillis;
    servoPos += servoStep;
    if (servoPos < 10 || servoPos > 170) {
       servoStep = -servoStep;
       servoPos += servoStep;
    }
    myServo.write(servoPos);
  }
}
