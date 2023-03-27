/*
 * This Code is for the Hard-Eletronic-Stop
 * When the panic button (AUX1) is pressed it will turn off
 * a relay that is hooked to the main relay cut off chain.
 * This will kill power to the relay that goes to mains power.
 * 
 * The arduino will also kill power if the reciver disconnects.
 * 
 * The arduino will reset if the panic button is clicked again.
 * 
 */


#include <Radio.h>
#define stop_channel Radio::AUX1

Radio receiver;
//used to store result from radio
int receiver_input;
int receiver_input_pin = 7;
int relay_kill_pin = 6;
bool is_stopped = false;

//time for signal issues with radio before preminate disconect
double dissconect_time = 0.5; //in sec
long dissconnect_time_milli = (long)dissconect_time*1000;


long last_connected_time;


void setup() {
  pinMode(relay_kill_pin, OUTPUT); //pinmode for Relay
  digitalWrite(relay_kill_pin, LOW); //off by defult

  Serial.begin(9600);

  Serial.println("Startup");

  
  //Makes sure the power to the main relay is cut if the radio did not get a valid pin
  if( receiver.set(stop_channel, receiver_input_pin)!= 0 )
  { 
    digitalWrite(relay_kill_pin, LOW);
    Serial.println("Bad pin and/or channel");
  }


  //waits till the controller connects
  while( receiver.read(stop_channel)!= 0 ) 
  { 
    digitalWrite(relay_kill_pin, LOW);
  }

  
  //radio connected
  //Give power to the main relay
  Serial.println("Detected reciver"); 
  digitalWrite(relay_kill_pin,HIGH);
}


void loop() {
  receiver_input = receiver.read(stop_channel);
  Serial.print("Input: ");
  Serial.println(receiver_input);

  // Pressed kill button or controller disconected
  if (receiver_input != 0 && is_stopped == false)  
  {
    Serial.println("Kill Button Pressed");
    digitalWrite(relay_kill_pin, LOW); 
    is_stopped = true; 
    delay(1000);  
  }  
  // Pressed the kill button while remote is disconected 
  else if (receiver_input == 2 && is_stopped) 
  {
      delay(250);
      
      // Makes sure the controller is conected and that the button was tapped and not held
      if (receiver.read(stop_channel) == 0) 
      {
        digitalWrite(relay_kill_pin, HIGH);
        is_stopped = false;
      }
  }
  else 
  {
    //shouldn't happen but may if the reciver is changed
    Serial.println("error unreached");
  }

}
