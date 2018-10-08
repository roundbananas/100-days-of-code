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
  }

  if((m_mode == Modes::COUNTDOWN))
  {
    Serial.println ("Render - COUNTDOWN");
  }
  
  if(m_mode == Modes::PLAYING)
  {
       //Update Bullets
       //1. loop through each bullet, and identify the player (and therefore led strip) it's associated with. 
            for (int i = 0; i < m_NumPlayers; i++)
            {
              //2. if the bullet i is associated with player j, render the bullet on that player's strip (strip j)
              if (m_Players[i].getHasFired()) 
              {
                  //2. if the bullet partA is in flight, display it on player's own strip. If part B is in flight, display it on all strips except player's strip.
                  //    and if A or B are not in flight, make sure they are rendered black/off.
                  //and don't render part A if the player's bullet is exploding

                 if (m_Bullets[i].BIsInFlight())
                 {
                      for (int k=0; k < m_NumPlayers; k++) //here, numPlayers refers to each LED strip
                      {
                        if (i == k)
                        {
                          //that's the player whose bulletB is in flight, so do nothing
                        }
                         else //draw bullet B on every other strip
                         {
                            m_PlayerLEDS[k].setPixelColor(m_Bullets[i].getHeadBPos(), 255, 0, 0); 
                            m_PlayerLEDS[k].setPixelColor(m_Bullets[i].getTailBPos(), 0);  
                         }   
                      }//end for
                 } //end if for part B  
                  
                  if (!m_Players[i].isExploding() && m_Bullets[i].AIsInFlight())
                  {
                      m_PlayerLEDS[i].setPixelColor(m_Bullets[i].getHeadAPos(), 255, 0, 0); 
                      m_PlayerLEDS[i].setPixelColor(m_Bullets[i].getTailAPos(), 0);
                  } //end if partA     
                  else if (m_Players[i].isExploding()) //clear the strip
                  {  
                    for (int j = 0; j < m_stripLengthArray[i]; j++) m_PlayerLEDS[i].setPixelColor(j, 0);
                  }
            } //end if, to identify which player is associated with the bullet
          } //end loop through players
        
            //draw explosions
            for (int i = 0; i < m_NumExplosions; i++)
             {
              if (m_Explosions[i].IsActive())
              {
               // Serial.print ("r "); Serial.print (r); Serial.print (" g "); Serial.print (g); Serial.print (" b "); Serial.print (b);
                int strip = m_Explosions[i].GetStrip();

              m_PlayerLEDS[strip].setPixelColor(m_Explosions[i].GetHead(), 100, 0, 0); 
              m_PlayerLEDS[strip].setPixelColor(m_Explosions[i].GetTail(), 0, 0, 100); 

//m_Explosions[i].GetColour()
               
                 m_PlayerLEDS[strip].setPixelColor(m_Explosions[i].GetPosition(), 0, 255, 0); 
               
              }// end if explosion is active
             }//end loop through explosions

                 

             for (int i = 0; i < m_NumPlayers; i++)
            {
              m_PlayerLEDS[i].show();
            }
    //UPDATE HUD
       //    m_FramesSinceLastHUDUpdate++;
    //  if(m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
    //  {
       //  m_FramesSinceLastHUDUpdate = 0;
             
  } //end PLAYING mode
  
}




/*
 * Syntax
 * strip.setPixelColor(index, color);
 *   strip.show();                     // Refresh strip

 */
