#define LED 13

int lecturaLed;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() 
{
  digitalToggle(lecturaLed);
  delay(500);
}

void digitalToggle(int pin)
{
  lecturaLed = digitalRead(LED);
  
  if (lecturaLed == 1)
  {
    digitalWrite(LED, LOW);
  }
  else if (lecturaLed == 0)
  {
    digitalWrite(LED, HIGH);
  }
}
