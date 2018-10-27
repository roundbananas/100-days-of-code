//
//  Engine.cpp
//
//  Created by Carl Turner on 28/10/18.
//

#include "Engine.h"

Engine::Engine()
{
    //setup radio
    m_pRadio = new RF24(m_CEpin, m_CSpin);

    m_pRadio->begin();
    m_pRadio->openWritingPipe(m_pipe);
}

