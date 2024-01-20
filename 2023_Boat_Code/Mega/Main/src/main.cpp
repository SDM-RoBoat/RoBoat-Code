//This code is for the Mega controling the Estop system

#include <Arduino.h>
#include <ros.h>

//----------------------------------------------------------------------------------------------------------------------------------------------------------
//gobal delarations

enum killLocation {
  KillPushBotton,
  EKill,
  RadioKill,
  killLocation_MAX
};

//----------------------------------------------------------------------------------------------------------------------------------------------------------
//function delarations

void killRelay(bool state);
void killSystem(killLocation loc, bool state);
bool checkKillButton();

//----------------------------------------------------------------------------------------------------------------------------------------------------------
//pin delarations

int killRelayPin = 2;
int killButtonPin = 3;

//----------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  pinMode(killRelayPin, OUTPUT);
  pinMode(killButtonPin, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  killSystem(KillPushBotton, checkKillButton());
  delay(10);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------

bool checkKillButton() {
  return !digitalRead(killButtonPin);
}


bool currentKillStates[killLocation_MAX] = {false};

void killSystem(killLocation loc, bool state) {
  currentKillStates[loc] = state;

  bool setKillState = false;
  for (int i=0; i<killLocation_MAX; i++) {
    if (currentKillStates[i]) {
      setKillState = true;
    } 
  }

  /*
    Note: this flips the setKillState
    this is due to human readable code
    for the kill system to be actavated or current kill to
    be true the relay pin needs to be set low/false
  */
  killRelay(!setKillState);
}

void killRelay(bool state) {
  digitalWrite(killRelayPin, state);
}