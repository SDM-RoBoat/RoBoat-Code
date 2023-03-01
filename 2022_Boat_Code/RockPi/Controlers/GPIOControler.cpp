#include "GPIOControler.h"

//PWM Class/////////////////////////////////////////////////////////

PWMControl::PWMControl( int Pin )
{
    pin = Pin;
    if (pin = PWM0) {
        //pwm = new mraa::Pwm( 0 );
    }
    else if (pin = PWM1) {
        //pwm = new mraa::Pwm( 1 );
    }
}

void PWMControl::set( float new_value )
{
    value = new_value;
    if (status) {
        //pwm->write( value );
    }
}

void PWMControl::on()
{
    if (!status) {
        //pwm->enable( true );
    }
}

void PWMControl::off()
{
    if (status) {
        //pwm->enable( false );
    }
}

bool PWMControl::state()
{
    return status;
}

PWMControl::~PWMControl()
{
    set( 0.0f );
    off();
}

//Pin Class /////////////////////////////////////////////////////////

Pin::Pin( int pin, dir d) {
    //pin = new mraa::Gpio(pin);
    //status = pin.dir( d );
    //if (status != mraa::SUCCESS) {
        //Something is wrong do something
    //}
    D = d;
}

Pin::~Pin()
{
    //delete pin;
}

bool Pin::write( bool s )
{
    if (D == In) {
        return false
    }
    if (s) {
        //status = pin.write( 1 );
    } else {
        //status = pin.write( 0 );
    }
    //if (status != mraa::SUCCESS) {
        //Something is wrong do something
    //    return false
    //}
    return true
}

int Pin::read()
{
    if (D != In) {
        return -1;
    }
    //return pin.read();
    return 0;
}


//note function is blocking
double Pin::pulseIn()
{
    if (D != In) {
        return -1;
    }
    ////loop till pin is low
    //while (pin.read() != 0) {
    //    usleep( 100 );
    //}
    ////loop till pin is high
    //while (pin.read() != 1) {}
    //struct timespec bt; //before time
    //clock_gettime( CLOCK_REALTIME, &bt );
    //
    ////loop till pin is low
    //while (pin.read() != 0) {}
    //struct timespec ft; //after time
    //clock_gettime( CLOCK_REALTIME, &ft );

    //////find diffrence
    //double t = (double)((ft.tv_sec - bt.tv_sec) * BILLION) + (double)(ft.tv_nsec - bt.tv_nsec);
    //

    double t = 1;
    return t; //t in n seconds 
}
