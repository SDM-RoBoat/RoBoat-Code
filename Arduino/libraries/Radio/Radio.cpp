/** ***************************************************************************
 * @file
 *
 * @brief   The implementation of the radio class
 *****************************************************************************/

#include "Radio.h"

 /** ***************************************************************************
  * @author Micah Healy
  *
  * @par Description:
  * sets up the radio class. initialize the the setup array
  *
  *****************************************************************************/
Radio::Radio()
{
    //initilise setup
    for (int i = 0; i < 6; i++)
    {
        input_setup[i] = -1;
    }
}

/** ***************************************************************************
 * @author Micah Healy
 *
 * @par Description: 
 * sets up the radio class. initialize the the setup array 
 *
 * @param[in] setup[][2] - a 2D array containing pins to activate and the pins
 * to assign to them 
 * @param[in] size - the size to the first column
 * 
 *****************************************************************************/
Radio::Radio(int setup[][2], int size)
{
    //turn all pins to off state
    for (int i = 0; i < 6; i++)
        input_setup[i] = -1;

    //initilise setup
    for (int i = 0; i < size; i++)
    {
        int pin = setup[i][1];
        int channel = setup[i][0];
        //error checking
        if (pin > -1 && pin < 14)
        {
            //assignment
            input_setup[channel] = pin;
            pinMode(pin, INPUT);
        }
    }
}

/** ***************************************************************************
 * @author Micah Healy
 *
 * @par Description:
 * Checks inputs
 *
 * @param[in] channel - the channel to activate
 * @param[in] pin - the pin to assign to the channel
 *
 * @returns 0 - no error
 * @returns -1 - invalid pin
 * @returns -2 - invalid channel
 *
 *****************************************************************************/
int Radio::set(channel channel, int pin)
{
    //error checking
    if (pin < -1 || pin > 13)
        return -1;
    if (channel < 0 || channel > 5)
        return - 2;

    //setup pin
    if (pin != -1)
        pinMode(pin, INPUT);

    //asign in setup
    input_setup[channel] = pin;

    return 0;
}

/** ***************************************************************************
 * @author Micah Healy
 *
 * @par Description:
 * Using a given channel finds the pin number and reads the input using one of 
 * the three read functions
 *
 * @param[in] channel - the channel to read
 *
 * @returns The output from one of the read functions
 * @returns -100000 - channel has no pin set to it
 * @returns -100001 - channel values dosn't exist
 *
 *****************************************************************************/
int Radio::read(channel channel)
{
    int pin = input_setup[channel];

    if (pin == -1)
        return -100000;

    //determine channel type & read in data
    if (channel == Throttle)
        return (readThrottle(pin));
    else if (channel < Gear)
        return readJoystick(pin);
    else if (channel < 6) //switches
        return readSwitch(pin);
    else
        return -100001;
}

/** ***************************************************************************
 * @author Micah Healy
 *
 * @par Description:
 * Changes the scale that the joystick/throttle values are scale off.
 *
 * @param[in] new_scale - the scale to scale joystick/throttle values to
 *
 *****************************************************************************/
void Radio::setScale(int new_scale)
{
    scale = new_scale;
}

/** ***************************************************************************
 * @author Micah Healy
 *
 * @par Description:
 * Using a pin location reads in the duration of the pulse and outputs the
 * duration scaled from 0 to a set scale int the class
 *
 * @param[in] pin - the location that the reciver is connected
 *
 * @returns scale - a value between 0 and the scale representing the throttle 
 * position
 *
 *****************************************************************************/
int Radio::readThrottle(int pin)
{
    //read in data
    int duration = pulseIn(pin, HIGH);

    //translate to consistent scale
    int output = map(duration, 973, 1915, 0, scale);

    if (output > scale)
        return scale;
    return output;
}

/** ***************************************************************************
 * @author Micah Healy
 *
 * @par Description:
 * Using a pin location reads in the duration of the pulse and outputs the
 * duration scaled from -255 to 255 
 *
 * @param[in] pin - the location that the reciver is connected 
 *
 * @returns duration(mapped) - a value between the scale and -scale which 
 * represents the joystick position
 *
 *****************************************************************************/
int Radio::readJoystick(int pin)
{
    //read in data
    int duration = pulseIn(pin, HIGH);

    //translate to consistent scale
    return map(duration, low, high, -scale, scale);
}

/** ***************************************************************************
 * @author Micah Healy
 *
 * @par Description:
 * Using a pin number reads in the duration of the pulse and outputs the 
 * position the switch is in.
 *
 * @param[in] pin - the location that the reciver is connected 
 *
 * @returns 2 - low position
 * @returns 1 - mid position
 * @returns 0 - high position
 * @returns -256 - error
 *
 *****************************************************************************/
int Radio::readSwitch(int pin)
{
    //read in data
    int output = pulseIn(pin, HIGH);

    //translate to consistent scale
    if (abs(output - low) < 100)
        return 2;
    else if (abs(output - zero) < 100)
        return 1;
    else if (abs(output - high) < 100)
        return 0;
    else
        return -256;
}

