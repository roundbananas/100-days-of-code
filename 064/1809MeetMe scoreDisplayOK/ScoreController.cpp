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
  scoreValue *= m_Scaler;
  //give players a bonus points if they collided very close to the end of their strips
  if (scoreValue > 0.95 * stripLength) //if we've got 90 LEDs (1.5m of 60/m), this equates to the last 4 LEDs
  {
    m_CurrentScore += 800;
  }
  else if (scoreValue > 0.90 * stripLength) //if we've got 90 LEDs (1.5m of 60/m), this equates to the last 9 LEDs
  {
    m_CurrentScore += 50;
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
