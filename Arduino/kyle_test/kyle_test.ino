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

int StopPin = 7;
int relay = 6;
int input = 0;


void setup() {
pinMode(relay, OUTPUT); //enables relay

  Serial.begin(9600);
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
  //Serial.println(rad.read(Hard_Stop));
  input = rad.read(Hard_Stop);
  Serial.println(input);

  //Note: if radio gets disconneted the code does not do anything
  //TODO: need to be fixed!
  
  if (input!=0 && input!=-256) // true or pressed .read return 0 on high 
  {
    digitalWrite(relay, LOW);    
  }
}
