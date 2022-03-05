/** ***************************************************************************
 * @file
 *
 * @brief   Setup for the Sonar class
 *****************************************************************************/
#ifndef SERVO_H
#define SERVO_H

#include "arduino.h"

 /** ***************************************************************************
  * @brief   A class to control one sonar sensor
  *
  * @author  Kyle Houchin
  * @date    02/14/2022
  *****************************************************************************/
class Servo
{
    public:
        //wave: lest powerfull, biggest step
        //full: relable full steps, mid power, half step size as wave
        //half: most powerfull. slowest step
        enum mode { wave, full, half };

        Servo(int pin1, int pin2, int pin3, int pin4);
        void setMode(mode m);
        void step(double step);
        void stepAng(double angle);
        double getAng();
        double getStep();

    private:
        const int revSteps = 4048; //this is how many steps the servo has
        double currentSteps = 0; //count of internal posistion
        int cycle = 0; //there are 8 steps in a cycle.
        int delayTimeMirco = 2; //time between each step

        int pins[4] = { 0 }; //arduino pins for servo
        mode curMode = full; //stored time

        double convertAng( double step );
        double convertStep( double angle );

        void stepOnce();
        void stepTwice();
        void capCycle();


        //this holds the on/off controls for each mode for the servo per step
        int waveVal[8][4] = { {1,0,0,0}, {1,0,0,0}, {0,1,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,1,0}, {0,0,0,1}, {0,0,0,1} };
        int fullVal[8][4] = { {1,0,0,1}, {1,1,0,0}, {0,1,1,0}, {0,0,1,1}, {1,0,0,1}, {1,1,0,0}, {0,1,1,0}, {0,0,1,1} };
        int halfVal[8][4] = { {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0}, {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1} };
};

#endif // !SERVO_H
