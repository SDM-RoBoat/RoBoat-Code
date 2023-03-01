/** ***************************************************************************
 * @file
 *
 * @brief   The implementation of the Robot class
 *****************************************************************************/
#include "robot.h"


 /** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * Sets up the robot class. initialize the the setup array.
 *
 * @param[in] leftMotor - 3 pins for left motor, 1 needs to be pwm
 * @param[in] rightMotor - 3 pins for right motor, 1 needs to be pwm
 * @param[in] size - number of items in left and right motor, needs to be 3.
 * 
 *****************************************************************************/
Robot::Robot( int leftMotor[], int rightMotor[], int size )
{
    if (size != 3)
    {
        return;
    }
    
    left_motor = nullptr;
    left_motor = new  Motor(leftMotor, size);
    if (left_motor == nullptr)
    {
        return;
    }

    right_motor = nullptr;
    right_motor = new Motor( rightMotor, size );
    if (right_motor == nullptr)
    {
        delete left_motor;
        return;
    }

}


/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* Destroctor for class
*
*****************************************************************************/
Robot::~Robot()
{
    delete left_motor;
    delete right_motor;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* Sets the left motor to newSpeed and sets right motor to 0.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
*****************************************************************************/
bool Robot::left( int newSpeed )
{
    if (newSpeed < -255 || newSpeed > 255)
    {
        return false;
    }
    (*left_motor).setSpeed( newSpeed );
    (*right_motor).setSpeed( 0 );

    return true;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* Sets the right motor to newSpeed and sets left motor to 0.
*
* @param[in] newSpeed - new speed for robot -255 to 255 
*
*****************************************************************************/
bool Robot::right( int newSpeed )
{
    if (newSpeed < -255 || newSpeed > 255)
    {
        return false;
    }
    (*right_motor).setSpeed( newSpeed );
    (*left_motor).setSpeed( 0 );
    return true;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
* 
* @returns false if it failed
*
*****************************************************************************/
bool Robot::forward( int newSpeed )
{
    if (newSpeed < -255 || newSpeed > 255)
    {
        return false;
    }
    (*left_motor).setSpeed( newSpeed );
    (*right_motor).setSpeed( newSpeed );
    return true;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* Stops the robot.
*
*****************************************************************************/
void Robot::hult()
{
    (*left_motor).setSpeed( 0 );
    (*right_motor).setSpeed( 0 );
}
