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

void setup ()
{
  Serial.begin (115200);
  state = NONE;
  subState = _NONE;
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

void loop ()
{
  while (Serial.available ())
    processIncomingByte (Serial.read ());
/*
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
  */
}  // end of loop
