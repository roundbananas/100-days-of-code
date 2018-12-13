//
//  Update.cpp
//
//  Created by Carl Turner on 20/9/18.
//
#include "ESP_Engine.h"

void ESP_Engine::m_Update()
{
	//set pixel colours using data in array
	if((m_mode == Modes::IDLE_MODE))
  	{
  		if(!m_IdleFlag)
      {	
		//turn all strips off.
		for (int i = 0; i < m_NumPlayers; i++) 
		{
			for (int j = 0; j < m_stripLengthArray[i]; j++) 
			{
			m_LedStrips[i].setPixelColor(j, 0);
			}
		}
		m_IdleFlag = true;
		m_GameOverFlag = false;
	  } //End if !m_IdleFlag
  	} //End Idle Mode

  	if((m_mode == Modes::COUNTDOWN))
  	{        
      if (!m_CountdownFlag)
      {
      	//strips are already cleared, during IDLE_MODE
        m_CountdownFlag = true;
        m_IdleFlag = false;
	  } //End if !m_CountdownFlag

	  //Update the strips during countdown
	  //We're referring to the 'BulletA head position' for this, 
	  // (rather than add an extra element to the m_DataReceived[][] array, 
	  // just for countdownRemaining).
	  //The timing and counting down are handled by the Mega.
	  for (int i = 0; i < m_NumPlayers; i++)
      { 
        m_LedStrips[i].setPixelColor(m_DataReceived[i][4], 0); //turn off the last pixel

        for (int k = 0; k < m_DataReceived[i][4]; k++)
            m_LedStrips[i].setPixelColor(k, 0xff0000); //set colour of pixels to indicate countdown remaining
      }
    } //End Countdown mode

    if(m_mode == Modes::LEVELLING_UP)
	{
		//do nothing
	}// end LEVELLING_UP mode

/*
 * GAME OVER MODE
 */
  if((m_mode == Modes::GAME_OVER))
  {  
    if(!m_GameOverFlag)
    {
      for (int i = 0; i < m_NumPlayers; i++)
      { 
          for (int j = 0; j < m_stripLengthArray[i]; j++) 
              m_LedStrips[i].setPixelColor(j, 0);

          for (int k = 45; k < 50; k++) //Make this a cooler animation when I get a chance
              m_LedStrips[i].setPixelColor(k, 0xff0000);
      }
      m_GameOverFlag = true;

	  m_PlayingFlag = false;
    }      
  } //End Game Over Mode

/*
* PLAYING MODE
*/
  if(m_mode == Modes::PLAYING)
  {
  	if(!m_PlayingFlag)
    {
    	//reset all strips at the start of PLAYING mode.
		for (int i = 0; i < m_NumPlayers; i++) 
		{
			for (int j = 0; j < m_stripLengthArray[i]; j++) 
			{
			m_LedStrips[i].setPixelColor(j, 0);
			}
		}
    	m_PlayingFlag = true;

    	m_CountdownFlag = false;
    } //End flag flipping
    else // update pixel colours during PLAYING mode, with values from DataReceived[][]
    {
    	for (int i = 0; i < m_NumPlayers; i++)
		{
			//NOTE:
			//the bullet[i] positions in the array relate to player[i] 
			//- bulletA for player[i] will always be on strip[i]
			//- bulletB for player[i] will can be on every other strip EXCEPT strip[i]
			//
			//The Mega has already taken care of working out which explosion 
			//is on which strip. So, in the code below the explosion[i] will be on strip[i]

			//So, do explosions first. If there's an explosion on 
			//strip i, we don't render bullets on that strip.

			if(m_DataReceived[i][3] == 1) //there's an explosion on strip i
			{
				//clear the strip
				for (int j = 0; j < m_stripLengthArray[i]; j++) m_LedStrips[i].setPixelColor(j, 0);

				//set exploding pixels
				for (int j = m_DataReceived[i][9]; j < m_DataReceived[i][8]; j++) //from tail to head
				m_LedStrips[i].setPixelColor(j, m_ColorExplosion);
			} //end updating explosions

			else //no explosion on this strip, let's update bullets
			{
				if(m_DataReceived[i][1] == 1) //bulletA is on for player i on strip i 
				{	
					//set pixels for the bullet position
					for (int j = m_DataReceived[i][4]; j > m_DataReceived[i][5]; j--) //from head to tail
						m_LedStrips[i].setPixelColor(j, m_PlayerColors[i]);
					//clean up some pixels behind the bullet, just to make sure
					//if bullet travels more than 1 pixel per loop that pixel will be left on.
					for (int j = m_DataReceived[i][5]; j > m_DataReceived[i][5] - 5; j--) //from tail to a few behind the tail
						m_LedStrips[i].setPixelColor(j, 0);
				} //end updating BulletA

				if(m_DataReceived[i][2] == 1) //bulletB is on for player i. Set pixels on every strip OTHER than strip i.
				{
					for (int k=0; k < m_NumPlayers; k++) //here, numPlayers refers to each LED strip
              		{
		                if (i == k)
		                {
		                  //that's the player whose bulletB is in flight, and we don't want to draw bullet B on their own strip
						}
						else
						{
							//set pixels for the bullet position
							for (int j = m_DataReceived[i][6]; j < m_DataReceived[i][7]; j++) //from head to tail
								m_LedStrips[k].setPixelColor(j, m_PlayerColors[i]);
							//clean up some pixels behind the bullet, just to make sure.
							for (int j = m_DataReceived[i][7]; j < m_DataReceived[i][7] + 5; j++) //from tail to a few behind the tail
								m_LedStrips[k].setPixelColor(j, 0);
						}

					}
				} //end updating BulletB
			} //end updating bullets

		} //end for loop through players
    } //end update pixel colours during PLAYING mode

  } //End Playing Mode
} //end Update()
