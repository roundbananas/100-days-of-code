//
//  Input.cpp
//
//  Created by Carl Turner on 20/9/18.
//
#include "ESP_Engine.h"

void ESP_Engine::m_Input()
{
	while (Serial.available ())
    	processIncomingByte (Serial.read ());
}
