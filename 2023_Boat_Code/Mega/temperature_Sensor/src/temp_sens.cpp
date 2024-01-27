#include "Temp_Sens.h"

Temp_Sens::Temp_Sens(byte pin) 
{
  PIN = pin;
  pinMode(PIN, INPUT);
}

float Temp_Sens::get_temp() {
  int a = analogRead(PIN);

  float R = 1023.0/a-1.0;
  R = R0*R;

  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet

  return temperature;
}