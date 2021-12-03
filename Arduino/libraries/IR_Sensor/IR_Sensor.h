#ifndef IR_SENSOR.H
#define IR_SENSOR.H

#include "Arduino.h"

class IR_Sensor
{
public:
	IR_Sensor(int pin);
	int Read();

private:
	int IRPin;
};


#endif // !IR_SENSOR.H
