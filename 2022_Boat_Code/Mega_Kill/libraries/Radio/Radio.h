/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the radio class
 *****************************************************************************/


#ifndef Radio_H
#define Radio_H

#include "Arduino.h"
#include <math.h>



/** ***************************************************************************
 * @brief   A set of functions to read in data from a Spektrum AR610 6CH 
 * reciver
 *
 * @author  Micah Healy
 * @date    01/26/2022
 *****************************************************************************/
class Radio
{
public:

    enum channel { Throttle, Aileron, Elevator, Rudder, Gear, AUX1 }; //corralates to the channel on the reciver

    Radio();
    Radio(int setup[][2], int size);

    int set(channel Channel, int pin);
    int read(channel Channel);
    void setScale(int new_scale);

private:
    int low = 1181;     //MEASURED LOW VALUE FOR MOST OUTPUTS
    int zero = 1490;    //MEASURED ZERO VALUE
    int high = 1795;    //MEASURED HIGH VALUE
    int pin_low = 1100;
    int pin_mid = zero;
    int pin_high = 1900;
    int input_setup[6]; //pins for a given channel
    int scale = 255; //the scale for outputing analog value

    int readJoystick(int pin);
    int readThrottle(int pin);
    int readSwitch(int pin);
};

#endif