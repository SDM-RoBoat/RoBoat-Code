#include "boatSonar.h"

//Note: Do not use pins 19, 18, 5 ,4 for triggers

BoatSonar myBoat();

int MIDtriggers[3] = {6,7,8};
int BACKtriggers[2] = {40,41);

long dataMID[3] = {0};
long dataBACK[2] = {0};

void setup() {
  myBoat.initZone(BoatSonar::MID, MIDtriggers, 3);
  myBoat.initZone(BoatSonar::BACK, BACKtriggers, 2);
  
}

void loop() {
  myBoat.updateBoatSonar();

  //I2c

  myBoat.getDistance(dataMID, 3, BoatSonar::MID);
  myBoat.getDistance(dataBACK, 3, BoatSonar::BACK);
}
