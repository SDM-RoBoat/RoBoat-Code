#include <SonarSensor.h>

const int SONAR_AMOUNT = 6;

int triggerPins[SONAR_AMOUNT] = {29, 31, 33, 35, 37, 39};
int echoPins[SONAR_AMOUNT] = {38, 40, 42, 44, 46, 48};
long distances[SONAR_AMOUNT] = {};

int i;

Sonar** mySonar = nullptr;

void setup() {
  
    Serial.begin(9600);
    
    mySonar = new Sonar*[SONAR_AMOUNT];
    
    for(i = 0; i < SONAR_AMOUNT; i++)
    {
      mySonar[i] = new Sonar(triggerPins[i], echoPins[i], 3, 100);
    }
   
}


void loop() {

//  INDIVIDUALLY GETTING DISTANCES  
//
//  for(i = 0; i < SONAR_AMOUNT; i++)
//    {
//      mySonar[i]->getDistance(distances[i]);
//    }

// 
  getAvgDist(mySonar, distances, 5, SONAR_AMOUNT);
  
  Serial.print("Son1Dist: ");
  Serial.print(distances[0]);
  Serial.print("    Son2Dist: ");
  Serial.print(distances[1]);
  Serial.print("    Son3Dist: ");
  Serial.print(distances[2]);
  Serial.print("    Son4Dist: ");
  Serial.print(distances[3]);
  Serial.print("    Son5Dist: ");
  Serial.print(distances[4]);
  Serial.print("    Son6Dist: ");
  Serial.println(distances[5]);
}
