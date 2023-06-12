#define CANT 5

int vector[CANT];
String lectura;}
bool flag;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  for (int i; i < CANT; i++)
  {
    lectura = Serial.readString();
    vector[i] = lectura.parseInt();
  }

  sortMaxToMin(vector[], CANT);
}

void sortMaxToMin(int *array, int size)
{
  while (flag)
  {
    for (int i; i < CANT + 1; i++)
    {
      if (vec[i] > vec[i+1])
      {
        vec[i] = vec[i+1];
      }
    }
  }
}
