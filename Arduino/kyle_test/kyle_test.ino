/*This Code is for the Hard-Eletronic-Stop
 * When the button on AUX1 is pressed it will trun off
 * a relay that is hooked to the main relay cut off chain.
 * This will kill power to the relay that goes to mains power.
 * 
 * The arduino will not reset untill the E-Stop Circit is 
 * manually reset. 
 * 
 * Note: This is NOT the Soft-Stop!


#include <Radio.h>
channel Hard_Stop = AUX1;


int StopPin = 1;
 * This will require a full reboot of the boat
 */
int relay = 2;

Radio radio();

void setup() {
  pinMode(relay, OUTPUT); //enables relay
  
  if ( radio.set(Hard_Stop, StopPin)==0) 
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
  if (!radio.read(Hard_Stop)||radio.read(Hard_Stop)==-256) // true or pressed .read return 0 on high 
  {
    digitalWrite(relay, LOW);    
  }
}
