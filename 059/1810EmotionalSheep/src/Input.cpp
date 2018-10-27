//
//  Input.cpp
//
//  Created by Carl Turner on 22/10/18.
//
#include "Engine.h"

void Engine::m_Input(unsigned long t)
{
   
    if (m_Transmitter)
    {
         
        m_currentMillis = millis();
        if (m_currentMillis - m_prevMillis >= radioConfig.GetInterval()) 
        {
        m_HumansOrders.throttleSpeed = m_joystick.GetPositionY();
        m_HumansOrders.turnPosition = m_joystick.GetPositionX();
        Serial.println(" ");
            if(m_pRadio->write( &m_HumansOrders, sizeof(m_HumansOrders) ))
            {
            Serial.print("Orders Sent: ");
            Serial.print(m_HumansOrders.throttleSpeed);
            Serial.print(" / ");
            Serial.println(m_HumansOrders.turnPosition);
            }
            else
            {
            Serial.println("Orders not sent ");
            }
        m_prevMillis = millis();
        }
    }
    else 
    {
        if (m_pRadio->available())
        {
            while (m_pRadio->available())
            {
                Serial.println(m_HumansOrders.throttleSpeed);
                Serial.println(m_HumansOrders.turnPosition);

                m_pRadio->read(&m_HumansOrders, sizeof(m_HumansOrders)); //TODO: the read is working . the humansorders aren't updating.
               
                //Has it updated properly?
                Serial.println(m_HumansOrders.throttleSpeed);
                Serial.println(m_HumansOrders.turnPosition);
                Serial.println(" ");
            }
        }
        else
        {
            Serial.println("Radio Not Available");
        }
    }
} //End Input()