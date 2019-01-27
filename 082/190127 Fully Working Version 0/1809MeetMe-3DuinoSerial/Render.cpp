//
//  Render.cpp
//
//  Created by Carl Turner on 20/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#include "Engine.h"

void Engine::m_Render(unsigned long t)
{  
  
  if((m_mode == Modes::IDLE_MODE))
  { 
    if(!m_IdleFlag)
    {
      //turn score to zero
      Serial.print('A');
      Serial.print(0);

      //Turn level displays to zero
      Serial1.print('B');
      Serial1.print(0);
      Serial1.print('C');
      Serial1.print(0);
      
      for (int i = 0; i < m_NumPlayers; i++) 
      {
        for (int j = 0; j < m_stripLengthArray[i]; j++) 
        {
          m_PlayerLEDS[i].setPixelColor(j, 0);
        }
      }
      
      UpdateStrips(t);
      
      for (int i = 0; i < 3; i++)
      {
        m_PlayerButtonLeds[i].Update();
        m_PlayerBoostLeds[i].Update();
      }
      
      m_IdleFlag = true;
    }
    
 //   m_ScoreDisplay.refreshDisplay();
 //   m_CurrentRoundDisplay.refreshDisplay();
 //   m_BestRoundsDisplay.refreshDisplay();

    //flash New Game button light
    m_NewGameButtonLED.Update();
   
  }

  if((m_mode == Modes::COUNTDOWN))
  {  
      //clear the strips, once
      if (!m_CountdownFlag)
      {         
        for (int i = 0; i < m_NumPlayers; i++)
        { 
            for (int j = m_CountDownDuration; j < m_stripLengthArray[i]; j++) 
                m_PlayerLEDS[i].setPixelColor(j, 0);
         
         
        }
        UpdateStrips(t);
        //turn off New Game light and boost leds
        m_NewGameButtonLED.Update();
        for (int i = 0; i < m_NumPlayers; i++)
        {
          m_PlayerBoostLeds[i].Update();
        }
        m_CountdownFlag = true;
      }
      
      //update the strips
     for (int i = 0; i < m_NumPlayers; i++)
        { 
            m_PlayerLEDS[i].setPixelColor(m_CountDownRemaining, 0);

            for (int k = 0; k < m_CountDownRemaining; k++)
                m_PlayerLEDS[i].setPixelColor(k, 0xff0000); 
         
 //           m_ScoreDisplay.refreshDisplay();
  //          m_CurrentRoundDisplay.refreshDisplay();
  //          m_BestRoundsDisplay.refreshDisplay();
        }

    //flash player lights
    for (int i = 0; i < m_NumPlayers; i++)
    {
      m_PlayerButtonLeds[i].Update();
    }
       
     UpdateStrips(t);
  }

   /*
   * LEVELLING UP MODE
   */
  if(m_mode == Modes::LEVELLING_UP)
  {
     //   Serial.println ("Render - LEVELLING_UP_MODE");
 // Serial.println(m_ScoreController.GetCurrentScore());
    //Update the score display  
 //   m_PointsDisplay.SetNumber(m_ScoreController.GetCurrentScore());
 //   m_PointsDisplay.RefreshDisplay();
//  m_ScoreDisplay.refreshDisplay();
 // m_CurrentRoundDisplay.refreshDisplay();
 // m_BestRoundsDisplay.refreshDisplay();
 
  }//end Levelling_Up mode

if((m_mode == Modes::GAME_OVER))
  {  
  //  m_ScoreDisplay.refreshDisplay();
  //  m_CurrentRoundDisplay.refreshDisplay();
  //  m_BestRoundsDisplay.refreshDisplay();

    UpdateStrips(t);
    
    //flash New Game button light
    m_NewGameButtonLED.Update();

    if(!m_GameOverFlag)
    {
        //Send updated score to 4-digit display
        Serial.print('A');
        Serial.println(m_ScoreController.GetCurrentScore());
  
      for (int i = 0; i < m_NumPlayers; i++)
          { 
              for (int j = 0; j < m_stripLengthArray[i]; j++) 
                  m_PlayerLEDS[i].setPixelColor(j, 0);
  
              for (int k = 45; k < 55; k++)
                  m_PlayerLEDS[i].setPixelColor(k, 0xff0000);
            
       
          }
          UpdateStrips(t);
          //turn of player button lights
          for (int i = 0; i < 3; i++)
          {
            m_PlayerButtonLeds[i].Update();
            m_PlayerBoostLeds[i].Update();
          }
          
       m_GameOverFlag = true;
    }
  }

  /*
   * PLAYING MODE
   */
  
  if(m_mode == Modes::PLAYING)
  {
     for (int i = 0; i < m_NumPlayers; i++)
    { 
      if (m_Players[i].isExploding()) //clear the strip
      {  
        for (int j = 0; j < m_stripLengthArray[i]; j++) m_PlayerLEDS[i].setPixelColor(j, 0);
      }
      else if (m_Players[i].getHasFired()) 
      {

         if (m_Bullets[i].AIsInFlight())
         {
              int HeadPosA = m_Bullets[i].getHeadAPos();
              for (int j = HeadPosA; j > m_Bullets[i].getTailAPos(); j--) //10 is the number of pixels behind the tail.
              {
              m_PlayerLEDS[i].setPixelColor(j, m_Bullets[i].getColour(0)); 
              }
              //When the bullet travels at higher speeds, it may happen that it travels more than 1 pixel between one call of Render() and the next. 
              //in this case one or more pixels will be left on, so we will turn off enough LEDs after the tail to make sure we don't leave
              //any behind when the bullet is travelling very fast.
              int TailPosA = m_Bullets[i].getTailAPos();
              for (int j = TailPosA; j > TailPosA - 10; j--) //10 is the number of pixels behind the tail.
              {
                 m_PlayerLEDS[i].setPixelColor(j, 0);
              }
             
         } //end if partA 
          
         if (m_Bullets[i].BIsInFlight())
         {
              for (int k=0; k < m_NumPlayers; k++) //here, numPlayers refers to each LED strip
              {
                if (i == k)
                {
                  //that's the player whose bulletB is in flight, and we don't want to draw bullet B on their own strip
                }
                 else if (!m_Players[k].isExploding())//draw bullet B on every other strip , only if they're not exploding
                 {
                    
                    int HeadPosB = m_Bullets[i].getHeadBPos();
                    for (int j = HeadPosB; j < m_Bullets[i].getTailBPos(); j++) 
                    {
                    m_PlayerLEDS[k].setPixelColor(j, m_Bullets[i].getColour(0)); 
                    }
                    
                    int TailPosB = m_Bullets[i].getTailBPos();
                    for (int j = TailPosB; j < TailPosB + 10; j++) //10 is the number of pixels behind the tail.
                    {
                       m_PlayerLEDS[k].setPixelColor(j, 0);
                    }
                 }   
              }//end for
         } //end if for part B  
    } //end if, to identify which player is associated with the bullet     
  } //end loop through players

  
  //draw explosions
  for (int i = 0; i < m_NumExplosions; i++)
   {
    if (m_Explosions[i].IsActive())
    {
     // Serial.print ("r "); Serial.print (r); Serial.print (" g "); Serial.print (g); Serial.print (" b "); Serial.print (b);
      int strip = m_Explosions[i].GetStrip();
      long colour = m_Explosions[i].GetColour();
      for (int j = m_Explosions[i].GetTail(); j < m_Explosions[i].GetHead(); j++)
      {
         m_PlayerLEDS[strip].setPixelColor(j, colour); 
      }
  
    }// end if explosion is active
   }//end loop through explosions

    
  //the show() function seems to take ages to run, so it causes HUGE flicker in the 7SegDisplay
  //if we refresh the 7 seg display between refreshing every LED strip it reduces the flicker substantially, but still not enough.
  for (int i = 0; i < m_NumPlayers; i++)
  { 
 //   m_ScoreDisplay.refreshDisplay();
  //  m_CurrentRoundDisplay.refreshDisplay();
  //  m_BestRoundsDisplay.refreshDisplay();
    m_PlayerButtonLeds[i].Update();
     //  Serial.println(m_PlayerBoostLeds[i].GetMode());
    m_PlayerBoostLeds[i].Update();
  }
  
  UpdateStrips(t);

  //Send updated score to 4-digit display
  Serial.print('A');
  Serial.println(m_ScoreController.GetCurrentScore());  
  } //end PLAYING mode

}// End RENDER
