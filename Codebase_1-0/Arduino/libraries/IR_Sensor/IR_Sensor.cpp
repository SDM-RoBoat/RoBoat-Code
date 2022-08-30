/** ***************************************************************************
 * @file
 *
 * @brief   IR_Sensor class function definitions
 *****************************************************************************/
#include "IR_Sensor.h"


 /** ***************************************************************************
  * @author Kyle Houchin
  *
  * @par Description:
  * This function sets up the IR_Sensor class
  * 
  * 
  * @param[in] pin - Arduino pin Sensor is hooked upto.
  *
  *****************************************************************************/
IR_Sensor::IR_Sensor(int pin)
{
    if (pin < A0 || pin > A5)
    {
        //Serial.begin( 9600 );
        //Serial.println("IR_Sensor: Has an invlaid pin");
    }
    IRPin = pin;

    pinMode( pin, INPUT );

    lower_threshold = 0;
    upper_threshold = 0;
    enable_Threshold = false;
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function setups up the class. It will also inable bound checking.
 * 
 * 
 * @param[in] pin - Arduino pin Sensor is hooked upto.
 * @param[in] lower - lowwer cutoff in cm
 * @param[in] higher - higger cutoff in cm
 *
 *****************************************************************************/
IR_Sensor::IR_Sensor( int pin, int lower, int higher )
{
    if (pin < A0 || pin > A5)
    {
        //Serial.begin( 9600 );
        //Serial.println( "IR_Sensor: Has an invlaid pin" );
    }
    IRPin = pin;
    lower_threshold = lower;
    upper_threshold = higher;
    enable_Threshold = true;
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function reads the sensor and then applys the bounding.
 * 
 * 
 * @param[out] value - returns the recorded vlaue
 *
 * @return false if out of bounds
 * @returns true if in bounds
 * 
 *****************************************************************************/
bool IR_Sensor::Read(int &value)
{
    if (!IRPin)
        return false;
    
    value = analogRead( IRPin );
    
    if (!enable_Threshold)
    {
        return true;
    }

    if (lower_threshold < value && upper_threshold < value)
    {
        return true;
    }
    return false;
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function sets the bounds to a value and enables it.
 * 
 * @param[in] lower - lower cutoff value in cm
 * @param[in] higher - higer cutoff value in cm
 * 
 * @returns false if invalid bounds
 *
 *****************************************************************************/
bool IR_Sensor::setThreshold( int lower, int higher )
{
    if (lower < 0 || lower > higher)
        return false;

    lower_threshold = lower;
    upper_threshold = higher;
    enable_Threshold = true;
    return true;
}
