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
  m_PotValue = map(m_PotValue, m_RangeMin, m_RangeMax, 5.0f, 1.0f);
  m_PotValue = constrain(m_PotValue, 0.0f, 1.0f);
}
    
float SlidePot::updateSlidePot()
{
  m_PotValue = analogRead(m_PotPin);
  m_PotValue = map(m_PotValue, 0.0f, 1023.0f, 5.0f, 100.0f);
  m_PotValue = constrain(m_PotValue, 5.0f, 100.0f);
  return m_PotValue;
}
    
