#ifndef IR_SENSOR.H
#define IR_SENSOR.H

#include "Arduino.h"

class IR_Sensor
{
public:
	IR_Sensor(int pin);
	IR_Sensor( int pin, int lower, int higher );
	bool Read( int& value );
	bool setThreshold( int lower, int higher );

private:
	int IRPin;
	bool enable_Threshold;
	int lower_threshold;
	int upper_threshold;
};

#endif // !IR_SENSOR.H
