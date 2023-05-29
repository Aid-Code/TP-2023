//Filtro Básico Temperatura - Aiden Maid - 2023

#define TEMP A0

void setup() 
{
  Serial.begin(9600);
  
  pinMode(TEMP, INPUT);
}

void loop() 
{
  float lecturaAnalog;
  float tension;
  float temperatura;
  float sumaTemp = 0;
  float promedioTemp = 0;

  for (int i = 0; i < 10; i++)
  {
    lecturaAnalog = analogRead(TEMP);
    tension = lecturaAnalog * 5 / 1023;
    temperatura = tension * 50 / 5;
    delay(100);
    Serial.println(temperatura);
    sumaTemp = sumaTemp + temperatura;
  }

  promedioTemp = sumaTemp / 10;
  Serial.print("El promedio es: ");
  Serial.println(promedioTemp);
}
