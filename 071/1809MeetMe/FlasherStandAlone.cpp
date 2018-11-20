/*
 * FlasherStandAlone.cpp
 * 
 * Created by Carl Turner on 8/11/18.
 * 
 * A single coloured LED that flashes. Not intended for use with RGB LEDs or LED strips
 */

#include "Arduino.h"
#include "FlasherStandAlone.h"

FlasherStandAlone::FlasherStandAlone()
{
}

void FlasherStandAlone::Spawn(int pinNumber, long onDuration)
{
  m_pin = pinNumber;
  pinMode(m_pin, OUTPUT);
  m_OnDuration = onDuration;
  m_OffDuration = onDuration;
  m_LedMode = 0; //off
  m_LedState = LOW;
  m_PreviousMillis = 0;
}

int FlasherStandAlone::GetMode()
{
  return m_LedMode;
}

void FlasherStandAlone::SetMode(int mode)
{
  m_LedMode = mode;
}

void FlasherStandAlone::Update()
{
  switch(m_LedMode) //(0 = ConstantOff, 1 = ConstantOn, 2 = Flashing)
  {
    case 0: 
      m_LedState = LOW;
      digitalWrite(m_pin, m_LedState);
      break;
    
    case 1:
      m_LedState = HIGH;
      digitalWrite(m_pin, m_LedState);
      break;
      
    case 2:
      unsigned long currentMillis = millis();
      if((m_LedState == HIGH) && (currentMillis - m_PreviousMillis >= m_OnDuration))
      {
        m_LedState = LOW;
        m_PreviousMillis = currentMillis;
        digitalWrite(m_pin, m_LedState);
      }
      else if ((m_LedState == LOW) && (currentMillis - m_PreviousMillis >= m_OffDuration))
      {
        m_LedState = HIGH;
        m_PreviousMillis = currentMillis;
        digitalWrite(m_pin, m_LedState);
      }
      break;
  }
}
/*
void FlasherStandAlone::TurnOff()
{ 
  m_LedMode = 0; //constant off
  m_LedState = LOW;
  digitalWrite(m_pin, m_LedState);
}

void FlasherStandAlone::TurnOn()
{
  m_LedMode = 1; //constant on
  m_LedState = HIGH;
  digitalWrite(m_pin, m_LedState);
}
  
void FlasherStandAlone::FlashLed()
{
  m_LedMode = 2; //flashing
  unsigned long currentMillis = millis();

  if((m_LedState == HIGH) && (currentMillis - m_PreviousMillis >= m_OnDuration))
  {
    m_LedState = LOW;
    m_PreviousMillis = currentMillis;
    digitalWrite(m_pin, m_LedState);
  }
  else if ((m_LedState == LOW) && (currentMillis - m_PreviousMillis >= m_OffDuration))
  {
    m_LedState = HIGH;
    m_PreviousMillis = currentMillis;
    digitalWrite(m_pin, m_LedState);
  }
  
}  */
