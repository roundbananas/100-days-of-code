//
//  ScoreController.cpp
//
//  Created by Carl Turner on 12/10/18.
//
#include "ScoreController.h"

ScoreController::ScoreController()
{
  m_Colour = 0x77f442; //77f442 = lime green
  m_TargetScore = 100;
  
  m_CurrentScore = 0;
  m_ScoreAdded = 0;

  m_Scaler = 0.2f;

  m_FlashInterval = 500; //ms
  m_FlashingDuration = 3500; //ms
  
  m_LastToggleTime = 0;
  m_StartedAt  = 0;
  m_On = false;  
}

void ScoreController::AddScore(int scoreValue, int stripLength)
{
  m_On = true;
  scoreValue *= m_Scaler;
  //give players a bonus points if they collided very close to the end of their strips
  if (scoreValue > 0.98 * stripLength) 
  {
    m_ScoreAdded += 50;
  }
  else if (scoreValue > 0.95 * stripLength)
  {
    m_ScoreAdded += 30;
  }
  else
  {
    m_ScoreAdded += scoreValue; 
  }
}

void ScoreController::Update(unsigned long t)
{
  if((t - m_StartedAt) > m_FlashingDuration) //if we're done flashing
  {
    m_On = true;
    m_CurrentScore = m_CurrentScore + m_ScoreAdded; //add the new points to the current score
    m_ScoreAdded = 0;               
  }
  else if ((t - m_LastToggleTime) > m_FlashInterval)
  {
    m_LastToggleTime = t;
    m_On = !m_On; //toggle the boolean variable, which we Render() will refer to when displaying the score
  }
}

void ScoreController::SetStartedAt(unsigned long startedAt)
{
  m_StartedAt = startedAt;
}

int ScoreController::GetCurrentScore()
{
 return m_CurrentScore;
}
int ScoreController::GetScoreAdded()
{
  return m_ScoreAdded;
}
bool ScoreController::GetOn()
{
  return m_On; 
}
int ScoreController::GetColour()
{
  return m_Colour;
}
