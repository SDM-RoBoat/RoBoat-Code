#include <SonarSensor.h>

const int SONAR_AMOUNT = 3;
const int TRIGGER_AMOUNT = 1;

int triggerPins[TRIGGER_AMOUNT] = {2};
int echoPins[SONAR_AMOUNT] = {40, 45, 50};
int distances[SONAR_AMOUNT] = {};

int i;

void setup() {
  
    Serial.begin(9600);
    
    Sonar** mySonar = nullptr;
    mySonar = new (nothrow) Sonar*[SONAR_AMOUNT];
    
    for(i = 0; i < SONAR_AMOUNT; i++)
    {
      mySonar[i] = new (nothrow) Sonar(triggerPins[i], echoPins[i]);
    }
   
}

bool start = true;

void loop() {
  
  for(i = 0; i < SONAR_AMOUNT; i++)
    {
      mySonar[i].getDistance(distances[i]);
    }

  Serial.print("Son1Dist: ");
  Serial.print(distances[0]);
  Serial.print("    Son2Dist: ");
  Serial.print(distances[1]);
  Serial.print("    Son3Dist: ");
  Serial.println(distances[2]);

  delay(20);
}
