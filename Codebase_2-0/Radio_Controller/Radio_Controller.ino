/************ INFO ***********
 * This Code is for the Hard-Eletronic-Stop
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


/******** SERIAL  COMM INFO FOR rasPi *************
 *  send packet as follows 
 *  
 *  255RL
 *  
 *  255 =  255 sent as a delimiter 
 *  R = a byte for the right motor speed (0-254)
 *  L = a byte for the left motor speed (0-254)
 */

/*********** OPERATING INSTRUCTIONS ************
 *  To actavate the E-STOP push the bind/panic/trainer button.
 *  Do not do this unless there is a safety issue and you want 
 *  to kill the run.
 *  
 *  The left joystick controls all movement. Use the flight  
 *  mode switch to change to Autonimus mode. It can also be 
 *  used as a soft stop 
 */

#include <Coordinates.h>
#include <Radio.h>
#define Hard_Stop Radio::AUX1
Radio rad;

/**************** PINOUT INFO *****************
 *  Using a AR610 reciver 
 *  
 *  Attach the AUX 1 data pin to pin 2 
 *  Attach the Gear data pin to pin 3
 *  Attach the THRO data pin to pin 11 
 *  Attach the RUDD data pin to pin 12
 *  Attach all the - pins together and attach to GND
 *  Attach all the + pins together and attach to 5V pin
 *  
 *  Attach the Relay for the E-STOP to pin 6 
 *  Attach the Relay for the Green light to pin 7
 *  Attach the Right motor controller to pin 9
 *  Attach the Left motor controller to pin 10
 *  Attach the AI computer to the USB port
 *  
 *  Attach the reset pin the a button that is attached to GND
 *  
 */
  
//pins
int StopPin = 2;
int modePin = 3;
int speed_pin = 11;
int turn_pin = 12;
int relay = 6;
int hult_pin = 7;
int l_motor_pin = 9;
int r_motor_pin = 10;

//thresholds
double dissconect_time = 5; //time till boat kills power (in mins)
long dissconnect_time_milli; 
double hult_time = 0.5; //time till boat soft stops (in mins)
long hult_time_milli;
long last_connected_time;

//states
bool is_ai = false;
bool soft_stop = false;

//genral values
int speed_value = 0;
int turn_value = 0;
int l_speed = 0;
int r_speed = 0;
int input = 0;


void setup() {
  pinMode(relay, OUTPUT); //enables relay
  pinMode(hult_pin, OUTPUT); //enables relay
  digitalWrite(hult_pin, LOW);
  
  Serial.begin(9600);

  Radio setup
  if ( rad.set(Hard_Stop, StopPin)==0) 
  { 
    //If radio pin is valid powers main relay
    digitalWrite(relay,HIGH); 
  }
  else
  { 
    //If the radio did not get a valid pin the main relay is cut
    digitalWrite(relay, LOW);
  }

  //makes sure E-STOP is checked constantally
  attachInterrupt(digitalPinToInterrupt(StopPin), eStop, CHANGE);

  //sets up dissconection thresholds
  last_connected_time = millis();
  dissconnect_time_milli = (long)(dissconect_time*60*1000);
  hult_time_milli = (long)(hult_time*60*1000);
}



void loop() {
  input = rad.read(Gear);
  
  //Detirmine mode from the flight mode switch
  if(input == 2)
    is_ai = true;
  else if(input == 1)
    is_ai = false;
  else
    soft_stop = true;

    
  //Read in data
  if (is_ai == false)
  {
    yellowLight();

    //read in speed from controller
    speed_value = rad.read(Throttle, speed_pin);
    turn_value = rad.read(Rudder, turn_pin);

    //convert to motor speeds
    r_speed = speed_value + turn_value;
    l_speed = speed_value - turn_value;

    //floor at zero
    if(r_speed < 0)
      r_speed = 0;
    if(l_speed < 0)
      l_speed = 0;
      
    //check soft stop
    if (soft_stop == true)
    {
      l_speed = 0;
      r_speed = 0;  
    }
  }
  else 
  {
    greenLight();
    
    noInterrupts();
    while(Serial.read() != 255);
    
    //read in speed from computer
    r_speed = Serial.read();
    l_speed = Serial.read();
    interrupts();
  }

  //write motor speeds
  analogWrite(l_motor_pin, l_speed);
  analogWrite(r_motor_pin, r_speed);
   
}



void greenLight() {
  digitalWrite(hult_pin, LOW);
}

void yellowLight() {
  digitalWrite(hult_pin, HIGH);
}

void kill() {
  digitalWrite(relay, LOW); 
}

void eStop(){
  //Note: if radio gets disconneted the code does not do anything NOT SURE IF THIS IS STILL TRUE
  //TODO: test and fix if needed
  input = rad.read(Hard_Stop);
  
  if (input!=0 && input!=-256) // true or pressed .read return 0 on high 
  {
    kill();   
  }
  else if (input==-256) //disconnected
  { 
    if (millis() - last_connected_time >= hult_time_milli)
    {
      soft_stop = true;
      yellowLight();
    }
    if (millis() - last_connected_time >= dissconnect_time_milli)
      kill();
  }
  else if (hult_state && input==0)
    //activate();
  else
    last_connected_time = millis();
}
