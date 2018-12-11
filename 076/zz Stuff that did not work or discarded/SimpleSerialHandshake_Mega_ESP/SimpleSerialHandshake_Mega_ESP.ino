/*
 * THIS DOESNT WORK YET.
 * * THIS DOESNT WORK YET.
 * * THIS DOESNT WORK YET.
 * * THIS DOESNT WORK YET.
 * * THIS DOESNT WORK YET.
 * * THIS DOESNT WORK YET.
 * 
 * Simple Handshake - Arduino Mega & Esp8266 over hardware serial
 * 
 * Created by Carl Turner 18 Nov 2018
 * roundbananas.com
 * 
 * 
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

 /*** CONNECTIONS ****/
 /* Mega pin     Logic Level Shifter    ESP8266 (Wemos mini)
  * TX (1)       HV-TX0       LV-TXI    RX
  * RX (0)       -            -         TX
  */

 /*** SELECT BOARD TO UPLOAD TO ****/
bool Mega = true; //false means we're uploading to ESP8266

 /*** VARIABLES ****/
byte DataToSend = 2;  //data to be sent by the Mega
byte DataReceived;    //variable to hold data received by ESP
byte HandShakeCode = 254; //Mega won't send until it receives this from the ESP
bool OkToSend = false;
bool OkToReceive = false;  //a flag to help us switch between getting data and updating leds.

void setup()
{
  Serial.begin(9600);

  if(Mega)
  {
   Serial.println("SETUP - Mega");
  }
  else
  {
    Serial.println("SETUP - ESP");
  }
}

void loop()
{
  if (Mega)
  {
    //wait till ESP says it's ready to receive
    if(!OkToSend)
    {
      if (Serial.available() > 0) 
      {
        byte incomingByte = Serial.parseInt();
        if (incomingByte == HandShakeCode)
        {
          OkToSend = true;
        }
      }
    }
    else //ok to send
    {
      Serial.print(DataToSend);
      OkToSend = false;
    }
    
  } //end Mega loop

  else //ESP
  {
    if(OkToReceive) //let's get the data
    {
      while (Serial.available() > 0)
      {
        DataReceived = Serial.parseInt();
        Serial.println(DataReceived);
        OkToReceive = false;  //we've got the data, we want to let Mega know when it's ok to send again
      } 
    } //end get the data
    else
    {
      Serial.print(HandShakeCode);
      OkToReceive = true;
    } //end send the handshake
  } //end ESP loop
} //end main loop
