//Quick check to confirm I can use byte in place of 
//uint16_t, for values between 0-255.
//Yes. It works.

uint16_t head = 0;
byte NewValue;

void function(uint16_t var)
{
    NewValue = var;   
    Serial.print(" - ");
    Serial.println(NewValue);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 300; i++)
  {
      Serial.print(head);
      function(head);
      head++;
  }
 


}

void loop() {
  // put your main code here, to run repeatedly:

}
