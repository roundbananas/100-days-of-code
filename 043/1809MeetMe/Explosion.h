//
//  Explosion.h
//
//  Created by Carl Turner on 27/9/18.
//
#ifndef Explosion_h
#define Explosion_h

class Explosion
{
  private:
  int m_Colour[3];
  bool m_Active;    //the explosion is happening
  int m_Strip;      //which led strip is this explosion happening on?
  float m_Position; //where on the led strip is the explosion happening?
  unsigned long m_StartedAt;  //what time did the explosion start?
  
  public:
  Explosion();
  bool IsActive();
  void SetActive(unsigned long currentTime, int strip, float pos);
  void Update (unsigned long t);
  int* GetColour();
  float GetPosition();
  int GetStrip();
};
#endif
