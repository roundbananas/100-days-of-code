//
//  ScoreController.cpp
//
//  Created by Carl Turner on 12/10/18.
//
#include "ScoreController.h"

ScoreController::ScoreController()
{
  m_TargetScore = 1000;
  m_TargetReached = false;

  m_CurrentScore = 0;
  m_Scaler = 1.0f;
}

void ScoreController::AddScore(int scoreValue, int stripLength)
{
  if(scoreValue < 0) 
  { 
    //don't want to have negative points incurred.
    return;
  }
  
  scoreValue *= m_Scaler;
  //give players a bonus points if they collided very close to the end of their strips
  if (scoreValue > m_HighBonus * stripLength) 
  {
    m_CurrentScore += 200;
  }
  else if (scoreValue > m_LowBonus * stripLength) 
  {
    m_CurrentScore += 100;
  }
  else
  {
    m_CurrentScore += scoreValue; 
  }

  if (m_CurrentScore >= m_TargetScore)
  {
    m_TargetReached = true;
  }
}

void ScoreController::ResetScore()
{
  m_CurrentScore = 0;
  m_TargetReached = false;
}

int ScoreController::GetCurrentScore()
{
 return m_CurrentScore;
}

bool ScoreController::GetTargetReached()
{
  return m_TargetReached; 
}
