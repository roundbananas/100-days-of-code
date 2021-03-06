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

     for (int i = 0; i < 3; i++) // three displays
    {
        m_7SegDisplays[i].Spawn(m_7SegDigits[i], m_7SegDigitPins[i], m_7SegPins[i]); //we're passing the relevant variables for each display to their spawn functions
    }

    p1StartButton.spawn(m_p1StartButtonPin);
    m_RestartButton.spawn(m_RestartButtonPin);

   m_mode = Modes::IDLE_MODE;
   m_ModeStartedAt = millis();
}

void Engine::runEngine()
{
  unsigned long lastTime = 0; //used to calculate dt if we need it

  while(true)
  {
    unsigned long t = millis();
    unsigned long dt = t - lastTime;

    m_Input(t);
    m_Update(dt, t);
    m_Render();
 
    lastTime = t;
  }
  
}
void Engine::loadLevel()
{
  m_Level++;
  m_LoadedBullet = 0;
  m_CurrentExplosion = 0;
  m_CountDownRemaining = 3;

  delete[] m_Players;
  delete[] m_Buttons;
  delete[] m_SlidePots;
  
  delete[] m_Bullets;
  delete[] m_Explosions;

  m_Players = createPlayers(m_NumPlayers);
  m_SlidePots = createPots(m_NumPlayers, m_firstPotPin);
  m_Buttons = createButtons(m_NumPlayers, m_firstButtonPin);

  m_Bullets = createBullets(m_NumBullets);
  m_Explosions = createExplosions(m_NumExplosions); //max number of explosions we'll need is 1 less than numPlayers  

  
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

/*
void Engine::addScore(int playerB, int playerA, float value)
{
  if (value > 0.98 * m_stripLengthArray[0])
  {
    m_Score[playerB] += 50;
    m_Score[playerA] += 50;
  }
  else if (value > 0.95 * m_stripLengthArray[0])
  {
    m_Score[playerB] += 30;
    m_Score[playerA] += 30;
  }
  else
  {
  m_Score[playerA] += (int)(value + 0.0);
  }
}

int Engine::getScore(int player)
{
  return m_Score[player];
}
*/
