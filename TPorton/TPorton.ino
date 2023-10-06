#include "TimerOne.h"
#include <Servo.h>

Servo servo;

// Entradas y salidas
#define ENTRADA 2
#define SALIDA 3
#define LED_V 4
#define LED_R 5
#define SERVO 6

// Estados Antirrebote
#define ESPERA 0
#define LIBERACION 1
#define CONFIRMACION 2

// Estados Porton
#define ESPERA 0
#define ABIERTO 1
#define CERRADO 2

bool flagEntrada;
bool flagSalida;

int milis;
int seconds;
int msEntrada;
int msSalida;

int stateEntrada;
int stateSalida;
int statePorton;

int lecturaEntrada;
int lecturaSalida;

int abierto = 90;
int cerrado = 0;

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(ISR_Timer);

  servo.attach(SERVO);

  pinMode(ENTRADA, INPUT_PULLUP);
  pinMode(SALIDA, INPUT_PULLUP);
  pinMode(LED_V, OUTPUT);
  pinMode(LED_R, OUTPUT);
}

void loop()
{
  AntirreboteEntrada();
  AntirreboteSalida();
}

void Porton()
{
  switch (statePorton)
  {
    case CERRADO:
      if (flagEntrada == 1)
      {
        digitalWrite(LED_V, HIGH);
        digitalWrite(LED_R, LOW);
        servo.write(abierto);
        statePorton = ABIERTO;
      }
      break;

    case ABIERTO:
      if (flagEntrada == 0 && flagSalida == 0)
      {
        statePorton = ESPERA;
      }
      break;

    case ESPERA:
      if (flagSalida == 1 && flagEntrada == 0)
      {
        digitalWrite(LED_R, HIGH);
        digitalWrite(LED_V, LOW);
        servo.write(cerrado);
        statePorton = CERRADO;
      }
  }
}

void AntirreboteEntrada()
{
  switch (stateEntrada)
  {
    case ESPERA:
      if (lecturaEntrada == LOW)
      {
        msEntrada = 0;
        stateEntrada = CONFIRMACION;
      }
      break;

    case CONFIRMACION:
      if (lecturaEntrada == HIGH && msEntrada >= 15)
      {
        stateEntrada = ESPERA;
      }

      if (lecturaEntrada == LOW && msEntrada >= 15)
      {
        stateEntrada = LIBERACION;
      }
      break;

    case LIBERACION:
      if (lecturaEntrada == HIGH)
      {
        flagEntrada = true;
        stateEntrada = ESPERA;
      }
  }
}

void AntirreboteSalida()
{
  switch (stateSalida)
  {
    case ESPERA:
      if (lecturaSalida == LOW)
      {
        msSalida = 0;
        stateSalida = CONFIRMACION;
      }
      break;

    case CONFIRMACION:
      if (lecturaSalida == HIGH && msSalida >= 15)
      {
        stateSalida = ESPERA;
      }

      if (lecturaSalida == LOW && msSalida >= 15)
      {
        stateSalida = LIBERACION;
      }
      break;

    case LIBERACION:
      if (lecturaSalida == HIGH)
      {
        flagSalida = true;
        stateSalida = ESPERA;
      }
  }
}

void ISR_Timer()
{
  milis++;
  if (milis >= 1000)
  {
    milis = 0;
    seconds++;
  }
}
