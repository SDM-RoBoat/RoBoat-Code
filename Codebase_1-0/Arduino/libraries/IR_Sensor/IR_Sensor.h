/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the IR_Sensor class
 *****************************************************************************/
#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "arduino.h"



 /** ***************************************************************************
  * @brief
  * This IR_Sensor class takes one IR_sensor and makes it easy to use.
  *
  * @author  Kyle Houchin
  * @date    2/12/2022
  *****************************************************************************/
class IR_Sensor
{
public:
	IR_Sensor(int pin);
	IR_Sensor( int pin, int lower, int higher );
	bool Read( int& value );
	bool setThreshold( int lower, int higher );

private:
	int IRPin; //arduino pin
	bool enable_Threshold; //read() uses this
	int lower_threshold; //lower cutoff value in cm
	int upper_threshold; //upper cutoff value in cm
};

#endif // IRSENSOR_H
