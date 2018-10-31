
typedef struct {
  int throttleSpeed;
  int turnPosition;
} HumansOrders;

HumansOrders humansOrders;

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long intervalMillis = 50; // send at specified intervals

void setup() {
 Serial.begin(9600);
 humansOrders.throttleSpeed = 0;
 humansOrders.turnPosition = 0;
 prevMillis = millis();
}

void loop() {
currentMillis = millis();
 if (currentMillis - prevMillis >= intervalMillis) 
    {
      Serial.println(" ");
      Serial.print("Orders: ");
      Serial.print(humansOrders.throttleSpeed);
      Serial.print(" / ");
      Serial.println(humansOrders.turnPosition);

      UpdateOrders(&humansOrders);
      
      prevMillis = millis();
    }
}

void UpdateOrders(HumansOrders* var)
{
  var->throttleSpeed++;
  var->turnPosition--;
}
