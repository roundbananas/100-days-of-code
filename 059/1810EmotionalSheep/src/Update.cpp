//
//  Update.cpp
//
//  Created by Carl Turner on 22/10/18.
//
#include "Engine.h"

void Engine::m_Update(unsigned long t)
{
        if (m_Transmitter)
        {
            
        }
        else
        {
            m_Motor.Update(m_HumansOrders.throttleSpeed);
            m_Servo.Update(m_HumansOrders.turnPosition);
        }
     
} //end update()