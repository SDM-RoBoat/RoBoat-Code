#include "TelleOperated.h"
#include "../Controlers/MotorControler.h"
#include "../Sensors/Radio.h"

int TelleOp( MotorControler Motors, Radio radio )
{
    //Throttle, Aileron, Elevator, Rudder
    int PosT = radio.read( Radio::channel::Throttle );
    
    //choose one
    int PosA = radio.read( Radio::channel::Aileron );
    int PosE = radio.read( Radio::channel::Elevator );
    int PosR = radio.read( Radio::channel::Rudder );
    
    
    return 0;
}