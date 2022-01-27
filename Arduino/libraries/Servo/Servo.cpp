#include "Servo.h"

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

void Servo::setMode( mode m )
{
    curMode = m;
}

double Servo::convertAng( double step )
{
    if (curMode == half)
        return step * (360 / (revSteps/2.0));
    return step * (360 / revSteps);
}

double Servo::convertStep( double angle )
{
    if (curMode == half)
        return angle / (360 / (revSteps / 2.0));
    return angle / (360 / revSteps);
}

double Servo::getAng()
{
    return convertAng(currentSteps);
}

double Servo::getStep()
{
    return currentSteps;
}

void Servo::stepAng(double angle)
{
    step( convertStep( angle ) );
}

void Servo::step( double step )
{
    stepOnce( step );
}

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