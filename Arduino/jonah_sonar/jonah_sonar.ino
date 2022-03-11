#include <SonarSensor.h>

const int SONAR_AMOUNT = 6;
const int avg_Amount = 3;

int triggerPins[SONAR_AMOUNT] = {29, 31, 33, 35, 37, 39};
int echoPins[SONAR_AMOUNT] = {38, 40, 42, 44, 46, 48};
long distances[SONAR_AMOUNT] = {};
int i;
int j = 0;

Sonar** mySonar = nullptr;

long avgDist[SONAR_AMOUNT] = {0};
void calcAvg(long avgDistances[]);
void makeZero(long avgDistances[]);

void setup() {
  
    Serial.begin(9600);
    
    mySonar = new Sonar*[SONAR_AMOUNT];
    
    for(i = 0; i < SONAR_AMOUNT; i++)
    {
      mySonar[i] = new Sonar(triggerPins[i], echoPins[i], 3, 100);
    }
   
}


void loop() {
  ////// CALCULATING AVERAGE ///////
  if(j >= avg_Amount) // 
  {
    calcAvg(avgDist);
    j = 0; // counter reset
  }


  /////// GETTING DISTANCES ////////
  for(i = 0; i < SONAR_AMOUNT; i++)
  {
    mySonar[i]->getDistance(distances[i]);
    avgDist[i] += distances[i];
  }

  j++;
  
}



void calcAvg(long avgDistances[])
{
   for(int i = 0; i < SONAR_AMOUNT; i++)
    {
      avgDistances[i] = avgDistances[i] / avg_Amount;
      Serial.print("Son");
      Serial.print(i + 1);
      Serial.print("Dist: ");
      Serial.print(avgDistances[i]);
      Serial.print("    ");
    }
    
    Serial.println();
    for(i = 0; i < SONAR_AMOUNT; i++)
      avgDistances[i] = 0;
}
