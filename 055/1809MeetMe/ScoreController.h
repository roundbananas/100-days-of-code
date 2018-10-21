//
//  ScoreController.h
//
//  Created by Carl Turner on 12/10/18.
//
// This class keeps score.

#ifndef ScoreController_h
#define ScoreController_h

//#include "Arduino.h"

class ScoreController
{
  private:
  int m_TargetScore; //at what score will the game be over, will we win and celebrate?
  bool m_TargetReached; //if true, this wil lbe used to trigger GameOver mode
  
  int m_CurrentScore; //what's our current score?
  float m_Scaler; //used to scale the current score value (game balancing)
  
  public:
  ScoreController(); // constructor
  void AddScore(int scoreValue, int stripLength); //updates member variables with data from the game
  void ResetScore();
  //the following getter functions are called by render, when displaying the score
  int GetCurrentScore(); //get the current score to display
  bool GetTargetReached(); 
   
};
#endif
