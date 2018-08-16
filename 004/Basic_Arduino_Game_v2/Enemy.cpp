/*
 * Carl Turner 2018
 * roundbanans.com
 * 
 * Class implementation for an Enemy character
 */

#include "Enemy.h"
#include "Arduino.h"

//VantagePoints holds the possible positions the enemy could be in (ie the game board)
//will move VantagePoints to its own GameBoard class eventually.
int VantagePoints[] = {0,1,2,3,4};

   //constructor
   Enemy::Enemy(int pos, unsigned long time_arrived_at_pos, int loiter_time, int colourR, int colourG, int colourB)
   {
      m_pos = pos;                  
      m_time_arrived_at_pos = time_arrived_at_pos;  
      m_loiter_time = loiter_time;          
      m_colourR = colourR;            
      m_colourG = colourG;
      m_colourB = colourB;
   }

   //member function definitions
  int Enemy::Move(int pos) {

    //if loiter time has been exceeded,
    
    //get a random position from the array of possible positions.
    //make sure it's not the same as current position
    
    int randomPos = random(0, sizeof(VantagePoints));
    while (randomPos == pos)
    {
      randomPos = random(0, sizeof(VantagePoints));
    }
    
    return randomPos;
    } 

  void Enemy::Die() {  
      
  }

