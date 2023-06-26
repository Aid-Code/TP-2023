#define CANT 5

void sortMaxToMin(int *vec, int cant_elem);

int vector[CANT];
String lectura;
bool flag;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  for (int i; i < CANT; i++)
  {
    vector[i] = Serial.parseInt();
  }

  sortMaxToMin(*vector, CANT);
}

void sortMaxToMin(int *vec, int cant_elem)
{
  while (flag)
  {
    for (int i; i < cant_elem + 1; i++)
    {
      if (vec[i] > vec[i+1])
      {
        vec[i] = vec[i+1];
      }
      else
      {
        flag = false;
      }
    }
  }
}
