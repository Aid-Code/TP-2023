#include "TimerOne.h"

#define INIT 0
#define STOPPED 1
#define RUNNING 2
#define PAUSED 3

#define pulStart 2
#define pulPause 3
#define pulStopp 4

void EstadoContador();
void ISR_Timer();

int actualState = INIT;
int miliSeconds;
int seconds;
int minutes;

int start;
int pause;
int stopp;

void setup()
{
  Serial.begin(9600);

  pinMode(pulStart, INPUT_PULLUP);
  pinMode(pulStopp, INPUT_PULLUP);
  pinMode(pulPause, INPUT_PULLUP);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(ISR_Timer);
}

void loop()
{
  start  = digitalRead(pulStart);
  pause = digitalRead(pulPause);
  stopp = digitalRead(pulStopp);

  EstadosContador();

  if (actualState == RUNNING)
  {
    Serial.print("Time: ");
    if (minutes < 10)
    {
      Serial.print("0");
    }
    Serial.print(minutes);
    Serial.print(":");
    if (seconds < 10)
    {
      Serial.print("0");
    }
    Serial.println(seconds);
  }
}

void EstadosContador ()
{
  switch (actualState)
  {
    case INIT:
      Serial.print("Time: ");
      Serial.print("0");
      Serial.print(minutes);
      Serial.print(":");
      Serial.print("0");
      Serial.println(seconds);
      seconds = 0;
      minutes = 0;
      actualState = STOPPED;
      break;

    case STOPPED:
      if (start == LOW)
      {
        miliSeconds = 0;
        seconds = 0;
        minutes = 0;
        actualState = RUNNING;
      }
      break;

    case RUNNING:
      if (pause == LOW)
      {
        actualState = PAUSED;
      }
      else if (stopp == LOW)
      {
        miliSeconds = 0;
        seconds = 0;
        minutes = 0;
        actualState = STOPPED;
        Serial.print("Time: ");
        Serial.print("0");
        Serial.print(minutes);
        Serial.print(":");
        Serial.print("0");
        Serial.println(seconds);
      }
      break;

    case PAUSED:
      //Serial.println("PAUSED");
      if (start == LOW)
      {
        actualState = RUNNING;
      }
      else if (stopp == LOW)
      {
        actualState = STOPPED;
      }
      break;
  }
}

void ISR_Timer ()
{
  miliSeconds++;
  if (miliSeconds >= 1000)
  {
    miliSeconds = 0;
    seconds++;
  }
  if (seconds >= 60)
  {
    seconds = 0;
    minutes++;
  }
}
