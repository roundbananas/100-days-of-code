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
      Serial.println ("Render - PLAYING");         
      //loop through each pixel of each bullet that's in use, and update its colour
      //1. loop through each bullet. i relates to bullet number
    //  m_FramesSinceLastHUDUpdate++;
    // if(m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
     //{
       for (int i=0; i< m_NumBullets; i++)
        {
            for (int j = 0; j < m_NumPlayers; j++)
            {
              if (i == m_Players[j].getBulletIndex() && m_Players[j].getHasFired())
              {
                  //2. if the bullet is inflight, update the pixel colours on the strip, from the head to the tail. j relates to bullet element/pixel
                  if(m_Bullets[i].AIsInFlight() || m_Bullets[i].BIsInFlight())
                  {
                    // Serial.println ("Render - setting pixel colour");
                        
                        m_PlayerLEDS[j].setPixelColor(m_Bullets[i].getHeadAPos(), 255, 0, 0); 
                        m_PlayerLEDS[j].setPixelColor(m_Bullets[i].getTailAPos(), 0);
                         m_PlayerLEDS[j].setPixelColor(m_Bullets[i].getHeadBPos(), 0, 0, 255); 
                        m_PlayerLEDS[j].setPixelColor(m_Bullets[i].getTailBPos(), 0);
                        m_PlayerLEDS[j].show();
                     
                     /* 
                     if(m_Bullets[index].BIsInFlight())
                     {
                        m_PlayerLEDS[i].setPixelColor(m_Bullets[index].getHeadBPos(), 0xFF0000); 
                        m_PlayerLEDS[i].setPixelColor(m_Bullets[index].getTailBPos(), 0);
                        m_PlayerLEDS[i].show();
                       
                     }
                     */
                   //  m_FramesSinceLastHUDUpdate = 0;
                  }          
            }
          }
        }
  }
  
}




/*
 * Syntax
 * strip.setPixelColor(index, color);
 *   strip.show();                     // Refresh strip

 */
