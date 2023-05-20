float resultado;
float lecturaBase;
int lecturaExponente;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.print("Ingresar una base:  ");
  while (Serial.available() == 0){}
  lecturaBase = Serial.parseFloat();
  Serial.println(lecturaBase);

  Serial.print("Ingresar un exponente:  ");
  while (Serial.available() == 0){}
  lecturaExponente = Serial.parseInt();
  Serial.println(lecturaExponente);

  FuncionExponencial(lecturaBase, lecturaExponente);

  Serial.print("Tu resultado es:   ");
  Serial.println(resultado);
}

float FuncionExponencial (float base, int exponente)
{
  for (int i = 0; i <= exponente; i++)
  {
    resultado = base * base;
  }
}
