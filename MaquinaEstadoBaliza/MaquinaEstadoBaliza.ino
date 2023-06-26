#include "TimerOne.h"

#define INIT 0
#define BALIZA_OFF 1
#define LED_ON 2
#define LED_OFF 3

#define TIEMPO_BALIZA 1000

#define PUL 3
#define LED 4

int estadoBaliza = INIT;
int mSegBaliza;


void setup() 
{
  Timer1.intitialize(1000);
  Timer1.attachinterrupt(ISR_Timer);
}

void loop() 
{
  maquinaEstadoBaliza();
}

void maquinaEstadoBaliza (void)
{
  lecturaPul = digitalRead(PUL);

  switch(estadoBaliza)
  {
   case INIT:
    digitalWrite(LED, LOW)
    estadoBaliza = BALIZA_OFF;
    break;

   case BALIZA_OFF:
    if (lecturaPul == LOW)
    {
      digitalWrite(LED, HIGH);
      mSegBaliza = 0;
      estadoBaliza = LED_ON;
    }
    break;

   case LED_ON:
    if (mSegBaliza >= TIEMPO_BALIZA)
    {
      digitalWrite(LED, LOW);
      mSegBaliza = 0;
      estadoBaliza = LED_OFF;
    }
    if (lecturaPul == LOW)
    {
      digitalWrite(LED, LOW);
      estadoBaliza = BALIZA_OFF;
    }
    break;

   case LED_OFF:
    if (mSegBaliza >= TIEMPO_BALIZA)
    {
      digitalWrite(LED, HIGH);
      mSegBaliza = 0;
      estadoBaliza = LED_ON;
    }
    if (lecturaPul == LOW)
    {
      digitalWrite(LED, LOW);
      estadoBaliza = BALIZA_OFF;
    }
  }
}
