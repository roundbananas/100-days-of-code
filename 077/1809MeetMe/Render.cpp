//
//  Render.cpp
//
//  Created by Carl Turner on 11/12/18.
//
// This code runs on Mega.
// Send data via serial to ESP module, which will update the pixel colours and refresh the strips

#include "Engine.h"

void Engine::m_Render(unsigned long t)
{
	if((m_mode == Modes::IDLE_MODE))
  	{
      //Refresh 7 Segment displays
      m_ScoreDisplay.refreshDisplay();
      m_CurrentRoundDisplay.refreshDisplay();
      m_BestRoundsDisplay.refreshDisplay();

      //flash New Game button light
      m_NewGameButtonLED.Update();

      if(!m_IdleFlag)
      {
      	/** Clearing of LED strips handled by ESP **/

	      for (int i = 0; i < 3; i++)
	      {
	        m_PlayerButtonLeds[i].Update();
	        m_PlayerBoostLeds[i].Update();
	      }
	      
	      m_IdleFlag = true;
	  } //End if !m_IdleFlag
	} //End Idle Mode

	if((m_mode == Modes::COUNTDOWN))
  	{        
      if (!m_CountdownFlag)
      {
       	/** Clearing of LED strips handled by ESP **/
        
        //turn off New Game light and boost leds
        m_NewGameButtonLED.Update();
        
        for (int i = 0; i < m_NumPlayers; i++)
        {
          m_PlayerBoostLeds[i].Update();
        }
        m_CountdownFlag = true;
      } //End if !m_CountdownFlag
      
    /** Updating of LED strips handled by ESP **/

    //flash player lights
    for (int i = 0; i < m_NumPlayers; i++)
    {
      m_PlayerButtonLeds[i].Update();
    }
       
    m_ScoreDisplay.refreshDisplay();
    m_CurrentRoundDisplay.refreshDisplay();
    m_BestRoundsDisplay.refreshDisplay();
  } //End Countdown Mode

/*
* LEVELLING UP MODE
*/
  if(m_mode == Modes::LEVELLING_UP)
  {
   	 //Update the score display  
	  m_ScoreDisplay.refreshDisplay();
	  m_CurrentRoundDisplay.refreshDisplay();
	  m_BestRoundsDisplay.refreshDisplay();
  }//end Levelling_Up mode

/*
 * GAME OVER MODE
*/
  if((m_mode == Modes::GAME_OVER))
  {  
    m_ScoreDisplay.refreshDisplay();
    m_CurrentRoundDisplay.refreshDisplay();
    m_BestRoundsDisplay.refreshDisplay();

    /** Updating of LED strips handled by ESP **/
    
    //flash New Game button light
    m_NewGameButtonLED.Update();

    if(!m_GameOverFlag)
    {
      
          /** Updating of LED strips handled by ESP **/

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
		m_PlayerButtonLeds[i].Update();
    	m_PlayerBoostLeds[i].Update();
  	}
  
    /** Updating of LED strips handled by ESP **/
    
    m_ScoreDisplay.refreshDisplay();
    m_CurrentRoundDisplay.refreshDisplay();
    m_BestRoundsDisplay.refreshDisplay();
  } //end PLAYING mode

}// End Render()
