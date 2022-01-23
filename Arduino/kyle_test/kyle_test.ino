#include <Stepper.h>
#define STEPS 2024
Stepper motor(STEPS, 9, 10, 11, 12);

void setup() {
  // put your setup code here, to run once:
  motor.setSpeed(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  motor.step(1024);
  delay(1000);
}
