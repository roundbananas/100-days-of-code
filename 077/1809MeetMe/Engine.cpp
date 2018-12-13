//
//  Engine.cpp
//
//  Created by Carl Turner on 18/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#include "Engine.h"
#include "Arena.h"

Engine::Engine()
{  

	for (int i = 25; i < 53; i++)
	{pinMode(i, OUTPUT);
	}

    //Initialise button LEDs. The way I do this is inconsistent with initialising the buttons themselves, which is done in loadLevel(). I could probably put the button LEDs in loadLevel() too.
    for (int i = 0; i < 3; i++)
    {
      m_PlayerButtonLeds[i].Spawn(m_PlayerButtonLedPins[i], m_PlayerButtonLedOnDurations[i]);
      m_PlayerButtonLeds[i].SetMode(0);
      m_PlayerBoostLeds[i].Spawn(m_PlayerBoostLedPins[i], m_PlayerBoostLedOnDurations[i]);
      m_PlayerBoostLeds[i].SetMode(0);
    }
     m_NewGameButtonLED.Spawn(m_NewGameButtonLedPin, m_NewGameButtonLedOnDuration);
     m_NewGameButtonLED.SetMode(2);

     m_ScoreDisplay.begin(m_Score_HardwareConfig, m_Score_NumDigits, m_Score_DigitPins, m_Score_SegmentPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_ScoreDisplay.setBrightness(100);
     
     m_CurrentRoundDisplay.begin(m_CurrentRound_Score_HardwareConfig, m_CurrentRound_NumDigits, m_CurrentRound_DigitPins, m_CurrentRound_SegmentPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_CurrentRoundDisplay.setBrightness(100);
     
     m_BestRoundsDisplay.begin(m_BestRounds_Score_HardwareConfig, m_BestRounds_NumDigits, m_BestRounds_DigitPins, m_BestRounds_SegmentPins, m_ResistorsOnSegments, m_UpdateWithDelays, m_LeadingZeros);
     m_BestRoundsDisplay.setBrightness(100);

    p1StartButton.spawn(m_p1StartButtonPin);
    m_RestartButton.spawn(m_RestartButtonPin);

   m_mode = Modes::IDLE_MODE;
   m_ModeStartedAt = millis();
}

void Engine::runEngine()
{
  unsigned long lastTime = 0; //used to calculate dt if we need it

  int loop_counter = 0;             //holds the count for every loop pass
  long loop_timer_now;          //holds the current millis
  long previous_millis = millis();         //holds the previous millis
  long loop_time;              //holds difference (loop_timer_now - previous_millis) = total execution time
  int loop_test_times = 10000;  //Run loop x times then calculate loop duration

  while(true)
  {
    unsigned long t = millis();
    unsigned long dt = t - lastTime;
     
    m_Input(t); 
    m_Update(dt, t);
    m_Render(t); 
    m_SendDataToESP();
    Serial.println("End loop");

    //Loop time was 28ms when refreshing led strips on Mega - ie the show() function.
  /*  lastTime = t;
    loop_counter++;
    if (loop_counter == loop_test_times)
      { previous_millis = loop_timer_now;   
        loop_timer_now = millis(); 
        loop_counter = 0;
        loop_time = (loop_timer_now - previous_millis) / loop_test_times;  
        Serial.print("LOOP TIME: "); 
        Serial.println(loop_time);
      }
  */
      
  }
  
}

void Engine::UpdateArray()
{
	
	if((m_mode == Modes::IDLE_MODE))
	{
		//do nothing
	}
	
	if(m_mode == Modes::LEVELLING_UP)
	{
		//do nothing
	}// end LEVELLING_UP mode
	
	if(m_mode == Modes::COUNTDOWN)
	{
		//send data for countdownremaining, using the array element for BulletAHead (saves creating a whole new array element)
		for (int i = 0; i < m_NumPlayers; i++)
    {
		  m_DataToSend[i][4] = m_CountDownRemaining;
    }
	}
	
	if(m_mode == Modes::PLAYING)
	{
	/*
 	* UPDATE THE ARRAY VALUES IN PLAYING MODE
 	*/
//Set the mode variables in the array.
//We can just assign the current mode to each element in the first column of the array.
//-->Because the mode is an enum, it is automatically assigned a number based on it's 
// position in the enum list. AND we've been consistent with how we've defined the 
// 'enum class Modes' and how we're managing possible values in the first element 
// of the array.
// We don't actually need to do this. We don't even need the mode as part of the array. 
// I realise, after writing all this. Duh. Because the mode value is implicit in the 
// code. ie 'I' == Idle Mode, it can't be anything else.

//Get explosion details, they're not as straight forward as the rest
//we need to find out which strips have explosions active, and what the index of the explosion
//is for that strip. Because explosion indices don't align with strip/player/bullet indices.
bool explosionActiveOnStrip[m_NumPlayers] = {}; //is an explosion active on each of the strips?
int explosionIndexOnStrip[m_NumPlayers] = {}; //what is the index of the explosion on each strip?

for (int i = 0; i < m_NumExplosions; i++)
 {
   if (m_Explosions[i].IsActive())
   {
   	int strip = m_Explosions[i].GetStrip();
   	explosionActiveOnStrip[strip] = true;	//used for telling ESP if there's an explosion on a strip
   	explosionIndexOnStrip[strip] = i;		//used for getting the explosion position to send to ESP
   }
}

//Now update the array
for (int i = 0; i < m_NumPlayers; i++)
{
	 //m_DataToSend[i][0] = m_mode; //we don't actually need this array element I think, because we can send the mode directly.

	////If the bullet is on, update it's position too
	if(m_Bullets[i].AIsInFlight())
	{
		m_DataToSend[i][1] = 1; //this works since bullet i, player i and strip i are all related/associated
		m_DataToSend[i][4] = m_Bullets[i].getHeadAPos();
		m_DataToSend[i][5] = m_Bullets[i].getTailAPos();
	}
	if(m_Bullets[i].BIsInFlight())
	{
		m_DataToSend[i][2] = 1; //we need to handle not drawing BulletB on the i'th player's strip in the ESP
		m_DataToSend[i][6] = m_Bullets[i].getHeadBPos();
		m_DataToSend[i][7] = m_Bullets[i].getTailBPos();
	}
	if(explosionActiveOnStrip[i])
	{
		m_DataToSend[i][3] = 1; 
		m_DataToSend[i][8] = m_Explosions[explosionIndexOnStrip[i]].GetHead();
		m_DataToSend[i][9] = m_Explosions[explosionIndexOnStrip[i]].GetTail();
	}
} //end for each player
} //end PLAYING MODE



//if GAME_OVER mode, ESP will handle any animation, based on time
if (m_mode == Modes::GAME_OVER)
{     
	//do nothing
}// end GAME_OVER mode
}// end UpdateArray()

void Engine::StartNewGame()
{
  //reset all variables
      m_ScoreController.ResetScore();
      m_NumPlayersReady = 0;
      m_Level = -1;
      //don't reset m_BestRounds. We'll only do that through a hard reset on the board. OR if I add another 'factory reset' button.

      loadLevel();
           
      delay(100); //allow for button bounce, otherwise we just come straight back here
      m_mode = Modes::COUNTDOWN;
}

void Engine::loadLevel()
{
  m_Level++;
  m_LoadedBullet = 0;
  m_CurrentExplosion = 0;
  m_CountDownRemaining = m_CountDownDuration;
  m_NewBestRounds = false;

  m_ScoreDisplay.setNumber(m_ScoreController.GetCurrentScore());
  m_CurrentRoundDisplay.setNumber(m_Level);
  m_BestRoundsDisplay.setNumber(m_BestRounds);

  delete[] m_Players;
  delete[] m_Buttons;
  delete[] m_BoostButtons;
  delete[] m_SlidePots;
  
  delete[] m_Bullets;
  delete[] m_Explosions;

  m_Players = createPlayers(m_NumPlayers);
  m_SlidePots = createPots(m_NumPlayers, m_firstPotPin);
  m_Buttons = createButtons(m_NumPlayers, m_firstButtonPin);
  m_BoostButtons = createBoostButtons(m_NumPlayers, m_FirstBoostPin);

  m_Bullets = createBullets(m_NumBullets);
  m_Explosions = createExplosions(m_NumExplosions); //max number of explosions we'll need is 1 less than numPlayers  

  m_IdleFlag = false;
  m_CountdownFlag = false;
  m_PlayingFlag = false;
  m_LevelUpFlag = false;
  m_GameOverFlag = false; 
}

int Engine::getExplodeStrip(int j)
{
  int index;
  for (int i = 0; i < m_NumPlayers; i++)
  {
    if (j == m_Players[i].getBulletIndex())
    {
      index = i;
    }
  }
  return index;
}
