/*
 * HallSensor.h
 * 
 * By Carl Turner 4 March 2019
 * roundbananas.com
 * 
  */

 #ifndef HallSensor_h
 #define HallSensor_h

 class HallSensor {
  private:
    byte m_InterruptPin;
    volatile bool sensorState = LOW;

  public:
  
    HallSensor();

    void Setup(byte interruptPin){
      m_InterruptPin = interruptPin;
      pinMode(m_InterruptPin, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(m_InterruptPin), Update, CHANGE);
    }
    
    void Update() { sensorState = !sensorState;} //Called when there's a 'CHANGE' registered by the hall sensor
 };
 #endif
