#include "boatSonar.h"


BoatSonar::BoatSonar() {}

bool BoatSonar::setBound( int lower_bound, int upper_bound )
{
    if (lower_bound < 0)
        return false;
    if (lower_bound > upper_bound)
        return false;

    bound_enable = true;
    lowerBound = lower_bound;
    upperBound = upper_bound;
    return true;
}

void BoatSonar::useBound( bool value )
{
    bound_enable = value;
}

bool BoatSonar::initZone( boatZone bz, int triggerPin[], int numtriggerPins )
{
    if (numtriggerPins > SONAR_LIMIT)
        return false;

    if (Zones[bz] != nullptr)
    {
        delete Zones[bz];
        Zones[bz] = nullptr;
    }
    Zones[bz] = new zone( bz, triggerPin, numtriggerPins ); //mid is 0
    return true;
}

bool BoatSonar::getDistance( long distance[], int size, boatZone bz )
{
    return Zones[bz]->getData( distance, size );
}

void BoatSonar::updateBoatSonar()
{
    int i,j;
    int sizes[4] = { 0 };
    bool flag = false;
    //get the sizes
    for (i = 0; i < 4; i++)
    {
        if (Zones[i] != nullptr)
        {
            sizes[i] = Zones[i]->getSize();
        }
        else
        {
            sizes[i] = 0;
        }
    }

    for (j = 0; j < SONAR_LIMIT; j++)
    {
        for (i = 0; i < 4; i++)
        {
            if (sizes[i] != 0 && sizes[i]<j)
            {
                Zones[i]->updatezone();
                flag = true;
                delayMicroseconds( 5 );
            }
        }
        if (flag)
            delayMicroseconds( 1000 );
        flag = false;
    }
}
