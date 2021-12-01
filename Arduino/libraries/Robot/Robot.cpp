#include "robot.h"

Robot::Robot( int leftMotor[], int rightMotor[], int size )
{
    int i;
    if (size != 3)
    {
        return;
    }

    for (i = 0; i < 3; i++)
    {
        pinMode( leftMotor[i], OUTPUT );
        left_motor[i] = leftMotor[i];
    }
    for (i = 0; i < 3; i++)
    {
        pinMode( rightMotor[i], OUTPUT );
        right_motor[i] = rightMotor[i];
    }
}


void Robot::setMotor( int motor[], int newSpeed )
{
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
    analogWrite( motor[0], abs(newSpeed) );
}

bool Robot::left( int newSpeed )
{
    if (newSpeed < -255 || newSpeed > 255)
    {
        return false;
    }
    setMotor( left_motor, newSpeed );
    setMotor( right_motor, 0);

    return true;
}

bool Robot::right( int newSpeed )
{
    if (newSpeed < -255 || newSpeed > 255)
    {
        return false;
    }
    setMotor( right_motor, newSpeed );
    setMotor( left_motor, 0 );
    return true;
}

bool Robot::forward( int newSpeed )
{
    if (newSpeed < -255 || newSpeed > 255)
    {
        return false;
    }
    setMotor( left_motor, newSpeed );
    setMotor( right_motor, newSpeed );
    return true;
}

void Robot::hult()
{
    setMotor( left_motor, 0 );
    setMotor( right_motor, 0 );
}
