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
          Serial.println("PLAYING");        
      //loop through each pixel of each bullet that's in use, and update its colour
      //1. loop through each bullet. i relates to bullet number
    
       for (int i=0; i< m_NumBullets; i++)
        {
            for (int j = 0; j < m_NumPlayers; j++)
            {
              int currentPlayer = j;
              if (i == m_Players[j].getBulletIndex() && m_Players[j].getHasFired())
              {
                  //2. if the A is in flight, display it on player's own strip. If B is in flight, display it on all strips except player's strip.
                  if(m_Bullets[i].AIsInFlight())
                  {                        
                        m_PlayerLEDS[j].setPixelColor(m_Bullets[i].getHeadAPos(), 255, 0, 0); 
                        m_PlayerLEDS[j].setPixelColor(m_Bullets[i].getTailAPos(), 0);
                        m_PlayerLEDS[j].show();
                     
                  }
                 if(m_Bullets[i].BIsInFlight())
                 {
                  for (int k=0; k < m_NumPlayers; k++)
                  {
                    if (k == j)
                    {
                      //do nothing
                    }
                    else 
                    {
                      m_PlayerLEDS[k].setPixelColor(m_Bullets[i].getHeadBPos(), 0, 0, 255); 
                      m_PlayerLEDS[k].setPixelColor(m_Bullets[i].getTailBPos(), 0);
                      m_PlayerLEDS[k].show();
                    }
                  }
                 }            
            }
          }
        } //end loop through bullets
     
    //draw explosions
            for (int i = 0; i < m_NumExplosions; i++)
             {
              if (m_Explosions[i].IsActive())
              {
                 Serial.println ("EXPLODING");
                int* colour = m_Explosions[i].GetColour();
                int r = colour[0];
                int g = colour[1];
                int b = colour[2];
                int strip = m_Explosions[i].GetStrip();
                m_PlayerLEDS[strip].setPixelColor(m_Explosions[i].GetPosition(), r, g, b); //this controls one pixel
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
