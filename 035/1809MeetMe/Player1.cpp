//
//  Player1.cpp
//
//  Created by Carl Turner on 18/9/18.
//

#include "Player1.h"

Player1::Player1()
{


}
void Player1::spawn(int r, int g, int b)
{
    m_Colour[0] = r;
    m_Colour[1] = g;
    m_Colour[2] = b;
}

bool Player1::handleInput()
{
  return true;
}
