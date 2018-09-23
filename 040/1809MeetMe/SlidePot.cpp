//
//  SlidePot.cpp
//
//  Created by Carl Turner on 18/9/18.
//

#include "SlidePot.h"
#include "Arduino.h"

void SlidePot::spawn(int pin, int rangeMin, int rangeMax)
{
  m_PotPin = pin;
  pinMode(m_PotPin, INPUT);
  
  m_RangeMin = rangeMin;
  m_RangeMax = rangeMax;

  m_PotValue = analogRead(m_PotPin);
  m_PotValue = map(m_PotValue, m_RangeMin, m_RangeMax, 0, 255);
  m_PotValue = constrain(m_PotValue, 0, 255);
}
    
int SlidePot::updateSlidePot()
{
  m_PotValue = analogRead(m_PotPin);
  m_PotValue = map(m_PotValue, m_RangeMin, m_RangeMax, 0, 255);
  m_PotValue = constrain(m_PotValue, 0, 255);
  return m_PotValue;
}
    
