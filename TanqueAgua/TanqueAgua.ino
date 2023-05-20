#define BMB 6
#define LED_LN 5
#define LED_VC 4
#define SEN_LN 7
#define SEN_VC 8

int percent;
int pwm;
int iGuion;
int iNumeral;
int lecturaLleno;
int lecturaVacio;

String percentS;
String lectura;

bool lleno;
bool vacio;

void setup()
{
  Serial.begin(9600);

  pinMode(BMB, OUTPUT);
  pinMode(LED_LN, OUTPUT);
  pinMode(LED_VC, OUTPUT);

  pinMode(SEN_LN, INPUT_PULLUP);
  pinMode(SEN_VC, INPUT_PULLUP);

  Serial.println("Ingresar el porcentaje de potencia de la bomba con este formato *C-XX#");
}

void loop()
{
  if (Serial.available() > 0) //Estado 4 - Si hay un dato disponible, lee y ejecuta SubString y Llenado
  {
    lectura = Serial.readString();
    SubString();
    Llenado();
  }

  if (digitalRead(SEN_LN) == HIGH && digitalRead(SEN_VC) == HIGH) //Estado 1 - Ambos sensores en 1 (tanque vacío) apaga Led lleno, prende Led vacio, indica por Serial
  {
    digitalWrite(LED_LN, LOW);
    digitalWrite(LED_VC, HIGH);
    Serial.println("Tanque vacío");
  }
  
  if (digitalRead(SEN_LN) == LOW && digitalRead(SEN_VC) == LOW) //Estado 2 - Ambos sensores en 0 (tanque lleno) apaga Led vacío, prende Led lleno, indica por Serial
  {
    analogWrite(BMB, LOW);
    digitalWrite(LED_LN, HIGH);
    digitalWrite(LED_VC, LOW);
    Serial.println("Carga completa");
  }

  if (digitalRead(SEN_VC) == LOW && digitalRead(SEN_LN) == HIGH) //Estado 3 - Sensor vacío en 0, sensor lleno en 1 (tanque medio lleno) apaga todos los Leds
  {
    digitalWrite(LED_LN, LOW);
    digitalWrite(LED_VC, LOW);
  }

  if (digitalRead(SEN_VC) == HIGH && digitalRead(SEN_LN) == LOW) //ERROR - Sensor lleno en 0, sensor vacío en 1 (no tiene sentido) indica el error
  {
    Serial.println("Error en el sensado");
  }
}

int SubString()
{
  iGuion = lectura.indexOf('-');
  iNumeral = lectura.indexOf('#');

  percentS = lectura.substring(iGuion + 1, iNumeral);

  percent = percentS.toInt();
}

void Llenado()
{
  pwm = percent * 2.55;

  analogWrite(BMB, pwm);
  Serial.print("Llenando a potencia ");
  Serial.print(percent);
  Serial.println("%");
}
