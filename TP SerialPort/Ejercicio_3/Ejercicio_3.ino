int lectura;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    lectura = Serial.read();

    Serial.print("El caracter ingresado es: ");
    Serial.write(lectura);
    Serial.print(" y su valor en ASCII es: ");
    Serial.println(lectura);
  }
}
