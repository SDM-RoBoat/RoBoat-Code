#include "IR_Sensor.h"

IR_Sensor::IR_Sensor(int pin)
{
    if (pin < A0 || pin > A5)
    {
        //Serial.begin( 9600 );
        //Serial.println("IR_Sensor: Has an invlaid pin");
    }
    IRPin = pin;
    enable_Threshold = false;
}

IR_Sensor::IR_Sensor( int pin, int lower, int higher )
{
    if (pin < A0 || pin > A5)
    {
        //Serial.begin( 9600 );
        //Serial.println( "IR_Sensor: Has an invlaid pin" );
    }
    IRPin = pin;
    lower_threshold = lower;
    upper_threshold = higher;
    enable_Threshold = true;
}



bool IR_Sensor::Read(int &value)
{
    if (!IRPin)
        return false;
    value = analogRead( IRPin );
    if (!enable_Threshold)
    {
        return true;
    }

    if (lower_threshold < value && upper_threshold < value)
    {
        return true;
    }
    return false;
}

bool IR_Sensor::setThreshold( int lower, int higher )
{
    if (lower < 0 || lower > higher)
        return false;

    lower_threshold = lower;
    upper_threshold = higher;
    enable_Threshold = true;
    return true;
}
