#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>

#include "ArduinoHardware.h" 
#include <ros.h>

  //Arduino

#include <Servo.h>
#include <avr/wdt.h> //for system kill
#include "relay.h"
#include "radio.h"

  //Ros

#include <custom_msg/motor_speed.h>
#include <custom_msg/radio.h>
#include <std_msgs/Bool.h>
//Constants

//ros stuff
  const byte MAX_SUBSCRIBERS = 2;
  const byte MAX_PUBLISHERS = 4;
  const byte INPUT_SIZE = 128; //num of bytes recived
  const byte OUTPUT_SIZE = 160; //num of bytes sent


  extern ros::NodeHandle_<ArduinoHardware, MAX_SUBSCRIBERS, MAX_PUBLISHERS, INPUT_SIZE, OUTPUT_SIZE> nh;

//Arduino

//Pin deffintions
  const uint8_t LEFT_MOTOR_PIN = 6;
  const uint8_t RIGHT_MOTOR_PIN = 9;
  const uint8_t KILL_RELAY_PIN = 5; 
  const uint8_t HARD_KILL_PIN = 10;

  const uint8_t GEAR_PIN = 3;
  const uint8_t AILERON_PIN = 20;
  const uint8_t THROTTLE_PIN = 21;

//motor speed deffintions
  const int MOTOR_STOP = 1500;
  const int MIN_SPEED = 1100;
  const int MAX_SPEED = 1900;

//servo info
  const int maxServoAttachAttempts = 5;
  const int servoAttachDelayTime = 2000;


enum motor_side {
    Left,
    Right
};

  //radio gear parssing
    //for gear segmentation: used for parsing lever states

    const int GEAR_BASELINE = 1100;
    const int GEAR_ELEVDR_OFFSET = 100;
    const int GEAR_FLAP_OFFSET = 200;
    //note: Anything bigger than 1400 is automaticly placed in flap

    const int TOTAL_GEAR_OPTIONS_STATES = 4;

    struct GearValues {
        bool Gear = false;
        bool ElevD_R = false;
        bool Flap = false;
    };

    const int GEAR_OPTIONS_VALUES[] = {
        GEAR_BASELINE, //1100 (actual value: 1070)
        GEAR_BASELINE+GEAR_ELEVDR_OFFSET, //1200 (actual value: 1170)
        GEAR_BASELINE+GEAR_FLAP_OFFSET, //1300 (actual value: 1270)
        GEAR_BASELINE+GEAR_ELEVDR_OFFSET+GEAR_FLAP_OFFSET, //1400 (actual value: 1370)
        //anything bigger is flap + unknowen
    };

    const bool GEAR_OPTIONS[TOTAL_GEAR_OPTIONS_STATES+1][3] = {
      {0, 0, 0},
      {0, 0, 1},
      {0, 1, 0},
      {0, 1, 1},
      {1, 0, 0}
      //{Gear, FLAP, ELERD_R}
    };
  
  //radio throttle parssing (radio discconected or throttle cut hit)
    const int THROTTLE_KILL_VALUE = 1000; //ANY VALUE BELOW (892) WHEN BUTTON OR CONTROLER SIGNAL LOST
    
    struct ThrottleValues
    {
      int speed = 0; //default speed
      bool connected = false;
    };

#endif

