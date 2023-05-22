#define POTE A0
#define LED 4

void setup() 
{
  Serial.begin(9600);

  pinMode(POTE, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() 
{
  float lecturaAnalog;
  float tension;

  lecturaAnalog = analogRead(POTE);

  tension = lecturaAnalog * 5 / 1023;
  Serial.println(tension);
  
  if (tension > 3.5)
  {
    digitalWrite(LED, HIGH);
  }

  if (tension < 2.5)
  {
    digitalWrite(LED, LOW);
  }
}
