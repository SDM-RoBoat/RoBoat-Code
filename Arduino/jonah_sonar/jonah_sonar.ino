#include <SonarSensor.h>

const int SONAR_AMOUNT = 2;

int triggerPins[SONAR_AMOUNT] = {2, 3};
int echoPins[SONAR_AMOUNT] = {40, 44};
long distances[SONAR_AMOUNT] = {};

int i;

Sonar** mySonar = nullptr;

void setup() {
  
    Serial.begin(9600);
    
    mySonar = new Sonar*[SONAR_AMOUNT];
    
    for(i = 0; i < SONAR_AMOUNT; i++)
    {
      mySonar[i] = new Sonar(triggerPins[i], echoPins[i]);
    }
   
}


void loop() {
  
  for(i = 0; i < SONAR_AMOUNT; i++)
    {
      mySonar[i]->getDistance(distances[i]);
    }

  Serial.print("Son1Dist: ");
  Serial.print(distances[0]);
  Serial.print("    Son2Dist: ");
  Serial.println(distances[1]);
//  Serial.print("    Son3Dist: ");
//  Serial.println(distances[2]);

}
