/*
 * Radio.h
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

 #ifndef RADIO_H
 #define RADIO_H
 
/*-------------------IMPORT LIBRARIES-------------------*/
#include <SPI.h>
#include "nRF24L01.h"
 #include "RF24.h"

 class Radio
 {
  private:
  /*
   * Create a pointer to a type RF24. This lets us delay 
   * having to specify the CE and CSN pins we want to use, 
   * which are required by the RF24 constructor.
   */
  RF24* m_pRF24; 
  /*
   * array of pipe addresses. 
   * Note: 
   *    pipe0 is also used by the writing pipe
   */
  uint64_t m_Pipe; 

  unsigned long m_txIntervalMillis = 1000; // transmit at specified intervals
  
  public:
  /*our own constructor, which will:
  *   - instantiate and initialise a radio, 
  *   - assign up to 6 pipe addresses, 
  *   - call begin().
  */
  Radio(int CEpin, int CSNpin, uint64_t pipe); 
  void Begin();
  void OpenWritingPipe(); //pipe 0 is the writing pipe, no other option. We'll include stopListening() in here too
  void OpenReadingPipe(int pipeIndex); //we'll include startListening() in here too
  void CloseReadingPipe(int pipeIndex);
  bool Write(const void* p_dataToBeSent, uint8_t numberOfBytes);
  bool Available();
  void Read( void* p_dataToBeRead, uint8_t numberOfBytes);
  
  unsigned long GetInterval();
 };

 #endif
