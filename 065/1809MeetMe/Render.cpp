//
//  Render.cpp
//
//  Created by Carl Turner on 20/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#include "Engine.h"

void Engine::m_Render()
{  
  
  if((m_mode == Modes::IDLE_MODE))
  { 
    
    m_ScoreDisplay.refreshDisplay();
    m_CurrentRoundDisplay.refreshDisplay();
    m_BestRoundsDisplay.refreshDisplay();
    
    if(!m_IdleFlag)
    {
      for (int i = 0; i < m_NumPlayers; i++) 
      {
        for (int j = 0; j < m_stripLengthArray[i]; j++) 
        {
          m_PlayerLEDS[i].setPixelColor(j, 0);
        }
      m_PlayerLEDS[i].show();
      }

        //Write a message to tell players what they can do
        g_TextDisplay.clear();
        g_TextDisplay.setCursor(0,0); //column, row
        g_TextDisplay.print("Press 'New Game'");
        g_TextDisplay.setCursor(0,1); //column, row
        g_TextDisplay.print("   to start");
      
      m_IdleFlag = true;
    }
      
  }

  if((m_mode == Modes::COUNTDOWN))
  {  
      //clear the strips, once
      if (!m_CountdownFlag)
      {
        
        g_TextDisplay.clear();
        delay(500);
    
        for (int i = 0; i < m_NumPlayers; i++)
        { 
            for (int j = m_CountDownDuration; j < m_stripLengthArray[i]; j++) 
                m_PlayerLEDS[i].setPixelColor(j, 0);
          
            m_PlayerLEDS[i].show();
        }
        
        m_CountdownFlag = true;
      }
      
      //update the strips
     for (int i = 0; i < m_NumPlayers; i++)
        { 
            m_PlayerLEDS[i].setPixelColor(m_CountDownRemaining, 0);

            for (int k = 0; k < m_CountDownRemaining; k++)
                m_PlayerLEDS[i].setPixelColor(k, 0xff0000); 
            
            m_PlayerLEDS[i].show();
            m_ScoreDisplay.refreshDisplay();
            m_CurrentRoundDisplay.refreshDisplay();
            m_BestRoundsDisplay.refreshDisplay();
        }

    //update score display
    
    //render the current level
  //   m_CurrentRoundDisplay.SetNumber(m_Level);// Serial.print("Level: "); Serial.print(m_Level);
   //  m_CurrentRoundDisplay.RefreshDisplay();
       
     
     if(m_BestRounds > 0)
     {
   //    m_BestRoundsDisplay.SetNumber(m_BestRounds);
   //    m_BestRoundsDisplay.RefreshDisplay();
     }
   
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
  m_ScoreDisplay.refreshDisplay();
  m_CurrentRoundDisplay.refreshDisplay();
  m_BestRoundsDisplay.refreshDisplay();


  }//end Levelling_Up mode

if((m_mode == Modes::GAME_OVER))
  {  
    m_ScoreDisplay.refreshDisplay();
    m_CurrentRoundDisplay.refreshDisplay();
    m_BestRoundsDisplay.refreshDisplay();

    if(!m_GameOverFlag)
    {
      for (int i = 0; i < m_NumPlayers; i++)
          { 
              for (int j = 0; j < m_stripLengthArray[i]; j++) 
                  m_PlayerLEDS[i].setPixelColor(j, 0);
  
              for (int k = 35; k < 55; k++)
                  m_PlayerLEDS[i].setPixelColor(k, 0xff0000);
            
              m_PlayerLEDS[i].show();

                g_TextDisplay.clear();
                delay(500);
                g_TextDisplay.setCursor(0,0); //column, row
                g_TextDisplay.print("    GAME  ");
                g_TextDisplay.setCursor(0,1); //column, row
                g_TextDisplay.print("   OVER ");
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
    m_PlayerLEDS[i].show(); 
    m_ScoreDisplay.refreshDisplay();
    m_CurrentRoundDisplay.refreshDisplay();
    m_BestRoundsDisplay.refreshDisplay();
  }
  

  } //end PLAYING mode

}// End RENDER
