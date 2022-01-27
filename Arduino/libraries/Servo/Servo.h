#ifndef SERVO_H
#define SERVO_H

#include "arduino.h"

class Servo
{
    public:
        enum mode { wave, full, half };

        Servo(int pin1, int pin2, int pin3, int pin4);
        void setMode(mode m);
        void step(double step);
        void stepAng(double angle);
        double getAng();
        double getStep();

    private:
        const int revSteps = 4048;
        double currentSteps = 0;
        int cycle = 0; //there are 8 steps in a cycle. 
        int delayTimeMirco = 2;

        int pins[4] = { 0 };
        mode curMode = full;

        double convertAng( double step );
        double convertStep( double angle );

        void stepOnce();
        void stepTwice();
        void capCycle();

        int waveVal[8][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
        int fullVal[8][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
        int halfVal[8][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
};

#endif // !SERVO_H
