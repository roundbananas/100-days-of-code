/*
 * Carl Turner 1/11/2018
 * roundbananas.com
 * 
 * Directly control 7 segment display, without a library.
 * Useful if you just want to continuously display a number,
 * without having to constantly refresh the display, which is 
 * required if you use SevSeg library.
 * 
 * This code was designed to run on a Arduino Mega.
 * 7-segment module: HS420561K-32 (common cathode).
 * Resistors on digit pins
 * 
 * I adapted code found here:
 * https://www.jameco.com/jameco/workshop/techtip/working-with-seven-segment-displays.html
 */

/*----------------------------CONSTANTS--------------------------------*/
const byte numDigits = 4;
byte digitPins[] = {28, 29, 30, 31};  
byte segmentPins[] = {32, 33, 34, 35, 36, 37, 38, 39};

int displayBuffer[numDigits]; //holds digits to be displayed

byte segCode[11][8] = {
// 7 segment code table
//  a  b  c  d  e  f  g  .
  { 1, 1, 1, 1, 1, 1, 0, 0},  // 0
  { 0, 1, 1, 0, 0, 0, 0, 0},  // 1
  { 1, 1, 0, 1, 1, 0, 1, 0},  // 2
  { 1, 1, 1, 1, 0, 0, 1, 0},  // 3
  { 0, 1, 1, 0, 0, 1, 1, 0},  // 4
  { 1, 0, 1, 1, 0, 1, 1, 0},  // 5
  { 1, 0, 1, 1, 1, 1, 1, 0},  // 6
  { 1, 1, 1, 0, 0, 0, 0, 0},  // 7
  { 1, 1, 1, 1, 1, 1, 1, 0},  // 8
  { 1, 1, 1, 1, 0, 1, 1, 0},  // 9
  { 0, 0, 0, 0, 0, 0, 0, 0}   //off
};

/*----------------------------FUNCTIONS--------------------------------*/
void RefreshDisplay(int digit3, int digit2, int digit1, int digit0)
{
  digitalWrite(digitPins[0], HIGH);  // displays digit 0 (least significant)
  digitalWrite(digitPins[1], HIGH );
  digitalWrite(digitPins[2], HIGH );
  digitalWrite(digitPins[3], LOW );
  setSegments(digit0);
  delay(5);
  digitalWrite(digitPins[0], HIGH);    // then displays digit 1
  digitalWrite(digitPins[1], HIGH);
  digitalWrite(digitPins[2], LOW );
  digitalWrite(digitPins[3], HIGH );
  setSegments(digit1);
  delay(5);
  digitalWrite(digitPins[0], HIGH);    // then displays digit 2
  digitalWrite(digitPins[1], LOW);
  digitalWrite(digitPins[2], HIGH);
  digitalWrite(digitPins[3], HIGH );
  setSegments(digit2);
  delay(5);
  digitalWrite(digitPins[0], LOW);    // then displays digit 3
  digitalWrite(digitPins[1], HIGH);
  digitalWrite(digitPins[2], HIGH );
  digitalWrite(digitPins[3], HIGH);
  setSegments(digit3);
  delay(5);
}

void setSegments(int n)
{
  for (int i=0; i < 8; i++)
  {
    digitalWrite(segmentPins[i], segCode[n][i]);
  }
}

/*----------------------------SETUP--------------------------------*/
void setup() {
  Serial.begin(9600);
  
 // bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
 // byte hardwareConfig = COMMON_CATHODE; // See README.md for options
 // bool updateWithDelays = false; // Default. Recommended
 // bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros

  for (int i = 0; i < numDigits; i++)
  {
    pinMode(digitPins[i], OUTPUT);
    displayBuffer[i] = 10;  //initialise each digit to 'off'
  }
    
  for (int j = 0; j < 8; j++)
  {
    pinMode(segmentPins[j], OUTPUT);
  }
}

/*----------------------------VARIABLES--------------------------------*/
int i = 0, j =0, k=0, m=0; 
int startTime = 0;
int endTime;

/*----------------------------MAIN LOOP--------------------------------*/
void loop() {    
   //digitalWrite(digitPins[0], LOW); //set to LOW to activate digit pins
    //digitalWrite(segmentPins[0], HIGH); //set to HIGH to activate segments

   RefreshDisplay(displayBuffer[3], displayBuffer[2], displayBuffer[1], displayBuffer[0]);  // Refreshes the display with the contents of displayBuffer

   endTime = millis();                  
   if ((endTime - startTime) >= 10)
   {
      if (++i > 9)
      {
        i = 0;
        if (++j > 9) 
        {
          j = 0;
          if (++k > 9) 
          {
            k = 0;
            if (++m > 9) 
            {
              m = 0;
            }
          }
        }
      }
      displayBuffer[0] = i;                // send the updated count to the display buffer
      displayBuffer[1] = j;
      displayBuffer[2] = k;
      displayBuffer[3] = m;

      startTime = endTime;
   }
}
/// END ///
