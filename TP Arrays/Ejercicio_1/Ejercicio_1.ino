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
    total = total + vecMeses[i];

    if (vecMeses[i] > mayor)
    {
      mayor = vecMeses[i];
    }

    if (vecMeses[i] < menor)
    {
      menor = vecMeses[i];
    }
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
