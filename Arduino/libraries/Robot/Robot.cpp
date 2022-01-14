#include "robot.h"

Robot::Robot( int leftMotor[], int rightMotor[], int size )
{
    int i;
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
Robot::~Robot()
{
    delete left_motor;
    delete right_motor;
}


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

void Robot::hult()
{
    (*left_motor).setSpeed( 0 );
    (*right_motor).setSpeed( 0 );
}
