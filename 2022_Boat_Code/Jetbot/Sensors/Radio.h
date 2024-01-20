/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the radio class
 *****************************************************************************/


#ifndef Radio_H
#define Radio_H

#include "../Controlers/GPIOControler.h"
#include "../Other/Misc.h"
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
    struct pinsetup {
        int pin;
        channel c;
    };
    Radio();
    Radio( pinsetup setup[], int size );
    ~Radio();

    int set( pinsetup P );
    int read( channel Channel );
    void setScale( int new_scale );

private:
    Pin* Pins[6] = [nullptr];

    int low = 1181;     //MEASURED LOW VALUE FOR MOST OUTPUTS
    int zero = 1490;    //MEASURED ZERO VALUE
    int high = 1795;    //MEASURED HIGH VALUE
    int pin_low = 1100;
    int pin_mid = zero;
    int pin_high = 1900;
    int scale = 255; //the scale for outputing analog value

    int readThrottle();
    int readJoystick( channel Channel );
    int readSwitch( channel Channel );

};
#endif

