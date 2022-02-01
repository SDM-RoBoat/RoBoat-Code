/*This Code is for the Hard-Eletronic-Stop
 * When the button on AUX1 is pressed it will trun off
 * a relay that is hooked to the main relay cut off chain.
 * This will kill power to the relay that goes to mains power.
 * 
 * The arduino will not reset untill the E-Stop Circit is 
 * manually reset. 
 * 
 * Note: This is NOT the Soft-Stop!
 * This will require a full reboot of the boat
 */


#include <Radio.h>
#define Hard_Stop Radio::AUX1

Radio rad;

int StopPin = 1;
int relay = 2;



void setup() {
  pinMode(relay, OUTPUT); //enables relay
  
  if ( rad.set(Hard_Stop, StopPin)==0) 
  { //If radio pin is valid
    //Gives power to the main relay
    digitalWrite(relay,HIGH); 
  }
  else
  { //If the radio did not get a valid pin
    //Makes sure the power to the main relay is cut
    digitalWrite(relay, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!rad.read(Hard_Stop)||rad.read(Hard_Stop)==-256) // true or pressed .read return 0 on high 
  {
    digitalWrite(relay, LOW);    
  }
}
