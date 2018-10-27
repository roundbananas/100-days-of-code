/*
 * Radio.cpp
 * 
 * Carl Turner 27 October 2018
 * roundbananas.com
 * 
 */

 #include "Radio.h"
 
 Radio::Radio(int CEpin, int CSNpin, uint64_t pipe)
 {
     
        m_Pipe = pipe;
     
     m_pRF24 = new RF24(CEpin, CSNpin);
 } 

void Radio::Begin()
{
  m_pRF24->begin();
}

void Radio::OpenWritingPipe()
{
  m_pRF24->stopListening();
  m_pRF24->openWritingPipe(m_Pipe); 
}

void Radio::OpenReadingPipe(int pipeIndex)
{
  m_pRF24->openReadingPipe(pipeIndex, m_Pipe);
  m_pRF24->startListening();
}

void Radio::CloseReadingPipe(int pipeIndex)
{
  m_pRF24->closeReadingPipe(pipeIndex);
}

bool Radio::Write(const void* p_dataToBeSent, uint8_t numberOfBytes)
{
  bool value = m_pRF24->write(&p_dataToBeSent, numberOfBytes);
  return value;
}

bool Radio::Available()
{
  bool value = false;
  if(m_pRF24->available(m_Pipe))
  {
    value = true;
  }
  return value;
}

void Radio::Read( void* p_dataToBeRead, uint8_t numberOfBytes)
{
  
  m_pRF24->read(&p_dataToBeRead, numberOfBytes);
}

unsigned long Radio::GetInterval()
{
  return m_txIntervalMillis;
}
