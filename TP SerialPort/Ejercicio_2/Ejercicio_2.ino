#define LED_R 3
#define LED_G 4
#define LED_B 5

char lectura;

void setup() 
{
  Serial.begin(9600);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    lectura = Serial.read();
    Serial.println(lectura);

    if (lectura == 'r')
    {
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
    }
    else if (lectura == 'g')
    {
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
    }
    else if (lectura == 'b')
    {
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, HIGH);
    }
  }
}
