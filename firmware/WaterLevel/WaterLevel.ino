/*
  Water Level Controller by Arduino

  Check the water level by the probe inserted in the tank

  This example code is in the public domain.

  http://shridatt.github.io
*/

#define motor 12 // motor drive pin
#define G 2 // green cable
#define R 3 // red cable
#define Y 4
#define buzzer 9 // buzzer pin
#define SW 7 // manual automatic switch


void setup() {

  // setting mode as input pullup to avoid any additional resistor requirments
  
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

  int SW_State = digitalRead(SW); //read the switch state

  if(SW_State == 1)
  {
    automatic(); // calling automatic function
  }

  else
  {
    manual(); // calling manual function
  }

}


void iniCheck()
{
  int L = digitalRead(G);
  int H = digitalRead(R);
  int M = digitalRead(Y);

  if(L == 0 && H == 1)
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
