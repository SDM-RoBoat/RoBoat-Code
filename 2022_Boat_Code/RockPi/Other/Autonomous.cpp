#include "Autonomous.h"

int State;
bool ExitState = false;
bool RadioState = true;

int autonomous( MotorControler Motors, Radio radio, Pin statePin ) {
    State = radio.read( Radio::channel::Gear );
    if (State != 2) {
        return -1;
    }

    while (!ExitState || RadioState) { //eather program done or lost radio connection
         
        //actual autonomous code




        State = radio.read( Radio::channel::Gear );
        if (State != 2) {

        }
    }

    if (!RadioState) {
        return -1;
    }
    return 0
}