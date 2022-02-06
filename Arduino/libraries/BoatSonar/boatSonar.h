#ifndef SONAR_SENSOR_H
#define SONAR_SENSOR_H

#ifndef SONAR_LIMIT
#define SONAR_LIMIT 5
#endif // !SONAR_LIMIT

#include "arduino.h"
#include "zone.h"

class BoatSonar
{
public:
    enum boatZone
    {
        MID,
        STAR,
        PORT,
        BACK
    };

    BoatSonar();
    bool setBound( int lower_bound, int upper_bound );
    void useBound( bool value );
    void updateBoatSonar();
    bool getDistance( long distance[], int size, boatZone bz ); //false if no zones have been declared
    bool initZone( boatZone bz, int triggerPin[], int numtriggerPins );

private:
    bool isValid( long distance );

    bool bound_enable = false;
    int lowerBound = 2;
    int upperBound = 60;

    zone* Zones[4] = { nullptr };
};
#endif // !SONAR_SENSOR_H