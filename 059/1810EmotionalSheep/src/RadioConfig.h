/*
 * 
 * Carl Turner 27 October 2018
 * roundbananas.com
 * 
 */

/*Radio pin assignments
 * the way the radio libaries are setup means you need to connect the following way (different for Arduino Uno/Mega)
 * Uno    Mega  Radio Pin
 * 7      40    CE
 * 8      53    SCN    **CHECK CONNECTIONS ARE GOOD, NOT DODGY JUMPERS***
 * 11     51    MO
 * 12     50    MI
 * 13     52    SCK
 * 
 * Connect the radio to 3.3V, not 5V.
 */ 

#ifndef RADIOCONFIG_H
#define RADIOCONFIG_H

 /*-------------------IMPORT LIBRARIES-------------------*/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

class RadioConfig
{
    private:
        const uint64_t m_pipe = 0xE8E8F0F0E1LL; //can have multiple pipes, but the message must be sent from same pipe that it's received on. ie pipe value must be same for TX and RX
        unsigned long m_txIntervalMillis = 1000; // transmit at specified intervals
        
    public:
        uint64_t GetPipe();
        unsigned long GetInterval();
};
#endif