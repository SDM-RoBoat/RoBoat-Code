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
//used to store result from radio
int input = 0;


int RadioStopPin = 7;
int relay_KillPin = 6;

//time for signal issues with radio before preminate disconect
double dissconect_time = 0.5; //in sec
long dissconnect_time_milli = (long)dissconect_time*1000;


long last_connected_time;


void setup() {
  pinMode(relay_KillPin, OUTPUT); //pinmode for Relay
  digitalWrite(relay_KillPin, LOW); //off by defult

  Serial.begin(9600);

  Serial.println("Startup");
  
  
  while( rad.set(Hard_Stop, RadioStopPin)!=0 )
  { //If the radio did not get a valid pin
    //Makes sure the power to the main relay is cut
    digitalWrite(relay_KillPin, LOW);
  }

  Serial.println("Detected reciver");

  //radio connected
  //Give power to the main relay
  digitalWrite(relay_KillPin,HIGH);
  
  last_connected_time = millis();

  
}


void loop() {
  input = rad.read(Hard_Stop);
  Serial.print("Input: ");
  Serial.println(input);
  
  if (input!=0 && input!=-256) // Pressed kill button on radio
  {

    Serial.println("Kill Button Pressed");
    digitalWrite(relay_KillPin, LOW);    
  }
  else if (input==-256) //disconnected form radio breafly
  { 
    //kill (radio desconected to long)
    if (millis() - last_connected_time >= dissconnect_time_milli)
    {
      Serial.println("Time out");
      digitalWrite(relay_KillPin, LOW);
    }
    
  }
  else //kill not hit and still connected to radio
  {
    last_connected_time = millis();
  }
}
