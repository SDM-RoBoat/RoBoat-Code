#include "boatSonar.h"

//Note: Do not use pins 19, 18, 5 ,4 for triggers
int triggersZone0[3] = {22,23,24};
int triggersZone1[3] = {25,26,27};
int triggersZone2[3] = {28,29,30};
int triggersZone3[3] = {31,32,33};
zone zone0(0, triggersZone0, 3);
zone zone1(1, triggersZone1, 3);
zone zone2(2, triggersZone2, 3);
zone zone3(3, triggersZone3, 3);

void setup() {
  setInterupts();  
}

void loop() {
  zone0.updatezone();
  zone1.updatezone();
  zone2.updatezone();
  zone3.updatezone();

  
  
}
