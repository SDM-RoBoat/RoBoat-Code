#include <SonarSensor.h>
#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h"
BNO080 roboIMU;

typedef short int si;

const int SONAR_AMOUNT = 6;
const int avg_Amount = 3;

const char startSend = 'S';
const char endSend = 'E';

const si posIdent = 0;
const si sonarIdent = 1;

float angles[3] = {0};
int pos[3] = {0};
long distances[SONAR_AMOUNT] = {};

int triggerPins[SONAR_AMOUNT] = {29, 31, 33, 35, 37, 39};
int echoPins[SONAR_AMOUNT] = {38, 40, 42, 44, 46, 48};

int i;
int j = 0;

Sonar** mySonar = nullptr;

long avgDist[SONAR_AMOUNT] = {0};
void calcAvg(long avgDistances[]);
void makeZero(long avgDistances[]);
void sendPos(char startSend, char endSend, si identity,
             int pos[], float angles[]);
void sendSonar(char startSend, char endSend, si identity, long dist[], int sizeDist);

void setup() {
  
    Serial.begin(9600);
    
    mySonar = new Sonar*[SONAR_AMOUNT];
    
    for(i = 0; i < SONAR_AMOUNT; i++)
    {
      mySonar[i] = new Sonar(triggerPins[i], echoPins[i], 3, 100);
    }

    Wire.begin();

    if (roboIMU.begin() == false)
    {
      Serial.println("BNO080 not detected!");
      while (1)
        ;
    }

    Wire.setClock(400000);

    roboIMU.enableRotationVector(50);
   
}

//make the send's into one function.
void loop() {
  ////// CALCULATING AVERAGE ///////
  if(j >= avg_Amount) // 
  {
    calcAvg(avgDist);
    sendSonar(startSend, endSend, sonarIdent, distances, SONAR_AMOUNT);
    j = 0; // counter reset
  }


  /////// GETTING DISTANCES ////////
  for(i = 0; i < SONAR_AMOUNT; i++)
  {
    mySonar[i]->getDistance(distances[i]);
    avgDist[i] += distances[i];
  }

  j++;

  if(roboIMU.dataAvailable() == true)
  {
    float roll = (roboIMU.getRoll()) * 180.0 / PI; // Convert roll to degrees
    float pitch = (roboIMU.getPitch()) * 180.0 / PI; // Convert pitch to degrees
    float yaw = (roboIMU.getYaw()) * 180.0 / PI; // Convert yaw / heading to degrees
    
    angles[0] = roll;
    angles[1] = pitch;
    angles[2] = yaw;

    pos[0] = roboIMU.getRawAccelX();
    pos[1] = roboIMU.getRawAccelY();
    pos[2] = roboIMU.getRawAccelZ();
    
    Serial.print(roll, 1);
    Serial.print(F(","));
    Serial.print(pitch, 1);
    Serial.print(F(","));
    Serial.print(yaw, 1);

    Serial.println();

    sendPos(startSend, endSend, posIdent, pos, angles);
    
  }
  
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


void sendPos(char startSend, char endSend, si identity,
             int pos[], float angles[])
{
  int i;
  Serial.write(startSend);
  Serial.write(identity);
  
  for(i = 0; i < 3; i++)
    Serial.write(pos[i]);
  for(i = 0; i<3; i++)
    Serial.write(angles[i]);
    
  Serial.write(endSend);
}



void sendSonar(char startSend, char endSend, si identity, 
               long dist[], int sizeDist)
{
  int i;
  Serial.write(startSend);
  Serial.write(identity);
  Serial.write(sizeDist);

  for(i = 0; i< sizeDist; i++)
    Serial.write(dist[i]);

  Serial.write(endSend);
}
