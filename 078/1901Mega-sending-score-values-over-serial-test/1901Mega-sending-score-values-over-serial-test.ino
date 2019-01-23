/*
 * Sending Data by Serial, with State Machine
 * 
 * Created by Carl Turner 3 Jan 2018
 * roundbananas.com
  */

 /*
  * We'll update three values, at different intervals, and send them over serial to another arduino.
  * 
  * Mode Codes. These indicate what the subsequent number relates to. We use them to drive mode machine
  *   A - relates to display #1, Score
  *   B - relates to display #2, Current Round
  *   C - relates to display #3, Best Rounds  
  * 
  * We'll use an Array to hold the data:
  *   Array index   Relates to      
  *     [0]           display #1  
  *     [1]           display #2   
  *     [2]           display #3  
  */

void setup ()
{
  Serial.begin (250000);
  Serial.print ("SETUP - Mega");
}

unsigned long updatePeriod = 1000; 
unsigned long lastTime = 0;

int Score = 0; //score can be 1000 or more in size
int CRound = 0;
int BRounds = 0;

const static int m_NumDisplays = 3;
int m_DataToSend[m_NumDisplays] = {};

bool firstTime = true;

void loop()
{
  //(Note - displays will be initialised to display 0's by the program on the other arduino)
  
  if((millis() - lastTime) > updatePeriod)
  {
    Score++;
    Serial.print('A');
    Serial.println(Score);

      CRound++;
      Serial.print('B');
      Serial.println(CRound);

          BRounds++;
          Serial.print('C');
          Serial.println(BRounds);

    lastTime = millis();
  }
}


  
