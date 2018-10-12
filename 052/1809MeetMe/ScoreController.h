//
//  ScoreController.h
//
//  Created by Carl Turner on 12/10/18.
//
// This class controls the visualisation of the score
// The idea is to display the current score using illuminated leds. 
// When new points are added to the score the leds representing those new points flash for a while before becoming solid.
// When you reach the max points/ or the target amount of points, an animation of all the leds happens to celebrate.

#ifndef ScoreController_h
#define ScoreController_h

#include "Arduino.h"

class ScoreController
{
  private:
  int m_Colour; //what colour are the lights representing the score?
  
  int m_TargetScore; //at what score will the game be over, will we win and celebrate?
  
  int m_CurrentScore; //what's our current score?
  int m_ScoreAdded; //how many points did we just add to our score?
  float m_Scaler; //used to scale the current score value (game balancing)
  
  //when we add new points to our score, we'll flash the leds representing those points
  unsigned long m_FlashInterval; // how long should each flash be on/off?
  unsigned long m_FlashingDuration; //how long do we want to flash for?
  
  unsigned long m_LastToggleTime; //when was it last toggled on or off?
  unsigned long m_StartedAt; //when did we start flashing?
  bool m_On; //are the new points currently flashing on? (visible?)

  public:
  ScoreController(); // constructor
  void AddScore(int scoreValue, int stripLength); //updates member variables with data from the game
  void Update(unsigned long t); //updates the flashing behaviour

  void SetStartedAt(unsigned long startedAt);

  //the following getter functions are called by render, when displaying the score
  int GetCurrentScore(); //get the current score to display
  int GetScoreAdded(); //get the score added value to display. the Update fn will set m_ScoreAdded = 0, once it's stopped flashing
  bool GetOn(); 
  int GetColour();
   
};
#endif
