#include "TimerOne.h"

#define INIT 0
#define M1_BMB_ON 1
#define M1_BMB_OFF 2
#define M2_BMB_ON 3
#define M2_BMB_OFF 4
#define STOP 5
#define MODO_1 6
#define MODO_2 7
#define M2_STOP 8

#define LED_INDICADOR 4
#define LED_KEEP_ALIVE 5
#define BMB 6
#define SW 2
#define HUM A0
#define PUL 3

int actualState = INIT;
int switchState = STOP;
bool ledState = false;
bool pulState = false;
int prevPulState;
bool flag;

int tiempo_activo = (47 + 10) / 10;
int tiempo_inactivo = (23 + 10) / 10;
int previousMillis = 0;
int intervalo = 500;
int mSeconds = 0;
int seconds = 0;

int lectura_sw;
int lectura_hum;
int lectura_pul;
float tension;

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(ISR_Timer);

  pinMode(LED_INDICADOR, OUTPUT);
  pinMode(LED_KEEP_ALIVE, OUTPUT);
  pinMode(BMB, OUTPUT);

  pinMode(HUM, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(PUL, INPUT_PULLUP);

  mSeconds = 0;
  seconds = 0;
  pulState = false;
}

void loop()
{
  int currentMillis = millis();

  lectura_pul = digitalRead(PUL);
  lectura_sw = digitalRead(SW);
  lectura_hum = analogRead(HUM);
  tension = lectura_hum * 5 / 1023;

  if (lectura_pul == LOW)
  {
    prevPulState = 1;
    pulState = !pulState;
  }
  if (lectura_pul == HIGH)
  {
    prevPulState = 0;
  }

  //Serial.print("prevPulState: ");
  //Serial.println(prevPulState);

  SwitchEstados();

  if (actualState != INIT)
  {
    if (currentMillis - previousMillis >= intervalo)
    {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_KEEP_ALIVE, ledState);
    }
  }
}

void ISR_Timer ()
{
  mSeconds++;
  if (mSeconds >= 1000)
  {
    mSeconds = 0;
    seconds++;
  }
}

void Modo1 ()
{
  digitalWrite(LED_INDICADOR, HIGH);

  switch (actualState)
  {
    case INIT:
      Serial.println("INIT 1");
      digitalWrite(BMB, HIGH);
      actualState = M1_BMB_ON;
      break;

    case M1_BMB_ON:
      Serial.println("Modo 1: Bomba ON");
      if (tension > 2, 5)
      {
        digitalWrite(BMB, LOW);
        actualState = M1_BMB_OFF;
      }
      break;

    case M1_BMB_OFF:
      Serial.println("Modo 1: Bomba OFF");
      if (tension < 2)
      {
        digitalWrite(BMB, HIGH);
        actualState = M1_BMB_ON;
      }
      break;
  }
}

void Modo2 ()
{
  switch (actualState)
  {
    case INIT:
      Serial.println("INIT 2");
      digitalWrite(BMB, HIGH);
      actualState = M2_BMB_ON;
      break;

    case M2_BMB_ON:
      Serial.println("Modo 2: Bomba ON");
      if (pulState == true && prevPulState == 0)
      {
        actualState = M2_STOP;
        digitalWrite(BMB, LOW);
        pulState = false;
      }
      if (seconds >= tiempo_activo)
      {
        digitalWrite(BMB, LOW);
        mSeconds = 0;
        seconds = 0;
        actualState = M2_BMB_OFF;
      }
      break;

    case M2_BMB_OFF:
      Serial.println("Modo 2: Bomba OFF");
      if (pulState == true && prevPulState == 0)
      {
        actualState = M2_STOP;
        digitalWrite(BMB, LOW);
        pulState = false;
      }
      if (seconds >= tiempo_inactivo)
      {
        digitalWrite(BMB, HIGH);
        mSeconds = 0;
        seconds = 0;
        actualState = M2_BMB_ON;
      }
      break;

    case M2_STOP:
      Serial.println("Modo 2: STOP");
      if (pulState == true && prevPulState == 0)
      {
        digitalWrite(BMB, HIGH);
        pulState = false;
        actualState = M2_BMB_ON;
      }
      break;
  }
}

void SwitchEstados ()
{
  switch (switchState)
  {
    case STOP:
      if (lectura_sw == 0)
      {
        switchState = MODO_1;
        actualState = INIT;
        Modo1();
      }
      else if (lectura_sw == 1)
      {
        switchState = MODO_2;
        actualState = INIT;
        Modo2();
      }
      break;

    case MODO_1:
      if (lectura_sw == 1)
      {
        switchState = MODO_2;
        actualState = INIT;
        Modo2();
      }
      Modo1();
      break;

    case MODO_2:
      if (lectura_sw == 0)
      {
        switchState = MODO_1;
        actualState = INIT;
        Modo1();
      }
      Modo2();
      break;
  }
}
