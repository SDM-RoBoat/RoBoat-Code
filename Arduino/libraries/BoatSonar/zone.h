#ifndef ZONE_H
#define ZONE_H

#include "arduino.h"
#include "interupts.h"

#ifndef SONAR_LIMIT
#define SONAR_LIMIT 5
#endif // !SONAR_LIMIT

//zone class
#ifndef SONAR_SAMPLE_RATE
#define SONAR_SAMPLE_RATE 1000
#endif // !SONAR_SAMPLE_RATE

class zone
{
public:
    //Note: Do not use pins 19, 18, 5 ,4 for triggers
    zone( int zoneselect, int triggers[], int triggersSize );
    bool updatezone();
    bool getData( long data[], int dataSize );
    int getSize();
    bool isValid();
private:
    int currentzone;
    bool enabled = false;
    int triggerPins[SONAR_LIMIT] = { 0 };
    int numTriggers = 0;
    long datazone[SONAR_LIMIT] = { 0 };
    long lastUpdate;
    int lastTrigger = 0;
};


#endif // !ZONE_H
