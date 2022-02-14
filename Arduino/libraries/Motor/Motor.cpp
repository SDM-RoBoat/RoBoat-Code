/** ***************************************************************************
 * @file
 *
 * @brief   Motor class function definitions
 *****************************************************************************/
#include "Motor.h"

/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* This function will check to make sure that 3 pins are given and will then
* save then into the class and set there pinmode
*
* @param[in] newMotor - [PWM pin, A1, A2]
* @param[in] size - newMotor size
*
*****************************************************************************/
Motor::Motor( int newMotor[], int size )
{
    int i;
    if (size != 3)
    {
        return;
    }
    for (i = 0; i < 3; i++)
    {
        pinMode( newMotor[i], OUTPUT );
        motor[i] = newMotor[i];
    }
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This
 *
 *
 * @todo need to implement into data retrun
 *
 * @param[in] newSpeed - lower cutoff value in cm for sonar
 *
 * @returns true succesfull
 * @returns false invalid speed was given
 *
 *****************************************************************************/
bool Motor::setSpeed( int newSpeed )
{
    if (newSpeed < -255 || newSpeed > 255)
    {
        return false;
    }

    if (newSpeed < 0)
    {
        //back
        //sets direction
        digitalWrite( motor[1], HIGH ); //A1 or A3
        digitalWrite( motor[2], LOW );  //A2 or A4
    }
    else
    {
        //forward
        //sets direction
        digitalWrite( motor[1], LOW );
        digitalWrite( motor[2], HIGH );
    }
    analogWrite( motor[0], abs( newSpeed ) );
    
    return true;
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This function will take two bounds and save then to the class
 * it will then enable bound checking. will retrun -1 for invlaid disstances
 * in the getDistance( long distance[], int size, boatZone bz ), disstance
 * array. At the location of the sonar that had an invalid reading
 *
 * @todo need to implement into data retrun
 *
 * @param[in] lower_bound - lower cutoff value in cm for sonar
 * @param[in] upper_bound - cutoff value in cm for sonar
 *
 * @returns true succesfull
 * @returns false if bounds are invalid
 *
 *****************************************************************************/
void Motor::hult() 
{
    setSpeed( 0 );
}