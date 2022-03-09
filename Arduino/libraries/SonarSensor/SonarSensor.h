/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the Sonar class
 *****************************************************************************/
#ifndef SONAR_SENSOR_H
#define SONAR_SENSOR_H

#include "arduino.h"

 /** ***************************************************************************
  * @brief   A class to control one sonar sensor
  *
  * @author  Kyle Houchin
  * @date    02/14/2022
  *****************************************************************************/
class Sonar
{
    public:

        Sonar( int triggerPin, int echoPin );
        Sonar( int triggerPin, int echoPin, int lower_bound, int upper_Bound );
        bool getDistance( long& distance );
        bool getAvgDistance(long &distance, int times);
        bool setBound( int lower_bound, int upper_bound );
        void useBound(bool value);
        void getAvgDist(Sonar thisSonar[], long distances[], int n, int sonar_amount);

    private:

        bool isValid( long distance );
        
        int Trigger; //pin # on arduino
        int Echo; //pin # on arduino

        bool bound_enable = false; //use bounding
        int lowerBound = 2; //lowwer cutoff distance in cm
        int upperBound = 60; //high cutoff distance in cm
};


// Other sonar functions

#endif // !SONAR_SENSOR_H