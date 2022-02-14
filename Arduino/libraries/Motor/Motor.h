/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the Motor class
 *****************************************************************************/
#ifndef Motor_H
#define Motor_H

#include "arduino.h"

class Motor
{
    public:
        Motor( int newMotor[], int size );
        bool setSpeed( int newSpeed);
        void hult();
    
    private:
        int motor[3]; //holds the pins for the motor
        
};

#endif