//
//  Arena.h
//
//  Created by Carl Turner on 18/9/18.
//
#ifndef Arena_h
#define Arena_h

#include "SlidePot.h"
#include "Player.h"
#include "ButtonMom.h"
#include "Explosion.h"

Player* createPlayers(int numPlayers);
SlidePot* createPots(int numPlayers, int firstPin);
ButtonMom* createButtons(int numPlayers, int firstPin);
Bullet* createBullets(int numBullets);
Explosion* createExplosions(int numExplosions);

//Adafruit_DotStar* createLEDS(int numPlayers);

#endif

/*
Adafruit_DotStar* createLEDS(int numPlayers)
{
  Adafruit_DotStar* m_PlayerLEDS = new Adafruit_DotStar[numPlayers];
  
  for (int i = 0; i < numPlayers; i++)
    {
      m_PlayerLEDS[i] = Adafruit_DotStar(stripLengthArray[i], stripDataPinArray[i], stripClockPinArray[i], DOTSTAR_BRG);
    }
  return m_PlayerLEDS;
}
*/

Player* createPlayers(int numPlayers)
{
  Player* players = new Player[numPlayers];
  int colour[] = {0, 0, 0};
  for (int i = 0; i < numPlayers; i++)
  {
    switch(i)
    {
      case 0: //player 1
        colour[0] = 255;
        colour[1] = 255;
        colour[2] = 0;
        break;
      case 1: //player 2
        colour[0] = 0;
        colour[1] = 0;
        colour[2] = 255;
        break;
    }
    players[i].spawn(colour);
  }
 
  return players;
}

SlidePot* createPots(int numPlayers, int firstPin)
{
  SlidePot* slidePots = new SlidePot[numPlayers];

  for (int i=0; i < numPlayers; i++)
  {
    int pin = firstPin + i; 
    int rangeMin = 0;
    int rangeMax = 1023;
    slidePots[i].spawn(pin, rangeMin, rangeMax);
  }
  return slidePots;
}

ButtonMom* createButtons(int numPlayers, int firstPin)
{
  ButtonMom* buttons = new ButtonMom[numPlayers];

  for (int i=0; i < numPlayers; i++)
  {
    int pin = firstPin + i; 
    buttons[i].spawn(pin);
  }
  return buttons;
}

Bullet* createBullets(int numBullets)
{
  Bullet* bullets = new Bullet[numBullets];
  
  for (int i=0; i < numBullets; i++)
  {
      bullets[i].spawn();
  }
  return bullets;
}

Explosion* createExplosions(int numExplosions)
{
  Explosion* explosions = new Explosion[numExplosions];

  //the above line should initialise using the default constructor I think. 
  //If we wanted to pass an argument to spawn the explosions in a different way (say depending on level),
  //then we could create a spawn() function to do that.
  return explosions;
}