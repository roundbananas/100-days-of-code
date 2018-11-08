//
//  Player.cpp
//
//  Created by Carl Turner on 18/9/18.
//

#include "Player.h"

Player::Player()
{
 
}
void Player::spawn(long colour)
{
    m_Colour = colour;
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
 
long Player::getColour()
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
