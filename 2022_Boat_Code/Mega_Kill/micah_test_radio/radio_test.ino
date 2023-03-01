#include <Radio.h>
int sig;
unsigned long duration;

Radio newRad;

void setup() {
  // put your setup code here, to run once:
  
  newRad.set(Throttle, 7);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sig = newRad.read(Throttle);
  Serial.println(sig);
}