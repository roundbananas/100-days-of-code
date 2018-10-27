//
//  Engine.h
//
//  Created by Carl Turner on 22/10/18.
//
//APA102 led strip - 3.3V!!! If you supply 5V you'll get residual colour, can't turn LEDs off!

#ifndef Engine_h
#define Engine_h

// Define structures and classes
#include "Arduino.h"
#include "Modes.h"
#include "ButtonMom.h"
#include "Joystick.h"
#include "Controller.h"
#include "RadioConfig.h"
#include "DataStructs.h"
#include "Motor.h"
#include "ServoMotor.h"

class Engine
{
  private:

    /*
    * CONFIGURATION
    * Set bool m_Transmitter to false if programming the receiver
    */
    bool m_Transmitter = false; 

    /*-------------------Variables to hold and manage the state-------------------*/
    Mode m_Mode;
    HumansOrders m_HumansOrders;
    unsigned long m_currentMillis;
    unsigned long m_prevMillis;

    /*-------------------Objects - TX-------------------*/
    //Buttons
    static const int m_NumButtons = 3;
    int m_ButtonPins[m_NumButtons] = {3, 4, 5}; //digital pins
    ButtonMom* m_Buttons = nullptr;

    //Joystick
    const int m_XPin = A0; //variable for joystick input (left/right)
    const int m_YPin = A1; //variable for joystick input (forward/back)
    Joystick m_joystick;

    /*-------------------Objects - RX-------------------*/
    //leds
    //TODO: work out the physical layout of leds first, and how I want to control them.

    //mp3 player
    
    //ultrasonic sensors for collision avoidance and triggering Mode changes

    //servo for dirn control
    const int m_ServoPin = 3;
    ServoMotor m_Servo;

    //motor for forward/backward movement
    const int m_MotorDirnPin = 4;
    const int m_MotorSpeedPin = 5;   
    Motor m_Motor;

    /*-------------------Objects - TX and RX-------------------*/
    RadioConfig radioConfig;  //describe how this works
    uint16_t m_CEpin = 7;
    uint16_t m_CSpin = 8;
    RF24* m_pRadio;

    /*-------------------Function Prototypes-------------------*/
    void m_Input(unsigned long t);
    void m_Update(unsigned long t);
    void m_Render();

  public:
    Engine();
    void runEngine();
};
#endif