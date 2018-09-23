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
      m_FramesSinceLastHUDUpdate++;
             if(m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
             {
       for (int i = 0; i < m_NumPlayers; i++)
        {
          //2. if the bullet is inflight, update the pixel colours on the strip, from the head to the tail. j relates to bullet element/pixel
          if(m_Bullets[m_Players[i].getBulletIndex()].AIsInFlight())
          {
                  Serial.println ("Render - setting pixel colour");

            
                 for (int j = m_Bullets[i].getHeadAPos(); j > (m_Bullets[i].getHeadAPos() - m_Bullets[i].getTailAPos()); j--)
                 {
                    m_PlayerLEDS[i].setPixelColor(j, m_Bullets[i].getColourR(j), m_Bullets[i].getColourG(j), m_Bullets[i].getColourB(j));
                 }
              
                  if(m_Bullets[m_Players[i].getBulletIndex()].BIsInFlight())
                  {
                     for (int j = m_Bullets[i].getHeadAPos(); j > (m_Bullets[i].getHeadAPos() - m_Bullets[i].getTailAPos()); j--)
                     {
                        m_PlayerLEDS[i].setPixelColor(j, m_Bullets[i].getColourR(j), m_Bullets[i].getColourG(j), m_Bullets[i].getColourB(j));
                     }
                  }
                m_FramesSinceLastHUDUpdate = 0;
            }
            Serial.println ("Render - showing");
        m_PlayerLEDS[i].show();
        }
    }
}
}

/*
 * Syntax
 * strip.setPixelColor(index, color);
 *   strip.show();                     // Refresh strip

 */
