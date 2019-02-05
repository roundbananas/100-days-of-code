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
    //Initialise displays
//  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
 // clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
//#endif
 
    for (int i = 0; i < m_NumPlayers; i++)
    {
        m_PlayerLEDS[i].begin(); //initialise pins for output
        m_PlayerLEDS[i].show(); //turn all LEDs off
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

    //turn score display off
    Serial.print('B');
    
    p1StartButton.spawn(m_p1StartButtonPin);
    m_RestartButton.spawn(m_RestartButtonPin);

   m_mode = Modes::IDLE_MODE;
   m_ModeStartedAt = millis();

}

void Engine::runEngine()
{
  unsigned long lastTime = 0; //used to calculate dt if we need it

  int loop_counter = 0;             //holds the count for every loop pass
  long previous_millis = millis();         //holds the previous millis
  float loop_time;              //holds difference (loop_timer_now - previous_millis) = total execution time
  int loop_test_times = 30000;  //Run loop 20000 times then calculate time


  while(true)
  {
    unsigned long t = millis();
    unsigned long dt = t - lastTime;
     
    m_Input(t); 
    m_Update(dt, t);
    m_Render(t); //This function loop time is 28ms.
    
    lastTime = t;

    loop_counter++;
    if (loop_counter >= loop_test_times)
      { 
        loop_time = (t - previous_millis) / loop_test_times;   
        Serial.print ("loop_time: ");
        Serial.println(loop_time);

        previous_millis = t;   
        loop_counter = 0;
      }
  }
  
}

void Engine::UpdateStrips(unsigned long currentTime) //I did try to put a timer on this to decrease LED refresh rate, to try to reduce 7segmentdisplay flicker. But couldn't find a sweet spot.
{
   for (int i = 0; i< m_NumPlayers; i++) m_PlayerLEDS[i].show();
}

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

  //Send score to 4-digit display
  Serial.print('A');
  Serial.print(m_ScoreController.GetCurrentScore());

  //Send updated current round and best rounds to single-digit display
  Serial1.print('B');
  Serial1.print(m_Level);
  Serial1.print('C');
  Serial1.print(m_BestRounds);
  
  m_LoadedBullet = 0;
  m_CurrentExplosion = 0;
  m_CountDownRemaining = m_CountDownDuration;
  m_NewBestRounds = false;

//  m_ScoreDisplay.setNumber(m_ScoreController.GetCurrentScore());
//  m_CurrentRoundDisplay.setNumber(m_Level);
 // m_BestRoundsDisplay.setNumber(m_BestRounds);

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
