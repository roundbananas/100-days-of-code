//
//  Engine.h
//
//  Created by Carl Turner on 28/10/18.
//

#ifndef Engine_h
#define Engine_h

// Define structures and classes
#include "RF24.h"

class Engine
{
  private:
    //variables for creating a radio
    uint16_t m_CEpin = 7;
    uint16_t m_CSpin = 8;
    const uint64_t m_pipe = 0xE8E8F0F0E1LL;
    RF24* m_pRadio;

  public:
    Engine(); 
};
#endif