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
ButtonMom* createBoostButtons(int numPlayers, int firstBoostPin);
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
  long colour;
  for (int i = 0; i < numPlayers; i++)
  {
    switch(i)
    {
      case 0: //player 1
        colour = 0x8B0000; // 8B0000 = dark red
        break;
      case 1: //player 2
        colour = 0x00bbff; //00bbff = blue
        break;
      case 2: //player 3
        colour = 0x00ff00; //0x00ff00 = green
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

ButtonMom* createBoostButtons(int numPlayers, int firstBoostPin)
{
  ButtonMom* boostButtons = new ButtonMom[numPlayers];
  for (int i=0; i < numPlayers; i++)
    {
     int pin = firstBoostPin + i; 
     boostButtons[i].spawn(pin);
    }
  return boostButtons;
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
  //I thought the above line would initialise using the default constructor, but it doesn't seem to. 

  for (int i=0; i < numExplosions; i++)
  {
      explosions[i].Spawn();
  }
  return explosions;
}
