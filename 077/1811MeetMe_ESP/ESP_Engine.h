//
//  Engine.h
//
//  Created by Carl Turner on 18/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!
 /*******
 * NOTE for NodeMCU or WEMOS mini ESP8266 module.
 * Pin assignments are confusing.
 * Pin label on board - Pin number you need to give assign it in software
 * TX (10)  - 1  
 * RX (9)   - 3
 * 
 * D0       - 16
 * D1       - 5
 * D2       - 4
 * D3       - 0              
 * D4       - 2
 * 
 * D5       - 14
 * D6       - 12
 * D7       - 13
 * D8       - 15
 * 
 * A0       - 0 (analog)
 ******/
  /*** CONNECTIONS ****/
 /* Mega pin     Logic Level Shifter    ESP8266 (Wemos mini)
  * TX (1)       HV-TX0       LV-TXI    RX
  * RX (0)       -            -         TX
  */

#ifndef ESP_Engine_h
#define ESP_Engine_h

#include "Modes.h"
#include "StripRefs.h"
#include "StripCharacteristics.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>

class ESP_Engine
{
  private:
    static const int m_NumPlayers = 3;
    
    //setup LEDs for players/bullets
    float m_stripLengthArray[m_NumPlayers] = {90.0f, 90.0f, 90.0f}; //float because bullet position is calculated as float 
    int m_stripDataPinArray[m_NumPlayers] = {4, 2, 12};
    int m_stripClockPinArray[m_NumPlayers] = {5, 0, 14};

    Adafruit_DotStar m_LedStrip1 = Adafruit_DotStar(m_stripLengthArray[0], m_stripDataPinArray[0], m_stripClockPinArray[0], DOTSTAR_BGR);
    Adafruit_DotStar m_LedStrip2 = Adafruit_DotStar(m_stripLengthArray[1], m_stripDataPinArray[1], m_stripClockPinArray[1], DOTSTAR_BGR);
    Adafruit_DotStar m_LedStrip3 = Adafruit_DotStar(m_stripLengthArray[2], m_stripDataPinArray[2], m_stripClockPinArray[2], DOTSTAR_BGR);

    Adafruit_DotStar m_LedStrips[m_NumPlayers] = {m_LedStrip1, m_LedStrip2, m_LedStrip3};

    //What colours do we use to represent each player's bullet and the explosions
    uint32_t m_ColorPlayer1, m_ColorPlayer2, m_ColorPlayer3, m_ColorExplosion;  
    uint32_t m_PlayerColors[3] = {m_ColorPlayer1, m_ColorPlayer2, m_ColorPlayer3};
    /*
     * How will we manage serial data we receive?
     */
    //Where will we put the data we receive from Mega?
    byte m_DataReceived[m_NumPlayers][10] = {}; //initialise to 0

    // current partial number
    unsigned int m_currentValue;



	Modes m_mode;
	unsigned long m_modeStartedAt = 0;

  StripRefs m_stripRef;
  StripCharacteristics m_stripCharacteristics;

  bool m_IdleFlag = false;
  bool m_CountdownFlag = false;
  bool m_PlayingFlag = false;
  bool m_LevelUpFlag = false;
  bool m_GameOverFlag = false;

	unsigned long m_countdownStartedAt = 0;
    
	  void m_Input();
    void m_Update();
    void m_Render();

  public:
  	ESP_Engine();
    void runEngine();
  	void processIncomingByte(const byte c);
	  void assignCurrentValueToArray();
    void processStrip (int strip, const unsigned int value);
};
#endif
	
