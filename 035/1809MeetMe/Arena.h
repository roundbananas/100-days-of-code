//
//  Arena.h
//
//  Created by Carl Turner on 18/9/18.
//
#ifndef Arena_h
#define Arena_h

#include "SlidePot.h"

SlidePot* createPots(int numPlayers);
ButtonMom* createButtons(int numPlayers);



#endif

SlidePot* createPots(int numPlayers)
{
  SlidePot* slidePots = new SlidePot[numPlayers];

  for (int i=0; i < numPlayers; i++)
  {
    int pin = 10+i; 
    int rangeMin = 0;
    int rangeMax = 255;
    slidePots[i].spawn(pin, rangeMin, rangeMax);
  }
  return slidePots;
}

ButtonMom* createButtons(int numPlayers)
{
  ButtonMom* buttons = new ButtonMom[numPlayers];

  for (int i=0; i < numPlayers; i++)
  {
    int pin = 7+i; 
    int rangeMin = 0;
    int rangeMax = 255;
    buttons[i].spawn(pin);
  }
  return buttons;
}

Bullet* createBullets(int numBullets)
{
  Bullet* bullets = new Bullet[numBullets];
  
  for (int i=0; i < numBullets; i++)
  {
      int head = 0;
      int tail = -5;
      bullets[i].spawn(head, tail);
  }
  
}
