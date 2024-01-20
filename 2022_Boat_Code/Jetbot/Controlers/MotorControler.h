#ifndef MotorControler_H
#define MotorControler_H

#include "GPIOControler.h"

class MotorControler {
    public:
        MotorControler( int Motor_Right, int Motor_Left ); //needs to be pwm pins
        ~MotorControler();
        bool SetDirection( float angle, float velocity ); //-90 to 90, 0-100
        void hult();
    private:
        enum MotorSide
        {
            Right,
            Left
        };

        float MRight; //Motor Right
        float MLeft; //Motor Left
        void setPWM( float value = 0.0f, MotorSide side ); //
        PWMControl* LMotor;
        PWMControl* RMotor;

        float offset = 20;
};

#endif //!MotorControler_H