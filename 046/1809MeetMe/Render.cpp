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
    // Serial.println("PLAYING");        
       //Update Bullets
       //1. loop through each bullet, and identify the player (and therefore led strip) it's associated with. 
       for (int i=0; i< m_NumBullets; i++)
        {
            for (int j = 0; j < m_NumPlayers; j++)
            {
              /*
               * For each strip (which has same index number as the player index):
               *  - if there's an explosion on the strip, render the explosion and nothing else.
               *  - otherwise 
               *      - render part A of the player's bullet (if in flight), 
               *      - AND render part B of another player's bullet (if in flight)
               */
              //2. if the bullet i is associated with player j, render the bullet on that player's strip (strip j)
              if (m_Players[j].getHasFired() && (i == m_Players[j].getBulletIndex())) //THIS WON'T WORK IF PLAYER HASN'T FIRED  
              {
                  //2. if the bullet partA is in flight, display it on player's own strip. If part B is in flight, display it on all strips except player's strip.
                  //    and if A or B are not in flight, make sure they are rendered black/off.
                  //and don't render part A if the player's bullet is exploding
                  
                  if (!m_Players[j].isExploding() && m_Bullets[i].AIsInFlight())
                  {
                      m_PlayerLEDS[j].setPixelColor(m_Bullets[i].getHeadAPos(), 255, 0, 0); 
                      m_PlayerLEDS[j].setPixelColor(m_Bullets[i].getTailAPos(), 0);
                      m_PlayerLEDS[j].show();
                      
                  } //end if partA
                  else //exploding. don't render their partA
                  {
                    for (int m = 0; m < m_stripLengthArray[j]; m++)
                             {
                                m_PlayerLEDS[j].setPixelColor(m, 0);
                                m_PlayerLEDS[j].show();
                             }
                  }

                 if (m_Bullets[i].BIsInFlight()) //for player j
                 {
                      for (int k=0; k < m_NumPlayers; k++) //here, numPlayers refers to each LED strip
                      {
                        if (k == j)
                        {
                          //do nothing
                        }
                        else for (int i = 0; i < m_NumExplosions; i++)
                        {
                           if (m_Explosions[i].IsActive() && k == m_Explosions[i].GetStrip())
                           {
                             //there's an explosion on this player's strip, so don't render bullet partB on this strip
                             for (int m = 0; m < m_stripLengthArray[k]; m++)
                             {
                                m_PlayerLEDS[k].setPixelColor(m, 0);
                                m_PlayerLEDS[k].show();
                             }
                             //and don't render player j's part A
                           }
                           else 
                           {
                              m_PlayerLEDS[k].setPixelColor(m_Bullets[i].getHeadBPos(), 0, 0, 255); 
                              m_PlayerLEDS[k].setPixelColor(m_Bullets[i].getTailBPos(), 0);
                              m_PlayerLEDS[k].show();
                           }
                        }//end else for
                      }//end for
                 } //end if for part B       
            } //end if, to identify which player is associated with the bullet
          } //end loop through players
        } //end loop through bullets
     
    //draw explosions
            for (int i = 0; i < m_NumExplosions; i++)
             {
              if (m_Explosions[i].IsActive())
              {
                 
               // int* colour = m_Explosions[i].GetColour();
                //int r = colour[0];
               // int g = colour[1];
               // int b = colour[2];
               // Serial.print ("r "); Serial.print (r); Serial.print (" g "); Serial.print (g); Serial.print (" b "); Serial.print (b);
                int strip = m_Explosions[i].GetStrip();
                m_PlayerLEDS[strip].setPixelColor(m_Explosions[i].GetPosition(), 0, 255, 0); //this controls one pixel
                //add extra lines for multiple pixels. Maybe I need a loop here if explosion position is held as an array.
                m_PlayerLEDS[strip].show();
              }
             }//end loop through explosions


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
