#include "MotorControler.h"
#include "GPIOControler.h"

#include <math.h>

MotorControler::MotorControler( int Motor_Right, int Motor_Left ) {
    LMotor = new PWMControl(Motor_Left);
    RMotor = new PWMControl( Motor_Right );
    
    MLeft = 0.0f;
    LMotor->on();
    LMotor->set( MLeft );

    MRight = 0.0f;
    RMotor->on();
    RMotor->set( MRight );
}

MotorControler::~MotorControler()
{
    LMotor->off();
    RMotor->off();
}

bool MotorControler::SetDirection( float angle, float velocity ) {
    if angle > 90 {
        angle = 90;
    }
    else if (angle < -90) {
        angle = -90;
    }

    angle = (angle + 90)/2.0;
    float maxUnit = sqrt( 2 ) / 2.0;
    float R = sin( angle );
    float L = cos( angle );

    //bounding
    if velocity > 100 {
        velocity = 100;
    }
    else if (velocity < 0) {
        velocity = 0;
    }

    if (R > maxUnit) {
        R = maxUnit;
    }

    if (L > maxUnit) {
        L = maxUnit;
    }

    //interpulate from 0 - sqrt(2)/2 to 0 - 1
    L = maxUnit * L;
    R = maxUnit * R;

    //set velocity 0-(100-offset)
    L = L * velocity - offset;
    R = R * velocity - offset;

    if (L < 0) {
        L = 0;
    }
    if (R < 0) {
        R = 0;
    }

    setPWM( R, Right );
    setPWM( L, Left );
    return true;
}

void MotorControler::setPWM( float value = 0.0f, MotorSide side) {
    if (side==Right) {
        RMotor->set( value );
    } else {
        LMotor->set( value );
    }
}

void void MotorControler::hult()
{
    setPWM( 0.0f, Right );
    setPWM( 0.0f, Left );
}