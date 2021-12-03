#include "Motor.h"

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

void Motor::hult() 
{
    setSpeed( 0 );
}