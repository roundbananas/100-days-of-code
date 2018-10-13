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
    Serial.println ("Render - IDLE_MODE");
      
      for (int i = 0; i < m_NumPlayers; i++) 
      {
        for (int j = 0; j < m_stripLengthArray[i]; j++) 
        {
          m_PlayerLEDS[i].setPixelColor(j, 0);
        }
      m_PlayerLEDS[i].show();
      }
  }

  if((m_mode == Modes::COUNTDOWN))
  {
    Serial.println ("Render - COUNTDOWN");
    //Clear the strips
     for (int i = 0; i < m_NumPlayers; i++)
        { 
            for (int j = m_CountDownRemaining; j < m_stripLengthArray[i]; j++) 
                m_PlayerLEDS[i].setPixelColor(j, 0);

            for (int k = 0; k < m_CountDownRemaining; k++)
                m_PlayerLEDS[i].setPixelColor(k, 0xff0000);
          
            m_PlayerLEDS[i].show();
        }

    //render the current level
    if (m_Level < 10)
    {
      m_LevelDisplay1.SetNumber(0);
      m_LevelDisplay2.SetNumber(secondDigit(m_Level));
      Serial.print("Level: "); Serial.print(0); Serial.println(secondDigit(m_Level));
    }
    else 
    {
       m_LevelDisplay1.SetNumber(firstDigit(m_Level));
       m_LevelDisplay2.SetNumber(secondDigit(m_Level));
       Serial.print("Level: "); Serial.print(firstDigit(m_Level)); Serial.println(secondDigit(m_Level));
    }
   
    m_LevelDisplay1.RefreshDisplay();
    m_LevelDisplay2.RefreshDisplay();
   
  }

   /*
   * LEVELLING UP MODE
   */
  if(m_mode == Modes::LEVELLING_UP)
  {
        Serial.println ("Render - LEVELLING_UP_MODE");

    //Update the score display
      int currentScore = m_ScoreController.GetCurrentScore();
      for (int i = 0; i <= currentScore; i++)
      {
        m_ScoreLEDS.setPixelColor(i, m_ScoreController.GetColour());
      }
      for (int i = currentScore + 1; i <= currentScore + m_ScoreController.GetScoreAdded(); i++)
      {
        if(!m_ScoreController.GetOn())
        {
          m_ScoreLEDS.setPixelColor(i, 0);
        }
        else
        {
          m_ScoreLEDS.setPixelColor(i, m_ScoreController.GetColour());
        }
      }         

    m_ScoreLEDS.show();

  }//end Levelling_Up mode

  /*
   * PLAYING MODE
   */
  
  if(m_mode == Modes::PLAYING)
  {
    Serial.println ("Render - PLAYING_MODE");
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
              m_PlayerLEDS[i].setPixelColor(m_Bullets[i].getHeadAPos(), m_Bullets[i].getColour(0)); 
              m_PlayerLEDS[i].setPixelColor(m_Bullets[i].getTailAPos(), 0);
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
                    m_PlayerLEDS[k].setPixelColor(m_Bullets[i].getHeadBPos(), m_Bullets[i].getColour(0)); 
                    m_PlayerLEDS[k].setPixelColor(m_Bullets[i].getTailBPos(), 0);  
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

   for (int i = 0; i < m_NumPlayers; i++) m_PlayerLEDS[i].show();
             
    //UPDATE HUD
       //    m_FramesSinceLastHUDUpdate++;
    //  if(m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
    //  {
       //  m_FramesSinceLastHUDUpdate = 0;

    
  } //end PLAYING mode

  
    
}// End RENDER




/*
 * Syntax
 * strip.setPixelColor(index, color);
 *   strip.show();                     // Refresh strip

 */
