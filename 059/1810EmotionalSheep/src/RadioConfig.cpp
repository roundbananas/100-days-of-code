/*
 * 
 * Carl Turner 27 October 2018
 * roundbananas.com
 * 
 */
#include "RadioConfig.h"

uint64_t RadioConfig::GetPipe()
{
    return m_pipe;
}
unsigned long RadioConfig::GetInterval()
{
    return m_txIntervalMillis;
}