#include "TimerOne.h"

#define INIT 0
#define M1_BMB_ON 1
#define M1_BMB_OFF 2
#define M2_BMB_ON 3
#define M2_BMB_OFF 4

#define LED_INDICADOR 2
#define LED_KEEP_ALIVE 3
#define BMB 4
#define SW 5
#define HUM 6

int actualState = INIT;
int mSeconds;
int seconds;
int lectura_sw;
int lectura_hum;
int tiempo_activo = (23 + 10) / 10;
int tiempo_inactivo = (23 + 10) / 10;

float tension;

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(100);
  Timer1.attachInterrupt(ISR_Timer);

  pinMode(LED_INDICADOR, OUTPUT);
  pinMode(LED_KEEP_ALIVE, OUTPUT);
  pinMode(BMB, OUTPUT);

  pinMode(HUM, INPUT);
  pinMode(SW, INPUT);
}

void loop()
{
  lectura_sw = digitalRead(SW);
  lectura_hum = digitalRead(HUM);
  tension = lectura_hum * 5 / 1023;

  EstadosRegado();
  if (seconds >= 1)
  {
    digitalWrite(LED_KEEP_ALIVE, HIGH);
  }
  if (seconds >= 1)
  {
    digitalWrite(LED_KEEP_ALIVE, LOW);
  }
}

void ISR_Timer ()
{
  mSeconds++;
  if (mSeconds >= 1000)
  {
    seconds++;
  }
}

void EstadosRegado ()
{
  switch (actualState)
  {
    case INIT:
      digitalWrite(BMB, HIGH);
      actualState = M1_BMB_ON;
      break;

    case M1_BMB_ON:
      if (lectura_sw == 1)
      {
        digitalWrite(LED_INDICADOR, LOW);
        actualState = M2_BMB_ON;
      }
      else if (tension > 2,5)
      {
        digitalWrite(BMB, LOW);
        actualState = M1_BMB_OFF;
      }
      break;

    case M1_BMB_OFF:
      if (tension < 2)
      {
        digitalWrite(BMB, HIGH);
        actualState = M1_BMB_ON;
      }
      else if (lectura_sw == 1)
      {
        digitalWrite(LED_INDICADOR, LOW);
        digitalWrite(BMB, HIGH);
        actualState = M2_BMB_ON;
      }
      break;

    case M2_BMB_ON:
      if (seconds >= tiempo_activo)
      {
        digitalWrite(BMB, LOW);
        seconds = 0;
        actualState = M2_BMB_OFF;
      }
      else if (lectura_sw == 0)
      {
        digitalWrite(LED_INDICADOR, HIGH);
        actualState = M1_BMB_ON;
      }
      break;

    case M2_BMB_OFF:
      if (seconds >= tiempo_inactivo)
      {
        digitalWrite(BMB, HIGH);
        seconds = 0;
        actualState = M2_BMB_ON;
      }
      else if (lectura_sw == 0)
      {
        digitalWrite(LED_INDICADOR, HIGH);
        digitalWrite(BMB, HIGH);
        actualState = M1_BMB_ON;
      }
      break;
  }
}
