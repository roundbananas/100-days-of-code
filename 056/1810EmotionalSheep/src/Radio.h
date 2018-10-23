//
//  Radio.h
//
//  Created by Carl Turner on 22/10/18.
//
/*Radio pin assignments
 * (different for Arduino Uno/Mega)
 * Uno    Mega  Radio Pin
 * 9      40    CE
 * 10     53    SCN
 * 11     51    MO
 * 12     50    MI
 * 13     52    SCK
 * 
 * Connect the radio to 3.3V, not 5V.
 */ 

#ifndef Radio_h
#define Radio_h

#include "Arduino.h"
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

class Radio
{
  private:
  int m_Msg[1]; //for debugging
  const uint64_t m_Pipe;

public:
    void spawn(int board, int type); //board: 0 = Arduino Uno, 1 = Arduino mega. type: 0 = TX, 1 = RX.
};

#endif

