#define PRT A0
#define POTE A1
#define LED_0 4
#define LED_1 5

void setup() 
{
  Serial.begin(9600);

  pinMode(PRT, INPUT);
  pinMode(POTE, INPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
}

void loop() 
{
  int lecturaAnalog_0;
  int lecturaAnalog_1;
  int tension_0;.
  int tension_1;

  lecturaAnalog_0 = analogRead(PRT);
  lecturaAnalog_1 = analogRead(POTE);

  tension_0 = lecturaAnalog_0 * 5 / 1023;
  tension_1 = lecturaAnalog_1 * 5 /1023;

  Serial.println(tension_0);
}
