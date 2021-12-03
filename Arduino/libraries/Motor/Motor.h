#ifndef Motor_H
#define Motor_H

#include "Arduino.h"

class Motor
{
    public:
        Motor( int newMotor[], int size );
        bool setSpeed( int newSpeed);
        void hult();
    
    private:
        int motor[3];
        
};

#endif