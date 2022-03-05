
#include <boatSonar.h>
#include <interupts.h>
#include <zone.h>

//Note: Do not use pins 19, 18, 2 ,3 for triggers

BoatSonar* myBoat;

//int MIDtriggers[2] = {40, 42};
int BACKtriggers[2] = {40, 42};
//int STARtriggers[2] = {42, 40};
//int PORTtriggers[2]  = {36, 34};

//long dataMID[2] = {0, 0};
long dataBACK[2] = {0};
//long dataSTAR[2] = {0};
//long dataPORT[2] = {0};



void setup() {
    Serial.begin(9600);

    myBoat = new BoatSonar();
   // myBoat->initZone(BoatSonar::MID, MIDtriggers, 2);
  myBoat->initZone(BoatSonar::BACK, BACKtriggers, 2);
//  myBoat->initZone(BoatSonar::STAR, STARtriggers, 2);
//  myBoat->initZone(BoatSonar::PORT, PORTtriggers, 2);
}

bool start = true;

void loop() {
  if(start)
  {
    delay(1000);
    start = !start;  
  }
  
    myBoat->updateBoatSonar();
//  I2c
//  we got pulse from zone.cpp updaate
    

  
 //   myBoat->getDistance(dataMID, 2, BoatSonar::MID);
  myBoat->getDistance(dataBACK, 2, BoatSonar::BACK);
//  myBoat->getDistance(dataSTAR, 2, BoatSonar::STAR);
//  myBoat->getDistance(dataPORT, 2, BoatSonar::PORT);
//    Serial.print("Son1Dist: ");
//    Serial.print(dataMID[0]);
//    Serial.print("       ");
//    Serial.print("Son2Dist: ");
//    Serial.println(dataMID[1]);
}
