#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"

class Robot
{
    public:
        Robot( int leftMotor[], int rightMotor[], int size );
        bool left( int newSpeed );
        bool right( int newSpeed );
        bool forward( int newSpeed );
        void hult();
    private:
        int left_motor[3];
        int right_motor[3];
        void setMotor( int motor[], int newSpeed );
};

#endif