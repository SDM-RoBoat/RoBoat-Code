#include "Controlers\PinsDefintions.h"
#include "Controlers\MotorControler.h"
#include "Sensors\Radio.h"
#include "PinsDefintions.h"
#include "Other\Autonomous.h"
#include "Other\TelleOperated.h"
#include "Other\Misc.h"
#include <ctime>


int main() {
//setup
     //Motor Set Up
     MotorControler Motors( PWM0, PWM1 ); //initilizes to motors off
    
     //Radio Set Up
     Radio::pinsetup newPins[5] = {
         {Radio::Throttle, GPIO2_A2},
         {Radio::Aileron, GPIO2_B0},
         {Radio::Elevator, GPIO2_B3},
         {Radio::Rudder, GPIO4_C4},
         {Radio::Gear, GPIO4_C3} //0 Telle, 1 Standby, 2 Auto
     };
     Radio radio( newPins, 5);

     //set up statePin for Led Stack
     Pin statePin( GPIO4_C2, Pin::dir::Out_Low );
     
     int State; //0 Telle, 1 Standby, 2 Auto
     bool ExitState = false;
     time_t* LastRadioConnectionTime = 0;
     time_t* CurrentTime;
     int timeout = 60; //60 seconds disconeted from controller

     //main loop
     while (!ExitState) {
         State = radio.read( Radio::channel::Gear ); //reads the gear signal from the radio controler
         time( &CurrentTime );
         switch (State)
         {
         case -1: //radio did not set up right
             ExitState = true; //exit program
             break;
         case 0: //Telle
             LastRadioConnectionTime = CurrentTime;
             statePin.write( false ); //trun on yellow signal stack
             int result = TelleOp( Motors, radio );
             if (result != 0) {
                 //handle error
             }

             break;
         case 1: //Standby
             LastRadioConnectionTime = CurrentTime;
             Motors.hult(); //just incase a motor is still running
             statePin.write( false ); //trun on yellow signal stack

             break;
         case 2: //Auto
             LastRadioConnectionTime = CurrentTime;
             Motors.hult(); //just incase a motor is still running
             statePin.write( true ); //trun on green signal stack

             int result = autonomous( Motors, radio, statePin );
             if (result != 0) {
                 //handle error
             }
             Motors.hult();
             statePin.write( false ); //trun on yellow signal stack

             break;
         default: //-1 controller not read properly
             if (LastRadioConnectionTime != 0) { //first Connection
                 //After First Connection
                 if (int(CurrentTime - LastRadioConnectionTime)>timeout) {
                     Motors.hult(); //just incase a motor is still running
                     statePin.write( false ); //trun on yellow signal stack
                 }
             }
             break;
         }
     }
     
     return 0;
}