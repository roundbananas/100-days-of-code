#include <AltSoftSerial.h> //check: specific rx tx pins required. https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
#include <DFMiniMp3.h>
#include "Mp3Notify.h"

uint16_t Mp3Count;
int Mp3Track; //will move this to be a state variable once I have tested it
bool Mp3Playing = false;

AltSoftSerial altSerial; //pins for AltSoftSerial must be TX = 9, RX = 8 on Uno and 46, 48 on Mega
DFMiniMp3<AltSoftSerial, Mp3Notify> mp3(altSerial);

void setup() {
  Serial.begin(115200);
  mp3.begin();
  mp3.reset();
  delay (2000);
    
  mp3.setVolume(4);
  Serial.print("volume ");
  Serial.println(mp3.getVolume());

  Mp3Count = mp3.getTotalTrackCount();
  Serial.print("files ");
  Serial.println(Mp3Count);

    Serial.println("Playing Track 3");
  mp3.playMp3FolderTrack(3);
  delay(2500);

 Serial.println("End SETUP");
}

void waitMilliseconds(uint16_t msWait)
{
  uint32_t start = millis();
  
  while ((millis() - start) < msWait)
  {
    Serial.println("looping");
    // calling mp3.loop() periodically allows for notifications 
    // to be handled without interrupts
    mp3.loop(); 
    delay(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

     Serial.print("Playing Tracks in folder 1: ");
     Serial.print(" jewel ");
  mp3.playFolderTrack16(1, 2); //jewel
 delay(2000);
  Serial.print(" demon ");
 mp3.playFolderTrack16(1, 4); //demon
  delay(2000);
 Serial.print(" lightning ");
 mp3.playFolderTrack16(1, 5); //lightning

  delay(2000);
   Serial.print(" jewel ");
mp3.playFolderTrack16(1, 2); //jewel

  delay(2000);
   Serial.println(" mario ");
mp3.playMp3FolderTrack(3); //
delay(2000);
  Serial.println("Playing Ad 5");

  mp3.playAdvertisement(5); //lightning

    delay(2000);
   Serial.println(" mario ");
mp3.playMp3FolderTrack(1); //

  delay(2000);
   Serial.println(" mario ");
mp3.playMp3FolderTrack(3); //

  delay(2000);
   Serial.println(" mario ");
mp3.playMp3FolderTrack(3); //
waitMilliseconds(5000);
}
