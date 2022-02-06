#include "zone.h"

//Note: Do not use pins 19, 18, 5 ,4 for triggers
zone::zone( int zoneselect, int triggers[], int triggersSize )
{
    if (triggersSize > SONAR_LIMIT || zoneselect > 3) //not a zone or incorrect number of MAX sensors
        return;
    currentzone = zoneselect;
    int i;

    for (i = 0; i < triggersSize; i++)
    {
        triggerPins[i] = triggers[i];
        pinMode( triggerPins[i], OUTPUT );
        digitalWrite( triggerPins[i], LOW );
    }
    numTriggers = triggersSize;
    lastUpdate = millis();
    enabled = true;
}

int zone::getSize()
{
    return numTriggers;
}

bool zone::isValid()
{
    return enabled;
}

bool zone::getData( long data[], int dataSize )
{
    if (dataSize != numTriggers || !enabled)
        return false;
    for (int i = 0; i < numTriggers; i++)
    {
        data[i] = datazone[i];
    }
    return true;
}

bool zone::updatezone() //only collects the next triggers data
{
    if (!enabled)
        return false;
    long currentUpdate = millis();
    if ((currentUpdate - lastUpdate < SONAR_SAMPLE_RATE)) //not enought time to resample
        return false;
    lastUpdate = currentUpdate; //reset soft clock

    //log last round of data
    switch (currentzone)
    {
    case 0:
        datazone[lastTrigger] = (long)((getZone(0)) * 0.034 / 2.0);
        break;
    case 1:
        datazone[lastTrigger] = (long)((getZone(1)) * 0.034 / 2.0);
        break;
    case 2:
        datazone[lastTrigger] = (long)((getZone(2)) * 0.034 / 2.0);
        break;
    case 3:
        datazone[lastTrigger] = (long)((getZone(3)) * 0.034 / 2.0);
        break;
    default: //should never reach
        return false;
    }

    //setup next round of data
    lastTrigger++;
    if (lastTrigger > numTriggers)
        lastTrigger = 0;

    digitalWrite( triggerPins[lastTrigger], HIGH );
    delayMicroseconds( 10 );
    digitalWrite( triggerPins[lastTrigger], LOW );
}
//end of zone class