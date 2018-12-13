//
//  Engine.cpp
//
//  Created by Carl Turner on 18/9/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#include "ESP_Engine.h"

ESP_Engine::ESP_Engine()
{
  // current state-machine state. These help us manage incoming data.
  m_mode = Modes::IDLE_MODE;
  m_stripRef = StripRefs::NONE; 
  m_stripCharacteristics = StripCharacteristics::_NONE;
  
  m_ColorPlayer1 = 0xff0000; //red
  m_ColorPlayer2 = 0x00ff00; //green
  m_ColorPlayer3 = 0x2f7fff; //blue
  m_ColorExplosion = 0xff7e22; //orange

  // turn all LEDS on each strip off
  for (int i = 0; i < m_NumPlayers; i++)
  {
    pinMode(m_stripDataPinArray[i], OUTPUT);
    pinMode(m_stripClockPinArray[i], OUTPUT);
    m_LedStrips[i].begin();
    m_LedStrips[i].show();
  }
}

void ESP_Engine::runEngine()
{

	while(true)
	  {
	  	m_Input(); 
	    m_Update();
	    m_Render(); 
	  }
}

void ESP_Engine::processIncomingByte(const byte c)
{
if (isdigit (c))
  {
    m_currentValue *= 10;
    m_currentValue += c - '0';
  }  // end of digit
  
  else
  {
    // The end of the number signals a state or SubState change
    assignCurrentValueToArray();

    // set the new state or subState, if we recognize it
    switch (c)
    {
      //Game modes
      case 'I':
        m_mode = Modes::IDLE_MODE;
        break;
      case 'C':
        m_mode = Modes::COUNTDOWN;
        break;
      case 'P':
        m_mode = Modes::PLAYING;
        break;
      case 'L':
        m_mode = Modes::LEVELLING_UP;
        break;
      case 'G':
        m_mode = Modes::GAME_OVER;
        break;

      //strips
      case 'X':
        m_stripRef = StripRefs::GOT_X;
        break;
      case 'Y':
        m_stripRef = StripRefs::GOT_Y;
        break;
      case 'Z':
        m_stripRef = StripRefs::GOT_Z;
        break;

      //strip states
      case 'Q':
        m_stripCharacteristics = StripCharacteristics::K_BULLETA_ON;
        break;
      case 'R':
        m_stripCharacteristics = StripCharacteristics::L_BULLETB_ON;
        break;  
      case 'S':
        m_stripCharacteristics = StripCharacteristics::M_EXPLOSION_ON;
        break; 
      case 'A':
        m_stripCharacteristics = StripCharacteristics::A_BULLETA_HEAD;
        break;  
      case 'a':
        m_stripCharacteristics = StripCharacteristics::A_BULLETA_TAIL;
        break;  
      case 'B':
        m_stripCharacteristics = StripCharacteristics::B_BULLETB_HEAD;
        break;  
      case 'b':
        m_stripCharacteristics = StripCharacteristics::B_BULLETB_TAIL;
        break;   
      case 'E':
        m_stripCharacteristics = StripCharacteristics::E_EXPLOSION_HEAD;
        break;  
      case 'e':
        m_stripCharacteristics = StripCharacteristics::E_EXPLOSION_TAIL;
        break;   
        
      default:
        m_mode = Modes::LEVELLING_UP; //just using LEVELLING_UP because nothing happens on ESP in this mode
        m_stripRef = StripRefs::NONE;
        m_stripCharacteristics = StripCharacteristics::_NONE;
        break;
    }  // end of switch on incoming byte
  } // end of not digit   
} // end of processIncomingByte()

void ESP_Engine::assignCurrentValueToArray()
{
  switch (m_stripRef)
    {
    case StripRefs::GOT_X:
      processStrip (0, m_currentValue); //for strip 1
      break;
    case StripRefs::GOT_Y:
      processStrip (1, m_currentValue); //for strip 2
      break;
    case StripRefs::GOT_Z:
      processStrip (2, m_currentValue); //for strip 3
      break;
    }  // end of switch  

    m_currentValue = 0; 
}  // end of assignCurrentValueToArray()

void ESP_Engine::processStrip (int strip, const unsigned int value)
{
// Assign data to array elements for relevant strip 
  switch(m_stripCharacteristics)
  {
    case StripCharacteristics::K_BULLETA_ON:
      m_DataReceived[strip][0] = value;
      break;
     case StripCharacteristics::L_BULLETB_ON:
      m_DataReceived[strip][1] = value;
      break;
    case StripCharacteristics::M_EXPLOSION_ON:
      m_DataReceived[strip][2] = value;
      break;
    case StripCharacteristics::A_BULLETA_HEAD:
      m_DataReceived[strip][3] = value;
      break;
    case StripCharacteristics::A_BULLETA_TAIL:
      m_DataReceived[strip][4] = value;
      break;
   case StripCharacteristics::B_BULLETB_HEAD:
      m_DataReceived[strip][5] = value;
      break;
    case StripCharacteristics::B_BULLETB_TAIL:
      m_DataReceived[strip][6] = value;
      break;
    case StripCharacteristics::E_EXPLOSION_HEAD:
      m_DataReceived[strip][7] = value;
      break;
    case StripCharacteristics::E_EXPLOSION_TAIL:
      m_DataReceived[strip][8] = value;
      break; 
  }// end switch 
} // end of processStrip
