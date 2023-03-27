/*
 * This program is used to check the output of a RC reciver 
 * if you want to check the raw output of the controller uncomment
 * the first lines in the setup and loop functions
 * if you want to see the output of the radio class uncomment 
 * the secound lines in those same functions.
*/

#include <Radio.h>

int sig;
unsigned long duration;

//to check diffrent pins or channels edit the variables below
#define channel Radio::AUX1
int pin = 7;


Radio newRad;

void setup() {
  //pinMode(pin, INPUT);    //raw reciver output
  newRad.set(channel, pin); //radio class output
  Serial.begin(9600);
}

void loop() {
  //sig = pulseIn(pin, HIGH); //raw reciver output
  sig = newRad.read(channel); //radio class output
  Serial.println(sig);
}
