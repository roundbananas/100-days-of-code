//
//  Engine.cpp
//
//  Created by Carl Turner on 18/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#include "Engine.h"
#include "Arena.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>

Engine::Engine()
{  
    //Declare and initialise displays
    //PLAYER 1
    int m_NumPixels1 = 30;
    int m_DataPin1 = 3;
    int m_ClockPin1 = 4;
    Adafruit_DotStar m_Player1LEDS = Adafruit_DotStar(m_NumPixels1, m_DataPin1, m_ClockPin1, DOTSTAR_BRG);
    m_Player1LEDS.begin(); //initialise pins for output
    m_Player1LEDS.show(); //turn all LEDs off

    //PLAYER2
    int m_NumPixels2 = 30;
    int m_DataPin2 = 5;
    int m_ClockPin2 = 6;
    Adafruit_DotStar m_Player2LEDS = Adafruit_DotStar(m_NumPixels1, m_DataPin1, m_ClockPin1, DOTSTAR_BRG);
    m_Player2LEDS.begin(); //initialise pins for output
    m_Player2LEDS.show(); //turn all LEDs off
}

void Engine::runEngine()
{
  unsigned long lastTime = 0; //used to calculate dt if we need it

  m_Player1->spawn(255, 0, 0); 
  m_Player2->spawn(0, 0, 255);
  
  while(true)
  {
    unsigned long t = millis();
    unsigned long dt = t - lastTime;
    
    m_Input(dt);
    m_Update(t);
    m_Render();
    
    lastTime = t;
  }
  
}
void Engine::loadLevel()
{
  m_Level++;

  delete[] m_Bullets;
  delete[] m_Buttons;
  delete[] m_SlidePots;

  m_Bullets = createBullets(m_NumBullets);
  m_SlidePots = createPots(m_NumPlayers);
  m_Buttons = createButtons(m_NumPlayers);

  //Set bullet colour. THIS IS WRONGLY DONE CURRENTLY
  m_Bullets[0].setColour(255, 0, 0);
  m_Bullets[1].setColour(0, 0, 255);

}

void Engine::m_Input(unsigned long t)
{
  if((m_mode == Modes::IDLE_MODE))
  {
    m_Player1->setScore(0);
    m_Player2->setScore(0);
    loadLevel();
    m_mode = Modes::PLAYING;
  }
  if((m_mode == Modes::PLAYING))
  {
    for (int i = 0; i < m_NumPlayers; i++)
    {
      if(!m_Bullets[i].isInFlight() && m_Buttons[i].UpdateButton())
      {
        m_Bullets[i].setBulletSpeed(m_SlidePots[i].getPotValue());
        m_Bullets[i].shoot();
        
        /*
         * the player doesn't need to hold HasFired variable. It's held by bullet is inflight.
         switch(i)
        {
          case 0:
            m_Player1->updatePlayer(t);
          case 1:
            m_Player2->updatePlayer(t);
        }
        */
      }
    }
  }
}
void Engine::m_Update(unsigned long dt)
{
  if(m_mode == Modes::PLAYING)
  {
    for (int i = 0; i < m_NumPlayers; i++)
    {
      m_bullets[i].updateBullet(dt);
 /*     
      for(int j = getHead(); j > getTail(); j--)
      {  
        for (int k = (m_Head - m_Tail) - 1; k >= 0; k--)
        {
           m_ledStrip.setPixelColor(i, m_RedValues[j], m_GreenValues[j], m_BlueValues[j]);
        }
      }
      */
    }

    
  }
  
  if(m_mode == Modes::COUNTDOWN && (dt > 3)) //magic number 3 seconds. Change this eventually
  {
    m_mode = Modes::PLAYING;
  }
}
void Engine::m_Render()
{
  
}
