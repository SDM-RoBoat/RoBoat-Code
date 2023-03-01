#include <PID.h>
#include <ctime>

PID::PID(int ki_in, int kp_in, int kd_in)
{
	ki = ki_in;
	kp = kp_in;
	kd = kd_in;
}

PID::~PID()
{
	
}

int PID::correct(int error)
{
	int current_time;
	int dt, de;
	int P, I, D;

	//time setup 
	if (previous_time == 0)
		previous_time = time(0);
	current_time = time(0);

	//P- Preportinal
	P = (kp / 10) * error;

	//I- Intagral
	dt = current_time - previous_time;
	intagral += (error * dt);
	if (intagral > 10)
		intagral = 10;
	else if (intagral < -10)
		intagral = -10;
	I = (ki / 10) * intagral;

	//D- Derivitive
	de = error - previous_error;
	D = (kd / 1000) * (de / dt);
	
	//store info
	previous_time = current_time;
	previous_error = error;
	sum_error += error;

	return P + I + D;
}
