#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"
#include "Motor.h"

//For VS
// /*
#include "..\Motor\Motor.h"


// */
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
        
        Motor* left_motor;
        Motor* right_motor;
};

#endif