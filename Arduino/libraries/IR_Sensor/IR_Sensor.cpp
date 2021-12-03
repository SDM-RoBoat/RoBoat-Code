#include "IR_Sensor.h"

IR_Sensor::IR_Sensor(int pin)
{
    if (pin < A0 || pin > A5)
    {
        Serial.begin( 9600 );
        Serial.println("IR_Sensor: Has an invlaid pin");
    }
    IRPin = pin;
}

int IR_Sensor::Read()
{
    if (!IRPin)
        return;
    return analogRead( IRPin );
}