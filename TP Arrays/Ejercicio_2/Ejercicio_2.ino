#define meses 12

int vecMeses[meses];
int lecIngresos;
int contador;
int total;
float promedio;
int mayor;
int menor = 32767;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  for (int i = 0; i < meses; i++)
  {
    while (Serial.available() == 0){}
    contador = i;
    
    lecIngresos = Serial.parseInt();
    Serial.print(contador + 1);
    Serial.print("; ");
    
    vecMeses[i] = lecIngresos;

    ValorTotal(vecMeses, meses);
    MayorValor(vecMeses, meses);
    MenorValor(vecMeses, meses);
  }

  if (contador == 11)
  {
    PrintVector(vecMeses, meses);
    promedio = total / meses;

    Serial.println();
    Serial.print("Total: ");
    Serial.println(total);
    Serial.print("Promedio: ");
    Serial.println(promedio);
    Serial.print("Mayor ingreso: ");
    Serial.println(mayor);
    Serial.print("Menor ingreso: ");
    Serial.println(menor);
  }
}

void PrintVector (int Vec[], int cant)
{
  for (int i = 0; i < cant; i++)
  {
    Serial.println();
    Serial.print("Ingreso mes ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(Vec[i]);
  }
}

int ValorTotal (int Vec[], int cant)
{
  for (int i = 0; i < cant; i++)
  { 
    total = total + Vec[i];
  }
}

int MayorValor (int Vec[], int cant)
{
  for (int i = 0; i < cant; i++)
  { 
    if (Vec[i] > mayor)
    {
      mayor = vecMeses[i];
    }
  }
}

int MenorValor (int Vec[], int cant)
{
  for (int i = 0; i < cant; i++)
  { 
    if (Vec[i] < menor)
    {
      menor = vecMeses[i];
    }
  }
}
