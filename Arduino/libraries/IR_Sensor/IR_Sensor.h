#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "arduino.h"

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

#endif // IRSENSOR_H
