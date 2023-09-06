#include "TimerOne.h"

#define PUL 3
#define LED 4

// Estados Baliza
#define LED_ON 0
#define LED_OFF 1
#define BALIZA_OFF 2

// Estados Antirrebote
#define ESPERA 0
#define LIBERACION 1
#define CONFIRMACION 2

bool flagPul_1;
int msPul_1;
int mSeconds;
int seconds;
int antirreboteState;
int balizaState;
int lecturaPul_1;

void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(ISR_Timer);
  

  pinMode(PUL, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  msPul_1 = 0;
  flagPul_1 = false;
}

void loop() 
{
  lecturaPul_1 = digitalRead(PUL);

  Serial.println(seconds);
  
  Antirrebote();
  Baliza();
}

void Baliza ()
{
  switch(balizaState)
  {
    case BALIZA_OFF:
      if (flagPul_1 == true)
      {
        seconds = 0;
        flagPul_1 = false;
        digitalWrite(LED, HIGH);
        balizaState = LED_ON;
      }
      break;

    case LED_ON:
      if (seconds >= 1)
      {
        seconds = 0;
        digitalWrite(LED, LOW);
        balizaState = LED_OFF;
      }

      if (flagPul_1 == true)
      {
        seconds = 0;
        flagPul_1 = false;
        digitalWrite(LED, LOW);
        balizaState = BALIZA_OFF;
      }
      break;

    case LED_OFF:
      if (seconds >= 1)
      {
        seconds = 0;
        digitalWrite(LED, HIGH);
        balizaState = LED_ON;
      }

      if (flagPul_1 == true)
      {
        seconds = 0;
        flagPul_1 = false;
        digitalWrite(LED, LOW);
        balizaState = BALIZA_OFF;
      }
  }
}

void Antirrebote ()
{
  switch(antirreboteState)
  {
    case ESPERA:
      if (lecturaPul_1 == LOW)
      {
        msPul_1 = 0;
        antirreboteState = CONFIRMACION;
      }
      break;

    case CONFIRMACION:
      if (lecturaPul_1 == HIGH && msPul_1 >= 15)
      {
        antirreboteState = ESPERA;
      }

      if (lecturaPul_1 == LOW && msPul_1 >= 15)
      {
        antirreboteState = LIBERACION;
      }
      break;

    case LIBERACION:
      if (lecturaPul_1 == HIGH)
      {
        flagPul_1 = true;
        antirreboteState = ESPERA;
      }
  }
}

void ISR_Timer ()
{
  msPul_1++;
  mSeconds++;
  if (mSeconds >= 1000)
  {
    mSeconds = 0;
    seconds++;
  }
}
