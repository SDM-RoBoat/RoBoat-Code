#include "Servo.h"

/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this setsup servo class.
*
* @param[in] pin1 - servo pin 1;
* @param[in] pin2 - servo pin 2;
* @param[in] pin3 - servo pin 3;
* @param[in] pin4 - servo pin 4;
*
*****************************************************************************/
Servo::Servo( int pin1, int pin2, int pin3, int pin4 )
{
    pins[0] = pin1;
    pins[1] = pin2;
    pins[2] = pin3;
    pins[3] = pin4;

    for (int i = 0; i < 4; i++)
    {
        pinMode( pins[i], OUTPUT );
    }
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets the servo mode
*
* @param[in] m - FULL, WAVE, HALF
*
*****************************************************************************/
void Servo::setMode( mode m )
{
    curMode = m;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function converts the setp into an angle. private function.
*
* @param[in] step - new speed for robot -255 to 255
*
* @returns return angle
*
*****************************************************************************/
double Servo::convertAng( double step )
{
    if (curMode == half)
        return step * (360 / (revSteps/2.0));
    return step * (360 / revSteps);
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* continue after here
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
* @returns false if it failed
*
*****************************************************************************/
double Servo::convertStep( double angle )
{
    if (curMode == half)
        return angle / (360 / (revSteps / 2.0));
    return angle / (360 / revSteps);
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
* @returns false if it failed
*
*****************************************************************************/
double Servo::getAng()
{
    return convertAng(currentSteps);
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
* @returns false if it failed
*
*****************************************************************************/
double Servo::getStep()
{
    return currentSteps;
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
* @returns false if it failed
*
*****************************************************************************/
void Servo::stepAng(double angle)
{
    step( convertStep( angle ) );
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
* @returns false if it failed
*
*****************************************************************************/
void Servo::step( double step ) //need to code
{
    if (floor( step ) != step)
        return;

    int i;
    for (i = 0; i < step; i++)
    {
        if (mode == full)
        {
            currentSteps += 2;
            stepTwice();
        }
        else
        {
            currentSteps++;
            stepOnce();
        }
    }
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
* @returns false if it failed
*
*****************************************************************************/
void Servo::stepOnce()
{
    cycle++;
    capCycle();
    for (int i = 0; i < 4; i++)
    {
        if (curMode == full)
        {
            digitalWrite( pins[i], fullVal[cycle][i] );
        }
        else if (curMode == half)
        {
            digitalWrite( pins[i], halfVal[cycle][i] );
        }
    }
    delayMicroseconds(delayTimeMirco);
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
* @returns false if it failed
*
*****************************************************************************/
void Servo::stepTwice()
{
    cycle += 2;
    capCycle();
    for (int i = 0; i < 4; i++)
    {
        digitalWrite( pins[i], waveVal[cycle][i] );
    }
    delayMicroseconds( delayTimeMirco );
}



/** ***************************************************************************
* @author Kyle Houchin
*
* @par Description:
* this function sets both motors to the newSpeed.
*
* @param[in] newSpeed - new speed for robot -255 to 255
*
* @returns false if it failed
*
*****************************************************************************/
void Servo::capCycle()
{
    if (curMode == wave) // 0 2 4 6 Note:8 is out of scope
    {
        if (cycle < 0 || cycle == 8)
        {
            if (cycle < 0 )
            {
                cycle = 6;
            }
            else //at 8
            {
                cycle = 0;
            }
        }
    }
    else // 0 1 2 3 4 5 6 7 Note: 8 is out of scope
    {
        if (cycle == -1 || cycle == 8)
        {
            if(cycle == -1)
            {
                cycle = 7;
            }
            else //at 8
            {
                cycle = 0;
            }
        }
    }
}