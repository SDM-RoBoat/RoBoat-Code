#pragma once

class PID
{
	public:
		PID(int ki, int kp, int kd);
		~PID();
		int correct(int error);

	private:
		int sum_error = 0;
		int previous_error = 0;
		int previous_time = 0;
		int intagral = 0;
		int kp, ki, kd;
};

