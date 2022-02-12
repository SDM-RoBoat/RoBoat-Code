/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the zone class
 *****************************************************************************/

#ifndef ZONE_H
#define ZONE_H

#include "arduino.h"
#include "interupts.h"

 /** ***************************************************************************
  * @brief   Total number of defualt sonars
  *****************************************************************************/
#ifndef SONAR_LIMIT
#define SONAR_LIMIT 5 //# of trigger pins allowed per zone
#endif // !SONAR_LIMIT



/** ***************************************************************************
* @brief   Total number of defualt sonars
*****************************************************************************/
//zone class
#ifndef SONAR_SAMPLE_RATE
#define SONAR_SAMPLE_RATE 1000 //milliseconds
#endif // !SONAR_SAMPLE_RATE


/** ***************************************************************************
 * @brief
 * This zone class handles the data collection of any trigger pins it
 * is given
 * Note: Do not use pins 19, 18, 5 ,4 for triggers pins
 * The pins listed above are for echo pins only. They are the only avalable pins
 * for pin interupts.
 *
 * @author  Kyle Houchin
 * @date    2/10/2022
 *****************************************************************************/
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
    int currentzone;  //(0,1,2,3) <- this tells the class what echo pin to 
                      // collect data from
    bool enabled = false; //only false if setup failes
    int triggerPins[SONAR_LIMIT] = { 0 }; // array of trigger pins
    int numTriggers = 0; // number of triggers in triggerPins
    long datazone[SONAR_LIMIT] = { 0 }; //data storage for the zone
    long lastUpdate; //time in milliseconds
    int lastTrigger = 0; //this stores a index in triggerPins to tell it 
                         //what trigger pin to pulse next
};


#endif // !ZONE_H
