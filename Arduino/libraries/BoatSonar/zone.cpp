/** ***************************************************************************
 * @file
 *
 * @brief   zone class function definitions
 *****************************************************************************/

#include "zone.h"

/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function sets up the zone class. It is used in the boatSonar class
 * This function checks to make sure the zoneselect and triggersSize are valid.
 * It then stores the pin # and set them up as OUTPUT and LOW (off).
 * It then stores the time and sets the zone class an active
 *
 * @param[in] zoneselect - selecting the zone, (0,1,2,3)
 * @param[in] triggers - a array that has the trigger pins # in it.
 * @param[in] triggersSize - this is how many items is in the triggers array
 *
 *****************************************************************************/
//Note: Do not use pins 19, 18, 5 ,4 for triggers
zone::zone( int zoneselect, int triggers[], int triggersSize )
{
    enabled = false; //makes sure this is set
    if (triggersSize > SONAR_LIMIT || zoneselect > 3) //not a zone or incorrect number of MAX sensors
        return;
    currentzone = zoneselect;

    for (int i = 0; i < triggersSize; i++)
    {
        triggerPins[i] = triggers[i];
        pinMode( triggerPins[i], OUTPUT );
        digitalWrite( triggerPins[i], HIGH );
    }
    numTriggers = triggersSize;
    lastUpdate = millis();
    enabled = true; //enables after everthing is proccesed
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 *  This function returns the number of triggers pins initiated
 * 
 * @returns the # of trigger pins
 *****************************************************************************/
int zone::getSize()
{
    return numTriggers;
}
 


/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 *  This function returns false if the class setup failed
 * 
 * @returns  if the function is enabled
 * 
 *****************************************************************************/
bool zone::isValid()
{
    return enabled;
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function checks to make sure the class is enabled and that there is 
 * enough space in data to store it. It then transfers the data held in the 
 * class.
 *
 * @param[in,out] data - a array to hold the returned data
 * @param[in] dataSize - number of elements in data array
 *
 * @returns false if it failed
 * 
 *****************************************************************************/
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


/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function will make sure that 1000 milliseconds have passed sence the
 * last time it was called. If 1000ms have passed it will retrive the data
 * from the last update. It will then trigger the next trigger pin and return true.
 * 
 * The Idea of function is pulse one trigger per update. This means if you have 5
 * trigger pins in this zone, updatezone() will need to be called 5 times to complete
 * the data collection for the zone. 
 * 
 * This allows the echo pins to have enough responce time to clear of nose and
 * resive the next signal. 
 * 
 * @returns false if the update failed
 *
 *****************************************************************************/
bool zone::updatezone() //only collects the next triggers data
{
    if (!enabled)
        return false;
    
    long currentUpdate = millis();

    if ((currentUpdate - lastUpdate < SONAR_SAMPLE_RATE)) //not enought time to resample
        return false;

    lastUpdate = currentUpdate; //reset soft clock

    //log last round of data
    datazone[lastTrigger] = (long)((getZone( currentzone )) * 0.034 / 2.0);

    //setup next round of data
    lastTrigger++;
    if (lastTrigger >= numTriggers)
        lastTrigger = 0;
    
    //noInterrupts();
    digitalWrite( triggerPins[lastTrigger], HIGH );
    delayMicroseconds(10);
    digitalWrite( triggerPins[lastTrigger], LOW );
    //interrupts();
    return true;

}
//end of zone class