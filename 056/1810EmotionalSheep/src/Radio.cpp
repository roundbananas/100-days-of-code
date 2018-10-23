#include "Radio.h"

void spawn(int board, int type)
{
    switch (board)
    {
        case 0: // Uno
            RF24 m_Radio(9,10);
            break;
        case 1: // Mega
            RF24 m_Radio(40,53);
            break;
    }

    switch (type)
    {
        case 0: // TX
            m_Pipe = 0xE8E8F0F0E1LL;
            break;
        case 1: // RX
            m_Pipe = ;
            break;
    }
    
    m_Radio.begin();
    m_Radio.openWritingPipe(m_Pipe);
}