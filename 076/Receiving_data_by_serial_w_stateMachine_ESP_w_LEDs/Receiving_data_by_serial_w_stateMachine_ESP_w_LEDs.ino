/*
 * Receiving Data by Serial, with State Machine
 * 
 * Created by Carl Turner 11 Dec 2018
 * roundbananas.com
 * 
 * This sketch adapts Nick Gammon's 'Example state machine reading serial input' (17 December 2011).
 * I can't believe I've made this work for a bit more of a complicated situation. Thanks Nick!
 */
 
   /*
  * We'll send data from the serial monitor, and put it into an Array when 
  * received on the arduino, byte DataReceived[3][9]
  * 
  * (The reference to bullets and explosions relates to a game I'm making.)
  * 
  * [3] holds strip number - possible value of 0, 1, 2
  * [9] holds on/off and position data for BulletA, BulletB and Explosion
  * 
  * Array index   Relates to      Possible values
  * [i][0]        BulletA on/off  0, 1
  * [i][1]        BulletB on/off  0, 1
  * [i][2]        Expl'n on/off   0, 1
  * [i][3]        BulletAHead     0 - 90 (strip length)
  * [i][4]        BulletATail     0 - 90 (strip length)
  * [i][5]        BulletBHead     0 - 90 (strip length)
  * [i][6]        BulletBTail     0 - 90 (strip length)
  * [i][7]        Expl'nHead      0 - 90 (strip length)
  * [i][8]        Expl'nTail      0 - 90 (strip length)
  * 
  */

  /*
 * State Codes (for inputting through serial monitor)
 * X, Y, Z - Strip 1, 2, 3
 * 
 * Sub state codes
 * K - Bullet A is on 
 * L - Bullet B is on
 * M - Explosion is on
 * A, a - Bullet A head, tail
 * B, b - Bullet B head, tail
 * E, e - Explosion head, tail
 *  
 *  Note, to assign a new value to the array you need to type the state, subState 
 *  and value into the serial monitor each time. Eg: to assign a position 
 *  of 23 to the BulletAHead on strip1, you'd write in serial monitor: XA23
 *  
  */

  // the possible states of the state-machine
typedef enum {  NONE, GOT_X, GOT_Y, GOT_Z } states;
typedef enum { 
  _NONE, 
  K_BULLETA_ON, L_BULLETB_ON, M_EXPLOSION_ON, 
  A_BULLETA_HEAD, A_BULLETA_TAIL, 
  B_BULLETB_HEAD, B_BULLETB_TAIL, 
  E_EXPLOSION_HEAD, E_EXPLOSION_TAIL } subStates;

// current state-machine state
states state = NONE;
subStates subState = _NONE;

// current partial number
unsigned int currentValue;

//full array
byte DataReceived[3][9]; //where we'll put the values we receive

//let's print the array after a certain time
unsigned long lastPrint = 0;
int timeTillNextPrint = 0;

//LEDs
#include <Adafruit_DotStar.h>
#include <SPI.h>  

int _DataPin1 = 0;
int _ClockPin1 = 2;
int _DataPin2 = 13;
int _ClockPin2 = 15;
uint16_t _NUMPixels = 25; //MUST BE SAME DECLARED IN MEGA CODE

Adafruit_DotStar strip1 = Adafruit_DotStar(_NUMPixels, _DataPin1, _ClockPin1, DOTSTAR_BRG);
Adafruit_DotStar strip2 = Adafruit_DotStar(_NUMPixels, _DataPin2, _ClockPin2, DOTSTAR_BRG);
Adafruit_DotStar strips[2] = {strip1, strip2}; //array to loop through

uint32_t _color1 = 0xFF0000; 
uint32_t _color2 = 0x0064EF;

void setup ()
{
  Serial.begin (115200);
  state = NONE;
  subState = _NONE;

  pinMode(_DataPin1, OUTPUT);
  pinMode(_ClockPin1, OUTPUT);
  pinMode(_DataPin2, OUTPUT);
  pinMode(_ClockPin2, OUTPUT);

  strip1.begin(); // Initialize pins for output
  strip2.begin();
  strip1.show();  // Turn all LEDs off ASAP
  strip2.show();
}  // end of setup

