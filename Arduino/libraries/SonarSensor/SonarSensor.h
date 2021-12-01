#ifndef SONAR_SENSOR_H
#define SONAR_SENSOR_H

#include "Arduino.h"

class Sonar
{
    public:
        Sonar( int triggerPin, int echoPin );
        Sonar( int triggerPin, int echoPin, int lower_bound, int upper_Bound );
        bool getDistance( long& distance );
        bool getAvgDistance(long &distance, int times);
        bool setBound( int lower_bound, int upper_bound );
        void useBound(bool value);

    private:
        bool isValid( long distance );
        
        int Trigger;
        int Echo;

        bool bound_enable = false;
        int lowerBound = 2;
        int upperBound = 60;
};



#endif // !SONAR_SENSOR_H