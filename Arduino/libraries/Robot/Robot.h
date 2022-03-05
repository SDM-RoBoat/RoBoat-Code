/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the Robot class
 *****************************************************************************/
#ifndef ROBOT_H
#define ROBOT_H

#include "arduino.h"

#include "..\Motor\Motor.h"

 /** ***************************************************************************
  * @brief  A class for handling a simple robot with two motors. Uses the Motor
  * class.
  *
  * @author  Kyle Houchin
  * @date    02/14/2022
  *****************************************************************************/
class Robot
{
    public:
        Robot( int leftMotor[], int rightMotor[], int size );
        ~Robot();
        bool left( int newSpeed );
        bool right( int newSpeed );
        bool forward( int newSpeed );
        void hult();
    private:
        
        Motor* left_motor; //left motor class instance
        Motor* right_motor; //right motor class instance
};

#endif