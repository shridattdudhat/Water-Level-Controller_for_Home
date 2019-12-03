/*
  Water Level

  Automatic detects Water level of Tank and turn on and off motor according to it

  https://shridatt.github.io

  modified 27 Oct 2019 Diwali
  by Shridatt Dudhat

           _            _
           |         G  |  => H
           |            |
           |            |
           |         R  |  => L
           |            |
           |            |
           \_________B__/  => GND

  This code is in the public domain.

  http://shridattdudhat.github.io

*/

#define motor      12
#define GREEN       2
#define RED         3
#define buzzer     11
#define SW 7
#define statusLED  13
#define LEDG       A0
#define LEDR       A1
#define R           5
#define G           6
#define B           9

bool ledState = LOW;
bool motorFlag = HIGH;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
 /*Setting up the pinModes*/
  pinMode(statusLED, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);

  pinMode(GREEN, INPUT_PULLUP);
  pinMode(RED, INPUT_PULLUP);

  pinMode(SW, INPUT_PULLUP);

  pinMode(motor, OUTPUT);

  motorState(LOW); //Initially motor is off
  delay(5000);
  motorState(HIGH); // turn on motor after 5 seconds

  Serial.begin(9600);
}

void loop() {
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    if (ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }
    digitalWrite(LEDG, ledState);
  }

  int SW_state = digitalRead(SW);

  if (SW_state == 0)
  {
    manual();
  }
  else
  {
    automatic();
  }
}


void automatic()
{
  Serial.println("Automatic Mode !");
  int H = digitalRead(GREEN);
  int L = digitalRead(RED);
  if (L == 1 && H == 1)                     //Tank Empty
  {
    if(motorFlag == HIGH)
    {
    motorState(HIGH);                       //Motor is on
    }
    color(1, 0, 0);                         //RED
    Serial.print("Motor ON!");
  }
  else if (L == 0 && H == 0)                //Tank Full
  {
    motorFlag == LOW;
    motorState(LOW);                        //Motor is off
    alert();
    color(0, 0, 1);                         //BLUE
    Serial.print("Motor OFF!");
  }
  else                                      //Tank Half
  {
    color(0, 1, 0);                         //GREEN
  }
}


void manual()
{
  Serial.println("Manual Mode !");
  motorState(HIGH);                       // Motor is on
  color(1, 0, 0);
  delay(100);
  color(0, 1, 0);
  delay(100);
  color(0, 0, 1);
  delay(100);
}

void color(int red_value, int green_value, int blue_value)
{
  digitalWrite(R, !red_value);
  digitalWrite(G, !green_value);
  digitalWrite(B, !blue_value);
}

void alert()
{
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void motorState(bool x)
{
  digitalWrite(motor, !x);
}
