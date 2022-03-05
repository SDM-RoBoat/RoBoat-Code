/** ***************************************************************************
 * @file
 *
 * @brief   The implementation of the Sonar class
 *****************************************************************************/
#include "SonarSensor.h"



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* Sets up the sonar class. initialize the the setup array. Dissables 
* bound checking.
*
* @param[in] triggerPin - pin # for trigger
* @param[in] echoPin - pin # for echo
*
*****************************************************************************/
Sonar::Sonar( int triggerPin, int echoPin )
{
    pinMode(triggerPin, OUTPUT);
    pinMode( echoPin, INPUT );

    digitalWrite( triggerPin, LOW );
    digitalWrite( echoPin, LOW );
    
    Trigger = triggerPin;
    Echo = echoPin;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* sets up the sonar class. initialize the the setup array. Set the bounds and
* enable bound checking
*
* @param[in] triggerPin - pin # for trigger
* @param[in] echoPin - pin # for echo
* @param[in] lower_bound - lowwer cutoff for bound checking in cm
* @param[in] upper_Bound - Higer cutoff for bound checking in cm
*****************************************************************************/
Sonar::Sonar( int triggerPin, int echoPin, int lower_bound, int upper_Bound )
{


    pinMode( triggerPin, OUTPUT );
    pinMode( echoPin, INPUT );

    digitalWrite( triggerPin, LOW );
    digitalWrite( echoPin, LOW );

    Trigger = triggerPin;
    Echo = echoPin;

    setBound( lower_bound, upper_Bound )
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* This function reads the data from the senor once.
* 
* @param[in] distance - the messured value
* 
* @returns false if out of bounds
*
*****************************************************************************/
bool Sonar::getDistance( long& distance )
{
    long result;

    //pulse signal
    digitalWrite( Trigger, HIGH );
    delayMicroseconds( 10 );
    digitalWrite( Trigger, LOW );

    //read responce
    result = pulseIn( Echo, HIGH );
    //procces result
    result = (long)(result * 0.034 / 2.0);
    
    //bound checking
    distance = result;
    if (isValid( result ))
        return true;
    return false;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function will advrage "times" amound of colleted samples from getDistance()
* this is helps cut out nose that comes with the sonar sensor. It returns false
* if the value it returned in distance is out of the set bounds.
* 
* 
* @param[in] distance - return value from sensor (avg)
* @param[in] times - the number of collections that will be avraged
* 
* @returns false if avg is out of bounds
* @returns true if succesfull
* 
*****************************************************************************/
bool Sonar::getAvgDistance( long& distance, int times )
{
    //TODO: Add check for negative numbers in int times

    int i;
    long temp;
    long avg = 0;

    for (i = 0; i < times; i++)
    {
        getDistance(temp);
        avg += temp;
    }
    avg /= times;

    distance = avg;
    if (isValid( avg ))
        return true;
    return false;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this is a private function used for bound checking. It will return false if 
* out of bounds and true if in bounds or bound checking is disabled
*
* @param[in] distance - messured distance in cm
* 
* @returns false if out of bounds
* @returns true if valid or disabled bound checking
*
*****************************************************************************/
bool Sonar::isValid( long distance )
{
    //checks to see if bounds are inabled
    if (!bound_enable)
        return true;

    if (distance < lowerBound)
        return false;
    if (distance > upperBound)
        return false;
    return true;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function changes the range on the bounding and enables the bound checking
*
* @param[in] lower_bound - lower cutoff distance in cm
* @param[in] upper_bound - higher cutoff distance in cm
* 
* @returns false if bounds are invalid
*
*****************************************************************************/
bool Sonar::setBound( int lower_bound, int upper_bound )
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


/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
*   This function enable or dissables bound checking
* 
* @param[in] value - enable/dissable bound checking
*
*****************************************************************************/
void Sonar::useBound( bool value )
{
    bound_enable = value;
}