//
//  SlidePot.h
//
//  Created by Carl Turner on 18/9/18.
//

#ifndef SlidePot_h
#define SlidePot_h

#include "Arduino.h"

class SlidePot
{
  private:
    int m_PotPin;

    //calibrate or map the range if needed
    int m_RangeMin;
    int m_RangeMax;

    int m_PotValue; 

  public:
    void spawn(int pin, int rangeMin, int rangeMax);
    void updateSlidePot();
    int getPotValue();
};

#endif
