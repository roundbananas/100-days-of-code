/*
 * Sending Data by Serial, with State Machine
 * 
 * Created by Carl Turner 11 Dec 2018
 * roundbananas.com
 * 
 * 
  */

 /*
  * We'll send data from the this sketch, and put it into an Array when 
  * received at the other end, byte DataReceived[3][9]
  * 
  * This info is included here for reference, to help understand what is being sent.
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

void setup ()
{
  Serial.begin (115200);
  Serial.print ("SETUP - Mega");
}

byte head  = 0, tail = -10; // Index of first 'on' and 'off' pixels

byte NUMPIXELS = 25;
byte BAOn = 1;

void loop()
{
  if(++head >= NUMPIXELS) head = 0; 
  if(++tail >= NUMPIXELS) tail = 0;

  Serial.print('X');
  Serial.print('K');
  Serial.print(BAOn);
  Serial.print('A');
  Serial.print(head);
  Serial.print('a');
  Serial.println(tail);
  
  Serial.print('Y');
  Serial.print('K');
  Serial.print(BAOn);
  Serial.print('A');
  Serial.print(head);
  Serial.print('a');
  Serial.println(tail);

  delay(20);
}


  
