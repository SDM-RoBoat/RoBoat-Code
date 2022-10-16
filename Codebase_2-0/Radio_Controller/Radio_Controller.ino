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
int hult_pin = 13;
int speed_pin;     //ADD PIN NUMBER
int angle_pin;     //ADD PIN NUMBER
int input = 0;

double dissconect_time = 5; //in mins
long dissconnect_time_milli;
double hult_time = 0.5; //in mins
long hult_time_milli;
long last_connected_time;
bool hult_state = false;
bool is_ai = false;

void setup() {
  pinMode(relay, OUTPUT); //enables relay
  pinMode(hult_pin, OUTPUT); //enables relay
  digitalWrite(hult_pin, LOW);
  
  Serial.begin(9600);
  

  //Radio setup
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
  
  last_connected_time = millis();
  dissconnect_time_milli = (long)(dissconect_time*60*1000);
  hult_time_milli = (long)(hult_time*60*1000);
}



void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(rad.read(Hard_Stop));
  input = rad.read(Hard_Stop);
  //Serial.println(input);

  //Note: if radio gets disconneted the code does not do anything
  //TODO: need to be fixed!


  
  //E-Stop
  if (input!=0 && input!=-256) // true or pressed .read return 0 on high 
  {
    digitalWrite(relay, LOW);    
  }
  else if (input==-256) //disconnected
  { 
    //hult
    if (millis() - last_connected_time >= hult_time_milli)
    {
      hult_state = true;
      digitalWrite(hult_pin, HIGH);
    }
    //kill
    if (millis() - last_connected_time >= dissconnect_time_milli)
    {
      digitalWrite(relay, LOW);
    }
  }
  else if (hult_state && input==0)
  {
    hult_state = false;
    digitalWrite(hult_pin, LOW);
  }
  else
  {
    last_connected_time = millis();
  }



  //Detirmine mode
  if(input == 2)
    is_ai = true;
  else
    is_ai = false;

  //Read in data
  if (is_ai == false)
  {
    rad.read(Throttle, speed_pin);
    rad.read(Rudder, angle_pin);
  }
  else 
  {
    
  }

  //detirmine and write motor speeds
  
   
}
