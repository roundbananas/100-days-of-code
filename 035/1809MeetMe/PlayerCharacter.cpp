//
//  PlayerCharacter.cpp
//
//  Created by Carl Turner on 18/9/18.
//

#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
  m_Score = 0;
}

void PlayerCharacter::addScore()
{
  m_Score += 10;
}


int PlayerCharacter::getScore()
{
  return m_Score;
}

void PlayerCharacter::setScore(int score)
{
  m_Score = score;
}

int* PlayerCharacter::getColour()
{
  return m_Colour[3];
}

void PlayerCharacter::updatePlayer(unsigned long currentTime)
{
  m_HasFired = true;
}
