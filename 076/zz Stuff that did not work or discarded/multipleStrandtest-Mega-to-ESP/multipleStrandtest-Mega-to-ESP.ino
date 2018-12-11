/*
 * Created by Carl Turner 18 Nov 2018
 * roundbananas.com
 * 
 * This is a test program to establish serial communication between Arduino Mega and ESP8266. 
 * I want to use lots of pins on the Mega, but outsource the processor-intensive led refreshing
 * to the ESP. 
 * 
 * On MEGA
 * 1. calculate pixel movement on MEGA
 * 2. send pixel movement to ESP
 * 
 * ON ESP8266
 * 1. receive data
 * 2. set pixel colours on strip
 * 3. refresh strip (render)
  */

/*******
 * NOTE for NodeMCU or WEMOS mini ESP8266 module.
 * Pin assignments are confusing.
 * Pin label on board - Pin number you need to give assign it in software
 * TX (10)  - 1  
 * RX (9)   - 3
 * 
 * D0       - 16
 * D1       - 5
 * D2       - 4
 * D3       - 0              
 * D4       - 2
 * 
 * D5       - 14
 * D6       - 12
 * D7       - 13
 * D8       - 15
 * 
 * A0       - 0 (analog)
 ******/

 /*
  * We'll send the following data from the Mega, and put it into an Array when received on the ESP.
  * byte LedUpdateData[3][9]
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

/*** SELECT BOARD TO UPLOAD TO ****/
bool Mega = true; //false means we're uploading to ESP8266

  /*****
   * MEGA Objects and Variables
   *****/
byte BulletLength = 2;
uint16_t NUMPixels = 25;

byte BulletA_isOn[3] = {1, 0, 0};
byte BulletB_isOn[3] = {0, 1, 0};
byte Explosion_isOn[3] = {0, 0, 1};

byte BA_Head[3] = {0, 0, 0};
byte BA_Tail[3] = {0 - BulletLength, 0 - BulletLength, 0 - BulletLength};

byte BB_Head[3] = {25, 25, 25};
byte BB_Tail[3] = {0 - BulletLength, 0 - BulletLength, 0 - BulletLength};

byte Ex_Head[3] = {12, 12, 12};
byte Ex_Tail[3] = {12 - BulletLength, 12 - BulletLength, 12 - BulletLength}; 

byte DataToSend[3][9] = 
      { 
        {BulletA_isOn[0], BulletB_isOn[0], Explosion_isOn[0], BA_Head[0], BA_Tail[0], BB_Head[0], BB_Tail[0], Ex_Head[0], Ex_Tail[0]}, //bullet and explosion data for Strip 1
        {BulletA_isOn[1], BulletB_isOn[1], Explosion_isOn[1], BA_Head[1], BA_Tail[1], BB_Head[1], BB_Tail[1], Ex_Head[1], Ex_Tail[1]}, //bullet and explosion data for Strip 2
        {BulletA_isOn[2], BulletB_isOn[2], Explosion_isOn[2], BA_Head[2], BA_Tail[2], BB_Head[2], BB_Tail[2], Ex_Head[2], Ex_Tail[2]}  //bullet and explosion data for Strip 3
      }; 

unsigned long lastTime = 0;

  /*****
   * ESP Objects and Variables
   *****/
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

int DataReceived[3][9]; //where we'll put the values we receive
uint32_t _color1 = 0xFF0000; 
uint32_t _color2 = 0x0064EF;

int  _serialCount = 0;      //a count of how many values we've received
bool _messageComplete = false;  //a flag to help us switch between getting data and updating leds.

void setup()
{
  Serial.begin(9600);
  
  if (Mega)
  {
    Serial.println("SETUP - Mega");
  
  }
  else
  {
    Serial.println("SETUP - ESP");

    pinMode(_DataPin1, OUTPUT);
    pinMode(_ClockPin1, OUTPUT);
    pinMode(_DataPin2, OUTPUT);
    pinMode(_ClockPin2, OUTPUT);
  
    strip1.begin(); // Initialize pins for output
    strip2.begin();
    strip1.show();  // Turn all LEDs off ASAP
    strip2.show();
  }
}

void loop()
{
  if (Mega)
  {
    //calculate pixel movement
    for (int i = 0; i < 3; i++) //3 = number of strips
    {
      if(++BA_Head[i] >= NUMPixels) BA_Head[i] = 0;  // Increment head index. Reset if head has gone off end of strip
      if(++BA_Tail[i] >= NUMPixels) BA_Tail[i] = 0; // Increment, reset tail index if it's off end of strip

      if(--BB_Head[i] <= 0) BB_Head[i] = NUMPixels; 
      if(--BB_Tail[i] <= 0) BB_Tail[i] = NUMPixels;

      if(millis() - lastTime > 1500) 
      {
        Ex_Head[i] = 12;
        Ex_Tail[i] = 10;
        lastTime = millis();
      }
      else {Ex_Head[i]++; Ex_Tail[i]--;}
    }
    delay (50); //so we can see it with human eye
    
    //send updated head, tail and strip number to ESP
    if (Serial.available() > 0) 
    {
      // read the incoming byte:
      uint8_t incomingByte = Serial.read();
      Serial.println(incomingByte);
      if(incomingByte == 'Q')
      {  //if incoming data is the expected request (request code = 'Q' in this example)
        for (int j = 0; j < 9; j++)
        {
          Serial.print(DataToSend[0][j]);
        }
        for (int j = 0; j < 9; j++)
        {
          Serial.print(DataToSend[1][j]);
        }
        for (int j = 0; j < 9; j++)
        {
          Serial.print(DataToSend[2][j]);
        }        
      }
    }  
  }
  else //ESP
  {  
    refresh:     
    //receive data from Mega
    if (_messageComplete)
    {
      Serial.println("Updating Strip ");

        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < 9; j++)
          {
             Serial.println(DataReceived[i][j]);
          }
          Serial.println(" ");
        } 

      //clear strips
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < NUMPixels; j++)
        {
          strips[i].setPixelColor(j, 0);
        }
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
      _messageComplete = false;
    } //end if messagecomplete
    
    else
    {
    //  Serial.println("Getting Data ");
      int dataCount = 1;
      Serial.write(81);
      while (Serial.available() > 0)
      {
        //add latest value from serial to array
       
          for (int j = 0; j < 9; j++)
          {
            DataReceived[0][j] = Serial.parseInt();
            dataCount++;
          }
        Serial.println("Got Data ");
        _messageComplete = true;
       goto refresh;
      } //end while
    } //end else (read serial) 
  } //end else (ESP)
}
