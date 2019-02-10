/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#define motor 12
#define G 2
#define R 3
#define Y 4
#define buzzer 9
#define SW 7


void setup() {
  
  pinMode(G, INPUT_PULLUP);
  pinMode(R, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);

  pinMode(SW, INPUT_PULLUP);
  
  pinMode(motor, OUTPUT);
  
  digitalWrite(motor, HIGH);

  delay(3000);

  Serial.begin(9600);

}

void loop() {

  int SW_State = digitalRead(SW);

  if(SW_State == 1)
  {
    automatic();
  }

  else
  {
    manual();
  }

}


void automatic()
{
  int L = digitalRead(G);
  int H = digitalRead(R);
  int M = digitalRead(Y);

  if(L == 1 && H == 1)
  {
    digitalWrite(motor, LOW);
  }

  else if(L == 0 && H == 0)
  {
    digitalWrite(motor, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(13, HIGH);
  }

  delay(100);  
}


void manual()
{
  digitalWrite(motor, LOW);
}