void processSTRIP (int strip, const unsigned int value)
{
  // Assign data to array elements for relevant strip 
  switch(subState)
  {
    case K_BULLETA_ON:
      DataReceived[strip][0] = value;
      break;
     case L_BULLETB_ON:
      DataReceived[strip][1] = value;
      break;
    case M_EXPLOSION_ON:
      DataReceived[strip][2] = value;
      break;
    case A_BULLETA_HEAD:
      DataReceived[strip][3] = value;
      break;
    case A_BULLETA_TAIL:
      DataReceived[strip][4] = value;
      break;
   case B_BULLETB_HEAD:
      DataReceived[strip][5] = value;
      break;
    case B_BULLETB_TAIL:
      DataReceived[strip][6] = value;
      break;
    case E_EXPLOSION_HEAD:
      DataReceived[strip][7] = value;
      break;
    case E_EXPLOSION_TAIL:
      DataReceived[strip][8] = value;
      break; 
  }// end switch 
} // end of processStrip

void handlePreviousState ()
{
  switch (state)
  {
  case GOT_X:
    processSTRIP (0, currentValue); //for strip 1
    break;
  case GOT_Y:
    processSTRIP (1, currentValue); //for strip 2
    break;
  case GOT_Z:
    processSTRIP (2, currentValue); //for strip 3
    break;
  }  // end of switch  

  currentValue = 0; 
}  // end of handlePreviousState

void processIncomingByte (const byte c)
{
  if (isdigit (c))
  {
    currentValue *= 10;
    currentValue += c - '0';
  }  // end of digit
  
  else
  {
    // The end of the number signals a state or SubState change
    handlePreviousState ();

    // set the new state or subState, if we recognize it
    switch (c)
    {
    case 'X':
      state = GOT_X;
      break;
    case 'Y':
      state = GOT_Y;
      break;
    case 'Z':
      state = GOT_Z;
      break;

    case 'K':
      subState = K_BULLETA_ON;
      break;
    case 'L':
      subState = L_BULLETB_ON;
      break;  
    case 'M':
      subState = M_EXPLOSION_ON;
      break; 
    case 'A':
      subState = A_BULLETA_HEAD;
      break;  
    case 'a':
      subState = A_BULLETA_TAIL;
      break;  
    case 'B':
      subState = B_BULLETB_HEAD;
      break;  
    case 'b':
      subState = B_BULLETB_TAIL;
      break;   
    case 'E':
      subState = E_EXPLOSION_HEAD;
      break;  
    case 'e':
      subState = E_EXPLOSION_TAIL;
      break;   
      
    default:
      state = NONE;
      subState = _NONE;
      break;
    }  // end of switch on incoming byte
  } // end of not digit   
} // end of processIncomingByte


void updateStrips()
{
  //clear the strips
  for (int i = 0; i < 3; i++) //for each strip
      {
        for (int j = 0; j < _NUMPixels; j++) //for each strip
      {
        strips[i].setPixelColor(j, 0);
      }
        strips[i].show();
      }
  //set pixel colors on strip
      for (int i = 0; i < 3; i++) //for each strip
      {
          if (DataReceived[i][0] == 1) //if bulletA is on
          {
            //setPixelColor for i strip
            for (int j = DataReceived[i][3]; j > DataReceived[i][4]; j--)
            {
              strips[i].setPixelColor(j, _color1);
            }
          }
          if (DataReceived[i][1] == 1) //if bulletB is on
          {
            //setPixelColor for i strip
            for (int j = DataReceived[i][5]; j < DataReceived[i][6]; j++)
            {
              strips[i].setPixelColor(j, _color1);
            }
          }
          if (DataReceived[i][2] == 1) //if Explosion is on
          {
            //setPixelColor for i strip
            for (int j = DataReceived[i][8]; j < DataReceived[i][7]; j++)
            {
              strips[i].setPixelColor(j, _color1);
            }
          }
      }

      //refresh strips
      for (int i = 0; i < 3; i++) //for each strip
      {
        strips[i].show();
      }
}

void loop ()
{
  while (Serial.available ())
    processIncomingByte (Serial.read ());

    updateStrips();

  if (millis() - lastPrint >= timeTillNextPrint)
  {
    Serial.println ("Strip 1 data");
    for (int i = 0; i < 9; i++) Serial.println(DataReceived[0][i]);
    Serial.println(" ");
    
    Serial.println ("Strip 2 data");
    for (int i = 0; i < 9; i++) Serial.println(DataReceived[1][i]);
    Serial.println(" ");
    
    Serial.println ("Strip 3 data");
    for (int i = 0; i < 9; i++) Serial.println(DataReceived[2][i]);
    Serial.println(" ");
    
    lastPrint = millis();
  }  
  
}  // end of loop
