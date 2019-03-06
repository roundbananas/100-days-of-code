// DFPlayer Mini MP3 by Makuna
// Moved class into header file, by Carl Turner 6 March 2019

#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include "Mp3Notify.h"

SoftwareSerial secondarySerial(6, 7); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

uint16_t count;

void waitMilliseconds(uint16_t msWait)
{
  uint32_t start = millis();
  
  while ((millis() - start) < msWait)
  {
    // calling mp3.loop() periodically allows for notifications 
    // to be handled without interrupts
    mp3.loop(); 
    delay(1);
  }
}

void setup() {
  Serial.begin(115200);

  Serial.println("initializing...");
  
  mp3.begin();

  uint16_t volume = mp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
  mp3.setVolume(6);
  
  count = mp3.getTotalTrackCount();
  Serial.print("files ");
  Serial.println(count);
  
  Serial.println("starting...");
}

void loop() {
  for (int i = 1; i <= count; i++)
  {
    Serial.print("track "); Serial.println(i);
    mp3.playMp3FolderTrack(i);  // sd:/mp3/0001.mp3
  
    waitMilliseconds(5000);
  }

}
