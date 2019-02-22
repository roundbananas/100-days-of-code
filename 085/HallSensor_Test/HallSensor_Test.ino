/*
 * Hall Sensor Test
 * 1. Turn on an LED when a hall sensor is triggered.
 *    
 * Use interrupt to read the hall sensors, 
 * without delaying the rest of the program.
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * 
 * Note on pinmodes: https://www.arduino.cc/en/Tutorial/DigitalPins
 */

//****** VARIABLES ******//
//Hall sensors and states to toggle
byte Hall_InterruptPin = 2; //pins 2 and 3 on Uno are designated interrupt pins
volatile bool Hall_State = LOW;

//LED
byte LED_pin = 4;

//This function is called when there's a change registered by the hall sensor
void UpdateHallState() {
  Hall_State = !Hall_State;
}

void setup() {
  //Setup pin modes
  pinMode(Hall_InterruptPin, INPUT_PULLUP);
  pinMode(LED_pin, OUTPUT);

  //setup to the interrupt to toggle Hall_State
  //whenever the magnet moves onto or away from the sensor
  attachInterrupt(digitalPinToInterrupt(Hall_InterruptPin), UpdateHallState, CHANGE);
}

void loop() {
  //turn on LED when the magnet is near hall sensor
  digitalWrite(LED_pin, Hall_State);
}
