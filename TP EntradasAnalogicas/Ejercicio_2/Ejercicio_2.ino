#define TEMP A0
#define LED 4

void setup() 
{
  Serial.begin(9600);
  
  pinMode(TEMP, INPUT);
  pinMode(LED, OUTPUT);

  Serial.println("Bienvenidx al sistema metereologico de GentileSoft");
}

void loop() 
{
  float lecturaAnalog;
  float tension;
  float temperatura;

  lecturaAnalog = analogRead(TEMP);
  tension = lecturaAnalog * 5 / 1023;
  temperatura = tension * 50 / 5;
  if (tension > 0 - 0.2 && tension < 0 + 0.2)
  {
    temperatura = -10;
  }

  Serial.println(temperatura);
  
  if (temperatura <= 10)
  {
    Serial.println("Temperatura baja");
    digitalWrite(LED, LOW);
  }

  if (temperatura > 10 && temperatura < 25)
  {
    Serial.println("Temperatura media");
    digitalWrite(LED, LOW);
  }

  if (temperatura > 25)
  {
    Serial.println("Temperatura elevada");
    digitalWrite(LED, HIGH);
  }
}
