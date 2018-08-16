/*
 * Carl Turner 2018
 * roundbanans.com
 * 
 * Class declaration for a an Enemy character.
 */

 #ifndef Enemy_h
 #define Enemy_h

 class Enemy
 {
  //Member variables
  private:
  int m_pos;                  //current position of the enemy (1 dimensional)
  unsigned long m_time_arrived_at_pos;  
  int m_loiter_time;          //how long enemy stays in current position
  int m_colourR;              //specify colour of the enemy
  int m_colourG;
  int m_colourB;

  public:
  //Forward declaration for constructor
  Enemy(int pos, unsigned long time_arrived_at_pos, int loiter_time, int colourR, int colourG, int colourB);

  //Forward declaration for methods
  int Move(int pos); //{ return m_pos;} //called to move the enemy to next position
  void Die();                 //called when we want to destroy the enemy
  
 };

#endif
