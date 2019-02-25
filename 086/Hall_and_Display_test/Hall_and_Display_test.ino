/*
 *    
 * Use interrupt to read the hall sensors, 
 * without delaying the rest of the program.
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * 
 * Note on pinmodes: https://www.arduino.cc/en/Tutorial/DigitalPins
 */

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//****** HALL SENSORS ******//
byte sensor1_InterruptPin = 2;
byte sensor2_InterruptPin = 3;
volatile bool sensor1_state = LOW;
volatile bool sensor2_state = LOW;

//This function is called when there's a change registered by the hall sensor
void UpdateSensor1State() {
  sensor1_state = !sensor1_state;
}

void UpdateSensor2State() {
  sensor2_state = !sensor2_state;
}


//****** LEDS ******//
byte LED_pin = 4;

//****** OLED ******//
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);



void setup() {
  //setup to the interrupt to toggle Hall_State
  //whenever the magnet moves onto or away from the sensor
  pinMode(sensor1_InterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor1_InterruptPin), UpdateSensor1State, CHANGE);
  pinMode(sensor2_InterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensor2_InterruptPin), UpdateSensor2State, CHANGE);

  pinMode(LED_pin, OUTPUT);

  u8g2.begin();

  Serial.begin(9600);
  Serial.println("End Setup");

}

void loop() {
  //turn on LED when the magnet is near hall sensor
  digitalWrite(LED_pin, sensor1_state);   Serial.println(sensor1_state);
  digitalWrite(LED_pin, sensor2_state);   Serial.println(sensor2_state);

  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_t0_16_mr); // choose a suitable font
  u8g2.drawStr(0,10,"Hello World!");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
}
