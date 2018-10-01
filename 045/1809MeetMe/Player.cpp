//
//  Player.cpp
//
//  Created by Carl Turner on 18/9/18.
//

#include "Player.h"

Player::Player()
{
 
}
void Player::spawn(int* colour)
{
    m_Colour[0] = colour[0];
    m_Colour[1] = colour[1];
    m_Colour[2] = colour[2];

     m_IsReady = false;
     m_HasFired = false;
     m_IsExploding = false;
}
bool Player::isReady()
{
  return m_IsReady;
}
void Player::setReady(bool value)
{
  m_IsReady = value;
}

bool Player::getHasFired()
{
  return m_HasFired;
}
void Player::setHasFired()
{
  m_HasFired = true;
}

void Player::setIsExploding()
{
  m_IsExploding = true;
}

bool Player::isExploding()
{
  return m_IsExploding;
}
 
int* Player::getColour()
{
  return m_Colour;
}
void Player::setBulletIndex(int index)
{
  m_CurrentBulletIndex = index; 
}
int Player::getBulletIndex()
{
  return m_CurrentBulletIndex;
}
