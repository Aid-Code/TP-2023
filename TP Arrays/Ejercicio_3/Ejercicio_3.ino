#define CANT 20 
String lectura; 

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  char vector[CANT];
  int i;
  while (Serial.available() == 0){}
  i = 0;
  while (Serial.available() > 0)
  {
    vector[i] = Serial.read();
    i++;
  }
  
  toUpper(vector, CANT); 
  Serial.print(vector);
  
}

void toUpper(char *Vec, int cantElem)
{
  for (int i; i < cantElem; i ++)
  {
    if (Vec[i] >= 'a' && Vec[i] <= 'z')
    {
      Vec[i] = Vec[i] - 32;
    }
  }
}
