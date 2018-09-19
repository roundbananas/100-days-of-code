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
    //PLAYER 1
    m_Player1LEDS.begin(); //initialise pins for output
    m_Player1LEDS.show(); //turn all LEDs off

    //PLAYER2
    m_Player2LEDS.begin(); //initialise pins for output
    m_Player2LEDS.show(); //turn all LEDs off
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

  delete[] m_Players;
  delete[] m_Bullets;
  delete[] m_Buttons;
  delete[] m_SlidePots;

  m_Players = createPlayers(m_NumPlayers);
  m_SlidePots = createPots(m_NumPlayers, m_firstPotPin);
  m_Buttons = createButtons(m_NumPlayers, m_firstButtonPin);
  m_RestartButton.spawn(m_RestartButtonPin);

  m_Bullets = createBullets(m_NumBullets);
}

void Engine::m_Input(unsigned long t)
{
  if((m_mode == Modes::IDLE_MODE))
  {
    if(m_NumPlayersReady >= m_NumPlayers)
    {
       //reset all variables
      for (int i=0; i < m_NumPlayers; i++)
      {
         m_Score[i] = 0;
      }   
      m_NumPlayersReady = 0;
      m_LoadedBullet = 0;
      m_Level = 0;

      loadLevel();
      m_mode = Modes::COUNTDOWN;
    }
    else
    {
      for (int i=0; i < m_NumPlayers; i++)
      {
        if (m_Buttons[i].updateButton() && !m_Players[i].isReady())
        {
          m_Players[i].setReady();
          m_NumPlayersReady++;
        }
      }
    }
  }
  
  if((m_mode == Modes::PLAYING))
  {
    for (int i=0; i < m_NumPlayers; i++)
    {
      if (m_Buttons[i].updateButton() && !m_Players[i].getHasFired())
      {
        m_Players[i].setHasFired();
        m_Players[i].setBulletIndex(m_LoadedBullet);
        m_Bullets[m_LoadedBullet].shoot(m_SlidePots[i].getPotValue(),m_Players[i].getColour()); 
        m_LoadedBullet++;
      }
    }
    if(m_RestartButton.updateButton())
    {  
      m_mode = Modes::IDLE_MODE;
    }
  }
}

void Engine::m_Update(unsigned long dt, unsigned long t)
{
  if(m_mode == Modes::PLAYING)
  {
    for (int i = 0; i < m_NumPlayers; i++)
    {
      m_Bullets[m_Players[i].getBulletIndex()].updateBullet(dt);
    }

    //Handle collisions etc

    
  }
  

  if((m_mode == Modes::COUNTDOWN))
  {
    bool countDownStarted = false;
    int countDown = 3000; //3 second countdown
    unsigned long countDownStartedAt;
    if(!countDownStarted)
    {
      countDownStartedAt = t;
      countDownStarted = true;
    }
    if (countDownStarted)
    {
      if ((t - countDownStartedAt) < 1000)
      {
        //PRINT TO SCREEN: 3
      }
      else if ((t - countDownStartedAt) < 2000)
      {
        //PRINT TO SCREEN: 2
      }
      else if ((t - countDownStartedAt) < countDown)
      {
        //PRINT TO SCREEN: 1
      }
      else if ((t - countDownStartedAt) > countDown)
      {
        //PRINT TO SCREEN: GO!
        m_mode = Modes::PLAYING;
      }
    }
  }
}

void Engine::m_Render()
{
  /*
    for(int j = getHead(); j > getTail(); j--)
      {  
        for (int k = (m_Head - m_Tail) - 1; k >= 0; k--)
        {
           m_Player1LEDS.setPixelColor(i, m_RedValues[j], m_GreenValues[j], m_BlueValues[j]);
        }
      }
  m_Player1LEDS.show();
  m_Player2LEDS.show();
  */
}
