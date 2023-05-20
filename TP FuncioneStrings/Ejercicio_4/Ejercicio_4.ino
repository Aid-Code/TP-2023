#define RGB 13

String red;
String green;
String blue;

int r;
int g;
int b;

int iNumeral;
int iAsterisco;
int iComaInicial;
int iComaFinal;

String lectura;

void setup() 
{
  Serial.begin(9600);

  pinMode(RGB, OUTPUT);
}

void loop() 
{
  while(Serial.available() == 0){}
  
  lectura = Serial.readString();
  Serial.println(lectura);

  SubString();

  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
}

int SubString ()
{
  iAsterisco = lectura.indexOf('*');
  iComaInicial = lectura.indexOf(',', 2);
  iComaFinal = lectura.indexOf(',', 5);
  iNumeral = lectura.indexOf('#');

  red = lectura.substring(iAsterisco + 1, iComaInicial);
  green = lectura.substring(iComaInicial + 1, iComaFinal);
  blue = lectura.substring(iComaFinal + 1, iNumeral);

  r = red.toInt();
  g = green.toInt();
  b = blue.toInt();
  
  if (r < 0 || g < 0 || b < 0)
  {
    Serial.println("Error en la estructura o en los valores ingresados");
  }
  else if (r > 255 || g > 255 || b > 0255)
  {
    Serial.println("Error en la estructura o en los valores ingresados");
  }
}
