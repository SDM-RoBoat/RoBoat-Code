/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the BoatSonar class
 *****************************************************************************/

#ifndef SONAR_SENSOR_H
#define SONAR_SENSOR_H



 /** ***************************************************************************
 * @brief   Total number of defualt sonars
 *****************************************************************************/
#ifndef SONAR_LIMIT
#define SONAR_LIMIT 5
#endif // !SONAR_LIMIT

#include "arduino.h"
#include "zone.h"


 /** ***************************************************************************
  * @brief   
  * This class is the class intened to be used with the arduino code. 
  * 
  * @par
  * Here is an exaple of the implemetation
  * @verbatum
//(Optional)
#define SONAR_LIMIT 10; <-use this decloration before the include to change the 
default size of the sonars in each zone. Defualt is 5 Sonar Sensors in a zone.

//(Required)
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
  myBoat.updateBoatSonar(); //sets up collection for the getDistance() below.

  //other proccesing

  myBoat.getDistance(dataMID, 3, BoatSonar::MID);
  myBoat.getDistance(dataBACK, 3, BoatSonar::BACK);
}
 @verbatum
  *
  * @author  Kyle Houchin
  * @date    2/10/2022
  *****************************************************************************/
class BoatSonar
{
public:
    enum boatZone //to access out side the class use BoatSonar::<option>
    {
        MID, //echo pin 2
        STAR, //echo pin 3
        PORT, //echo pin 18
        BACK //echo pin 19
    };

    BoatSonar();
    bool setBound( int lower_bound, int upper_bound );
    void useBound( bool value );
    void updateBoatSonar();
    bool getDistance( long distance[], int size, boatZone bz ); //false if no zones have been declared
    bool initZone( boatZone bz, int triggerPin[], int numtriggerPins );

private:
    bool isValid( long distance );

    bool bound_enable = false; //this tells the isValid function wether to run or not
    int lowerBound = 2;        //close cut off distance in cm from sensor
    int upperBound = 60;       //far cut off distance in cm from sensor

    zone* Zones[4] = { nullptr }; //Holds the 4 zones in a array definded in the boatZone enum
};
#endif // !SONAR_SENSOR_H