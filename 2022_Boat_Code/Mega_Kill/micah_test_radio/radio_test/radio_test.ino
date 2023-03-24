#include <Radio.h>
int sig;
int chann = 4;
int pin = 7;
unsigned long duration;

Radio newRad;

void setup() {
  // put your setup code here, to run once:
  //pinMode(pin, INPUT);
  newRad.set(chann, pin);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //sig = pulseIn(pin, HIGH);
  sig = newRad.read(chann);
  Serial.println(sig);
}
