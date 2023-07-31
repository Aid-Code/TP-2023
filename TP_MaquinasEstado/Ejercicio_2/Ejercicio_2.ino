#include "TimerOne.h"

// Definir componentes
#define LED 2
#define PUL_SERVIR 3
#define PUL_RETIRAR 4

// Definir estados
#define INIT 0
#define ESPERA 1
#define CORTO 2
#define LARGO 3
#define FINALIZO 4

String lectura;
int miliSeconds;
int seconds;

void setup() 
{
  Serial.begin(9600);

  pinMode(PUL_SERVIR, INPUT_PULLUP);
  pinMode(PUL_RETIRAR, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(ISR_Timer);
}

void loop() 
{
  
}

void ISR_Timer ()
{
  miliSeconds++;
  if (miliSeconds >= 1000)
  {
    miliSeconds = 0;
    seconds++;
  }
}
