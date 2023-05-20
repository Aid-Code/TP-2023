#define TOTAL 20

int datoAct = 0;
int datoAnt = 0;
int dato = 0;
int lectura;

unsigned int maximo;
unsigned int minimo;
float promedio = 0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  dato = datoAnt;
  
  if (Serial.available() > 0)
  {
    datoAct = Serial.parseInt();
    datoAnt = datoAct;
    lectura++;
    Serial.print(lectura);
    Serial.print(": ");
    Serial.println(datoAct);
    
    Promedio();
    Maximo();
    Minimo();
    
    if (lectura == TOTAL)
    {
      Serial.print("El promedio actual es   ");
      Serial.println(promedio);
      Serial.print("El maximo actual es   ");
      Serial.println(maximo);
      Serial.print("El minimo actual es   ");
      Serial.println(minimo);
      Serial.println("Ingrese un numero");
      lectura = 1;
      maximo = 0;
      minimo = 10000;
      promedio = 0;
    }
    
  }
}

void Maximo()
{
  if (lectura == 1)
  {
    maximo = datoAct;
  }
    
  if (datoAct > dato)
  {
    if (datoAct > maximo)
    {
      maximo = datoAnt;
    }
  } 
}

void Minimo()
{
  if (lectura == 1)
  {
    minimo = datoAct;
  }
    
  if (datoAct < minimo)
  {
    minimo = datoAct;
  }
}

void Promedio()
{
  promedio = promedio + datoAct;
  
  if (lectura == TOTAL)
  {
    promedio = promedio / TOTAL;
  }
}
