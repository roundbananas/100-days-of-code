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
  int m_Colour[];
  bool m_Active;    //the explosion is happening
  int m_Strip;      //which led strip is this explosion happening on?
  float m_Position; //where on the led strip is the explosion happening?
  unsigned long m_StartedAt;  //what time did the explosion start?

  float m_Head;
  float m_Tail;

  unsigned long m_Duration; //how fast does it animate in pixels per second?
  float m_Size; //how many pixels either side of the position does the explosion spread to?
  
  public:
  Explosion();
  void Spawn();
  bool IsActive();
  void SetActive(unsigned long currentTime, int strip, float pos);
  void Update (unsigned long t);
  int* GetColour();
  float GetPosition();
  int GetStrip();

  float GetHead();
  float GetTail();
};
#endif
