
//
//  SendDataToESP.cpp
//
//  Created by Carl Turner on 12/12/18.
//

/*
 * CODES, FOR REFERENCE
 * //Mode Codes
	I, //IDLE_MODE,
    C, //COUNTDOWN,
    P, //PLAYING,
    L, //LEVELLING_UP,
    G, //GAME_OVER

 	//Strip Codes
 	X, //Strip 1
 	Y, //Strip 2
 	Z, //Strip 3
  
 	//Sub state Codes 		array column index (see below)	where do we get the data from?
 	Q, // Bullet A is on 	1								m_Bullets[i].AIsInFlight()
 	R, // Bullet B is on 	2								m_Bullets[i].BIsInFlight()
 	S, // Explosion is on 	3								m_Explosions[i].IsActive() & m_Explosions[i].GetStrip()

 	A, // Bullet A head 	4								m_Bullets[i].getHeadAPos()
 	a, // Bullet A tail 	5								m_Bullets[i].getTailAPos()

 	B, // Bullet B head 	6								m_Bullets[i].getHeadBPos()
 	b, // Bullet B tail 	7								m_Bullets[i].getTailBPos()

 	E, // Explosion head 	8								m_Explosions[i].GetHead()
 	e  // Explosion tail 	9								m_Explosions[i].GetTail()
 */

/*
 * ARRAY ELEMENTS, FOR REFERENCE
 	  * Array index   Relates to      Possible values
	  * [i][0]		  Game Mode       0, 1, 2, 3, 4 (for IDLE, COUNTDOWN, PLAYING, LEVELLING_UP, GAME_OVER)
	  * [i][1]        BulletA on/off  0, 1
	  * [i][2]        BulletB on/off  0, 1
	  * [i][3]        Expl'n on/off   0, 1
	  * [i][4]        BulletAHead     0 - 90 (ie a location on a strip of, say, length 90)
	  * [i][5]        BulletATail     0 - 90 
	  * [i][6]        BulletBHead     0 - 90 
	  * [i][7]        BulletBTail     0 - 90 
	  * [i][8]        Expl'nHead      0 - 90 
	  * [i][9]        Expl'nTail      0 - 90 
*/

#include "Engine.h"

void Engine::m_SendDataToESP()
{
	//Send the mode
	switch (m_mode)
	{
    	case Modes::IDLE_MODE:
    		Serial.print('I');
    		break;
    	case Modes::COUNTDOWN:
    		Serial.print('C');
    		break;
    	case Modes::PLAYING:
    		Serial.print('P');
    		break;
    	case Modes::LEVELLING_UP:
    		Serial.print('L');
    		break;
    	case Modes::GAME_OVER:
    		Serial.print('G');
    		break;
	} // End send mode switch

	//if Idle Mode, ESP will handle clearing the strips based on the mode
	if((m_mode == Modes::IDLE_MODE))
	{
		//do nothing
	}

	if(m_mode == Modes::LEVELLING_UP)
	{
		//do nothing
	}// end LEVELLING_UP mode
	
	//if Countdown mode, ESP will handle the countdown, 
	//based on the time countdown mode startedAt
	if(m_mode == Modes::COUNTDOWN)
	{
		//send it for each strip, just to make sure.
	    for (int i = 0; i < m_NumPlayers; i++)
		{
			switch (i)
			{
				case 0: //strip 1
				Serial.print('X'); //Tell ESP we're sending data for strip 1				
				break;
				case 1: //strip 2
				Serial.print('Y'); //Tell ESP we're sending data for strip 1				
				break;
				case 2: //strip 3
				Serial.print('Z'); //Tell ESP we're sending data for strip 1				
				break;
			}
			
		Serial.print('A'); //Tell ESP we're sending data for BulletA head
		Serial.print(m_DataToSend[i][4]); //we're using the array element for BulletAHead to send countdownRemaining (rather than create a whole new array element that uses more memory)
		}
	} //end COUNTDOWN mode

	//if Playing mode, send all the data to ESP
	if(m_mode == Modes::PLAYING)
	{
		//send the data for each strip in turn
	    for (int i = 0; i < m_NumPlayers; i++)
		{
			/*  ?? Do we need to prefix every piece of data with the
				strip identifier (X, Y or Z), to avoid ESP 'missing' the 
				strip identifier, and assigning data to wrong strip. 
				Or will the data just stay in the buffer, in order and be 
				read in order?? Can we guarantee that?*/
			
			//prefix each array column sent with the strip identifier
			switch (i)
			{
				case 0: //strip 1
				Serial.print('X'); //Tell ESP we're sending data for strip 1				
				break;
				case 1: //strip 2
				Serial.print('Y'); //Tell ESP we're sending data for strip 1				
				break;
				case 2: //strip 3
				Serial.print('Z'); //Tell ESP we're sending data for strip 1				
				break;
			}
			
			//Now send the rest of the current strip's data
			Serial.print('Q'); //Tell ESP we're sending data for BulletA isOn/off
			Serial.print(m_DataToSend[i][1]);
			Serial.print('R'); //...data for BulletB isOn/off
			Serial.print(m_DataToSend[i][2]);
			Serial.print('S'); //...data for Explosion isOn/off
			Serial.print(m_DataToSend[i][3]);

			Serial.print('A'); //Tell ESP we're sending data for BulletA head
			Serial.print(m_DataToSend[i][4]);
			Serial.print('a'); //...data for BulletA tail
			Serial.print(m_DataToSend[i][5]);

			Serial.print('B'); //Tell ESP we're sending data for BulletB head
			Serial.print(m_DataToSend[i][6]);
			Serial.print('b'); //...data for BulletB tail
			Serial.print(m_DataToSend[i][7]);
			
			Serial.print('E'); //Tell ESP we're sending data for Explosion head
			Serial.print(m_DataToSend[i][8]);
			Serial.print('e'); //...data for Explosion tail
			Serial.print(m_DataToSend[i][9]);
		} //End sending data for each strip			
	} //End if Playing Mode
	
	//After we've sent it, reset the array to 0
	for (int i = 0; i < m_NumPlayers; i++)
	{
		for (int j = 0; j < 10; j++)
			m_DataToSend[i][j] = 0;
	} //end reset array

} //End SendDataToESP()
