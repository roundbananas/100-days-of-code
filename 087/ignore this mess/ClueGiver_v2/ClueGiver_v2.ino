/*
 * ClueGiver v2
 * By Carl Turner 4 March 2019
 * roundbananas.com
 * 
 * MODE: SETUP
 * The program randomly assigns one of three locations as having the 'jewels'.
 * LEDs at each of the three locations animate, then fade.
 * The Wizard says something (MP3) to give context/background story and a CTA to players.
 * 
 * When setup is complete, trigger Jewels_Not_Found mode.
 * 
 * MODE: JEWELS_NOT_FOUND
 * Background music plays - travelling, wonderous, but urgent music.
 * 
 * LEDs around the wizard's tower randomly flash (like lighting/spells being cast).
 * 
 * When you press a button, the program will display a random clue on an OLED display.
 * The clue will reveal ONE location that does not contain the jewels. (a symbol and word).
 * 
 * There are three hall sensors, one for each of location.
 * When a hall sensor corresponding to false jewel location is triggered:
 * - LEDs around non-jewels rise then fade dissapointingly
 * - MP3 fail sound FX
 * - MP3 wizard says "Fools, you'll never find my jewels!"
 * 
 * When the hall sensor corresponding the jewel location is triggered, the jewels have been 'found':
 * - LEDs around the jewels flash and glitter like jewels
 * - MP3 success sound FX
 * - wizard says something (MP3) that indicates he's aware the jewels are stolen, he's furious.
 * - wizard say something that reminds players about catastrophes (new rule), and subtle CTA reminder to get back to village safely.
 * 
 * MODE: JEWELS_FOUND 
 * Background music plays - more energetic, the heat is on.
 *
 * LEDs around the wizard's tower randomly flash at a faster pace.
 * MP3 - the odd cackle of fury from the wizard.
 *
 * STATE VARIABLES ()
 * Variable                 triggers mode change
 * byte jewelLocation       for checking any hall readings
 * bool hallSensor[i]       if i != jewelLocation, triggers fail song. If i = jewelLocation, trigger success song and Jewels_Found mode
 * bool clueButton          for OLED display timer
 * bool setupComplete       setup --> Jewels_Not_Found        
 * ul   lastClueRequestAt   for OLED display timer
 * 
 * 
 * Use interrupt to read the hall sensors, 
 * without delaying the rest of the program.
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * 
 * Note on pinmodes: https://www.arduino.cc/en/Tutorial/DigitalPins
 */

#include <Arduino.h>
#include "HallSensor.h"
#include "ButtonMom.h"

#include "Mp3Notify.h"

#include <U8g2lib.h>      //for OLED display
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "Modes.h"        //mode functions and state struct

/*
 * PINS
 */
byte sensorPins[3] = {A0, A1, A2};

byte clueButtonPin = A3;

byte LEDS_Wizard_clk = 2;
byte LEDS_Wizard_dat = 3;
byte LEDS_Locations_clk = 4;
byte LEDS_Locations_dat = 5;

byte MP3_RX = 6; //this is RX on Arduino, going to TX on MP3Player
byte MP3_TX = 7; //this is TX on Arduino, going to RX on MP3Player

byte OLED_clk = 13;   //to D0/SCK/SCL on display
byte OLED_data = 11;  //to D1/MOSI/SDA on display
byte OLED_cs = 10;    //to CS on display
byte OLED_dc = 9;     //to DC on display
byte OLED_reset = 8;  //to RES on display

/*DELETE THIS IT'S DIFFERENT
 * Pin                             Uno Pin
 * Vcc  Power Supply  5V
   D0  Clock into display  SCK SCL 13
   D1  Data into display MOSI  SDA 11
   RES Reset                       10
   DC  Data/Command                 9
   CS  Chip Select CS               8
 */

/*
 * VARIABLES
 */

State_Struct state; //holds current state

/* 
 *  NEED TO SORT THESE OUT. 
 *  
byte ClueOption1 = 0; 
byte ClueOption2 = 0;

char *ClueOptions[] = {"No Jewels!?", "NOT volcano", "NOT Mine", "NOT Swamp"};
char *Clues[2] = {"null", "null"};
 */

/*
 * INPUTS
 */

HallSensor sensor1;
HallSensor sensor2;
HallSensor sensor3;
HallSensor sensors[3] = {sensor1, sensor2, sensor3};

ButtonMom clueButton;

/*
 * OUTPUTS
 */

//OLED
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ OLED_clk, /* data=*/ OLED_data, /* cs=*/ OLED_cs, /* dc=*/ OLED_dc, /* reset=*/ OLED_reset);

//MP3 Player
SoftwareSerial secondarySerial(6, 7); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);


/*
 * FUNCTIONS
 */
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

void playTrack(byte trackNo)
{
   mp3.playMp3FolderTrack(trackNo);  // sd:/mp3/0001.mp3
   waitMilliseconds(5000);
}

void setup() {
  Serial.begin(115200);
  
  //setup to the interrupt to toggle Hall_State
  
  //Start Display
  Serial.println("Starting display...");
  u8g2.begin();  
  u8g2.setFont(u8g2_font_t0_16_mr); // choose a suitable font

  //Start MP3 Player
  Serial.println("Starting MP3 player...");
  mp3.begin();
  mp3.setVolume(4);
  

  clueButton.spawn(clueButtonPin);
  Serial.println("End Setup");
}

void loop() {

  
}
