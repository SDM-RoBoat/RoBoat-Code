#ifndef GPIOControler_h
#define GPIOControler_h

#include "../PinsDefintions.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

/* mraa headers */
//#include "mraa.h"
//#include "mraa/common.hpp"
//#include "mraa/pwm.hpp"

class PWMControl {
    public:
        PWMControl(int Pin);
        ~PWMControl();
        void set( float new_value); //between 0 & 255;
        void off();
        void on();
        bool state();
    private:
        bool status = false;
        float value = 0.0f;
        int pin;
        //mraa::Pwm* pwm;
};

class Pin {
    public:
        //ref: https://iotdk.intel.com/docs/master/mraa/java/gpio_8h.html
        enum dir
        {
            Out,
            In,
            Out_High,
            Out_Low
        };

        Pin(int pin, dir d);
        ~Pin();
        bool write( bool s );
        int read();
        double pulseIn();
    private:
        #define BILLION 1000000000L
        struct timespec btime, etime; __time_t i;
        //mraa::Gpio* pin;
        //mraa::Result status;
        dir D;
};

#endif // !GPIOControler_h
