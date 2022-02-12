#include <boatSonar.h>
#include <interupts.h>
#include <zone.h>

//Note: Do not use pins 19, 18, 2 ,3 for triggers

BoatSonar myBoat();

int MIDtriggers[3] = {38, 52, 22};
int BACKtriggers[3] = {45, 47, 49);
int STARtriggers[2] = {42, 40};
int PORTtriggers[2]  = {36, 34};

long dataMID[3] = {0};
long dataBACK[3] = {0};
long dataSTAR[2] = {0};
long dataPORT[2] = {0};

void setup() {
  myBoat.initZone(BoatSonar::MID, MIDtriggers, 3);
  myBoat.initZone(BoatSonar::BACK, BACKtriggers, 3);
  myBoat.initZone(BoatSonar::STAR, STARtriggers, 2);
  myBoat.initZone(BoatSonar::PORT, PORTtriggers, 2);
  
}

void loop() {
  myBoat.updateBoatSonar();

  //I2c
  myBoat.getDistance(dataMID, 3, BoatSonar::MID);
  myBoat.getDistance(dataBACK, 3, BoatSonar::BACK);
  myBoat.getDistance(dataSTAR, 2, BoatSonar::STAR);
  myBoat.getDistance(dataPORT, 2, BoatSonar::PORT);
}
