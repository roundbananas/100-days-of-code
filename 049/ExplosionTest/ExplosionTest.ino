// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include "Arduino.h"
#include <Adafruit_DotStar.h>
#include <SPI.h>        

#define NUMPIXELS 25 // Number of LEDs in strip
#define DATAPIN    6
#define CLOCKPIN   7
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

//Start positions and colours of each bullet
int      head1  = 0, tail1 = -5; // Index of first 'on' and 'off' pixels
uint32_t color = 0x008000;      // 'On' color (0x008000 = green)

int      head2  = 25, tail2 = 30; // Index of first 'on' and 'off' pixels
uint32_t color2 = 0xFF0000;      // 'On' color (starts FF0000 = red)

//Explosion class member variables
unsigned long m_StartedAt = 0; //time explosion started
unsigned long m_Duration = 500; //5ms
float m_MaxSize = 5.0f; //pixels in each direction from position

//constants for size calculation - from intercept form of parabolic equation, y = a(x-p)(x-q)
float m_const_p;
float m_const_q;
float m_const_a;
unsigned long m_tMaxSize;

uint32_t m_Colour = 0xea6e02; //ffa500 = orange, ea6e02 = burnt orange
bool m_IsActive = false;
float m_Position;

void setup() {
Serial.begin(9600);
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

void loop() {
  delay(20);
  unsigned long t = millis();
 // Serial.println(" ");
 // Serial.print("Head 1 position: "); Serial.println(head1);
//  Serial.print("Head 2 position: "); Serial.println(head2);  
    
  if (m_IsActive)
  {
    UpdateExplosion(t);
  }
  else
  {
    UpdatePositions();
    
    strip.setPixelColor(head1, color); // turn this pixel on
    strip.setPixelColor(tail1, 0);     // turn this pixel off
    
    strip.setPixelColor(head2, color2); 
    strip.setPixelColor(tail2, 0);     
    
    if (head1 > head2)
      {
        for (int i = 0; i < NUMPIXELS; i++) strip.setPixelColor(i, 0);
        m_Position = head2;
        m_StartedAt = millis();
        m_IsActive = true;
        //calculate constants 
        CalculateConstants(m_StartedAt);
      }
  }
  strip.show();                     // Refresh strip
}

 void CalculateConstants(unsigned long started_at)
        {
          m_const_p = m_StartedAt;
          m_const_q = m_StartedAt + m_Duration;
          m_tMaxSize = m_const_p + m_Duration/2;
          m_const_a = m_MaxSize/((m_tMaxSize - m_const_p)*(m_tMaxSize - m_const_q));
        }

// grow and collapse style explosion
void UpdateExplosion(unsigned long t)
{  
  if (t - m_StartedAt < m_Duration)
  {        
    float CurrentSize = m_const_a * (t - m_const_p) * (t - m_const_q);
    float ExplosionUp = m_Position + CurrentSize;
    float ExplosionDown = m_Position - CurrentSize;
     if (t > m_tMaxSize)
      {
        strip.setPixelColor(ExplosionUp, 0); 
         strip.setPixelColor(ExplosionDown, 0); 
      }
      else if (t <= m_tMaxSize)
      {
        strip.setPixelColor(ExplosionUp, m_Colour); 
         strip.setPixelColor(ExplosionDown, m_Colour); 
      }
  }
}

void UpdatePositions()
    {
      if(++head1 >= NUMPIXELS) head1 = 0; // Increment head index.  Off end of strip? //  Yes, reset head index to start
      if(++tail1 >= NUMPIXELS) tail1 = 0; // Increment, reset tail index

      if(--head2 <= 0) head2 = 25; // Increment head index.  Off end of strip?
      if(--tail2 <= 0) tail2 = 25; // Increment, reset tail index
    }


/*
//Original explosion test. Ripples outwards
void explode()
{
  for (int i=head; i < (head + 3); i++)
  {
    strip.setPixelColor(i, 0xffa500); 
    strip.show();
    //delay(1);
     
  }
  for (int i=head2; i > (head2 - 3); i--)
  {
    strip.setPixelColor(i, 0xffa500); 
    strip.show();
   // delay(1);
     
  }
  for (int i=0; i < NUMPIXELS; i++)
  {
  strip.setPixelColor(i, 0x000000); 
    strip.show();
  }
 }
 */
