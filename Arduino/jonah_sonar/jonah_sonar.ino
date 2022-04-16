#include <SonarSensor.h>
#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h"
BNO080 roboIMU;

typedef short int si;

const int SONAR_AMOUNT = 6;
const int avg_Amount = 3;

const char posIdent = 'p';
const char sonarIdent = 'i';

int pos3d[6] = {0};
long distances[SONAR_AMOUNT] = {};

int triggerPins[SONAR_AMOUNT] = {29, 31, 33, 35, 37, 39};
int echoPins[SONAR_AMOUNT] = {38, 40, 42, 44, 46, 48};

int i;
int j = 0;

Sonar** mySonar = nullptr;

long avgDist[SONAR_AMOUNT] = {0};
int avgDistInt[SONAR_AMOUNT] = {0};
void calcAvg( long avgDistances[] );
void makeZero( long avgDistances[] );
void sendData( char identity, int data[], int size );



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
      while (1);
    }

    Wire.setClock(400000);

    roboIMU.enableRotationVector(50);
    roboIMU.enableRawAccelerometer(50);
   
}



void loop() {
  ////// CALCULATING AVERAGE ///////
  if(j >= avg_Amount) // 
  {
    calcAvg(avgDist);
    
    // convert distances to regular ints.
    for(i = 0; i < SONAR_AMOUNT; i++)
      avgDistInt[i]  = (int)avgDist[i];

    // send data.
    sendData( sonarIdent, avgDistInt, SONAR_AMOUNT );
    
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
    float roll = ((roboIMU.getRoll()) * 180.0 / PI) * 1000; // Convert roll to degrees
    float pitch = ((roboIMU.getPitch()) * 180.0 / PI) * 1000; // Convert pitch to degrees
    float yaw = ((roboIMU.getYaw()) * 180.0 / PI) * 1000; // Convert yaw / heading to degrees
    

    pos3d[0] = (int)roboIMU.getRawAccelX();
    pos3d[1] = (int)roboIMU.getRawAccelY();
    pos3d[2] = (int)roboIMU.getRawAccelZ();
    pos3d[3] = (int)roll;
    pos3d[4] = (int)pitch;
    pos3d[5] = (int)yaw;

    Serial.println();

    // send data.
    sendData( posIdent, pos3d, 6 );
  }
}



void calcAvg(long avgDistances[])
{
   for(int i = 0; i < SONAR_AMOUNT; i++)
    {
      avgDistances[i] = avgDistances[i] / avg_Amount;
//      Serial.print("Son");
//      Serial.print(i + 1);
//      Serial.print("Dist: ");
//      Serial.print(avgDistances[i]);
//      Serial.print("    ");
    }
    
    Serial.println();
    
    for(i = 0; i < SONAR_AMOUNT; i++)
      avgDistances[i] = 0;
}



void sendData( char identity, int data[], int size )
{
  int i;
  Serial.print('S');
  Serial.print(" ");
  Serial.print(identity);
  Serial.print(" ");
  Serial.print(size);
  Serial.print(" ");
  for(i = 0; i < size; i++)
  {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  
  Serial.print(millis());
  Serial.print(" ");
  Serial.print('E');
  Serial.println();
}
