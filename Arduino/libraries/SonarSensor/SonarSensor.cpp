#include "SonarSensor.h"

Sonar::Sonar( int triggerPin, int echoPin )
{
    pinMode(triggerPin, OUTPUT);
    pinMode( echoPin, INPUT );

    Trigger = triggerPin;
    Echo = echoPin;
}

Sonar::Sonar( int triggerPin, int echoPin, int lower_bound, int upper_Bound )
{
    pinMode( triggerPin, OUTPUT );
    pinMode( echoPin, INPUT );

    Trigger = triggerPin;
    Echo = echoPin;

    if (!setBound( lower_bound, upper_Bound ))
    {
        Serial.begin( 9600 );
        Serial.println("Invalid Bounds! ");
        Serial.print("Trigger: ");
        Serial.print( triggerPin );
        Serial.print( "  Echo: " );
        Serial.println( echoPin );
    }
}

bool Sonar::getDistance( long& distance )
{
    long result;

    digitalWrite( Trigger, LOW );
    delayMicroseconds( 1000 );

    //pulse signal
    digitalWrite( Trigger, HIGH );
    delayMicroseconds( 10 );
    digitalWrite( Trigger, LOW );

    //read responce
    result = pulseIn( Echo, HIGH );
    //procces result
    result = result * 0.034 / 2;

    distance = result;
    if (isValid( result ))
        return true;
    return false;
}

bool Sonar::getAvgDistance( long& distance, int times )
{
    //TODO: Add check for negative numbers in int times

    int i;
    long temp;
    long avg = 0;

    for (i = 0; i < times; i++)
    {
        getDistance(temp);
        avg += temp;
    }
    avg /= times;

    distance = avg;
    if (isValid( avg ))
        return true;
    return false;
}

bool Sonar::isValid( long distance )
{
    //checks to see if bounds are inabled
    if (!bound_enable)
        return true;

    if (distance < lowerBound)
        return false;
    if (distance > upperBound)
        return false;
    return true;
}

bool Sonar::setBound( int lower_bound, int upper_bound )
{
    if (lower_bound < 0)
        return false;
    if (lower_bound > upper_bound)
        return false;

    bound_enable = true;
    lowerBound = lower_bound;
    upperBound = upper_bound;
    return true;
}

void Sonar::useBound( bool value )
{
    bound_enable = value;
}