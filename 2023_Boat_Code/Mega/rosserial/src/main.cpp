/*
Things Done:

Ros conection
soft kill
hard kill
radio kill
set motor speeds
radio controler

Thgings to Do:
-post Hard kill to ros
-tempsensors intergration
-better logs
*/

//Includes ------------------------------------------------------

#include "main.h"

//Global Vars ---------------------------------------------------

bool motorEnable = false;
Servo* LeftMotor = nullptr;
Servo* RightMotor = nullptr;

int LeftMotorSpeed = MOTOR_STOP; //1500 is off for motors
int RightMotorSpeed = MOTOR_STOP; //1500 is off for motors

int LastLeftMotorSpeed = LeftMotorSpeed;
int LastRightMotorSpeed = RightMotorSpeed;

relay killRelay(KILL_RELAY_PIN);

bool hardKill = true;
bool radioKill = true;

Radio radio;

//function Decrations

//ros
void motorSpeedCallBack( const custom_msg::motor_speed& motor_speed_msg);
void softKillCallBack( const std_msgs::Bool &soft_kill_msg);

//arduino
void attachServo(motor_side side, const byte pin);
int boundMotor(int speed);
void updateMotorSpeed();

void hardKillCheck(byte pin, bool &killState);
void updateRadio(bool &radioKillState);

GearValues parseGear(int gearVal);

ThrottleValues parseThrottle(int throVal);

//Ros Stuff -----------------------------------------------------

// <MAX_Subscribers, MAX_Publishers, Input_Size, Output_Size>
ros::NodeHandle_<ArduinoHardware, MAX_SUBSCRIBERS, MAX_PUBLISHERS, INPUT_SIZE, OUTPUT_SIZE> nh;
  
  //Publishers
  custom_msg::radio radio_msg;
  ros::Publisher radioPub("radio", &radio_msg);

  //Subscrtibers
  ros::Subscriber<custom_msg::motor_speed> motorSpeeds("motorSpeeds", &motorSpeedCallBack);
  ros::Subscriber<std_msgs::Bool> softKill("soft_kill", &softKillCallBack);

//Setup ---------------------------------------------------------


void setup() {
  
  //ros setup
    nh.getHardware()->setBaud(250000);
    nh.initNode();
    nh.subscribe(motorSpeeds);
    nh.subscribe(softKill);
    nh.advertise(radioPub);

    nh.spinOnce();
  //arduino setup
    motorEnable = false;
    killRelay.dissable();

    nh.logwarn("Setting up Left Servo");
    attachServo(Left, LEFT_MOTOR_PIN);
    nh.logwarn("Setting up Right Servo"); 
    attachServo(Right, RIGHT_MOTOR_PIN);

    pinMode(HARD_KILL_PIN, INPUT_PULLUP);

    radio.set(Gear, GEAR_PIN);
    radio.set(Aile, AILERON_PIN);
    radio.set(Thro, THROTTLE_PIN);

    nh.logwarn("Arduino setup complete");

    nh.logwarn("Motors Soft_Kill Dissabled by default");

}

//Main loop -----------------------------------------------------

void loop() {
  //motor control handled in motorSpeedCallBack
  //soft kill implimtationsradioPub in softKillCallBack & updateMotorSpeed

  hardKillCheck(HARD_KILL_PIN, hardKill);
  updateRadio(radioKill);
  updateMotorSpeed();
  nh.spinOnce();
  delay(200);
}


void motorSpeedCallBack( const custom_msg::motor_speed& motor_speed_msg) 
{   
    LeftMotorSpeed = int(motor_speed_msg.leftMotor);
    RightMotorSpeed = int(motor_speed_msg.rightMotor);
}

//Arduino
int boundMotor(int speed) {
    return (speed < MIN_SPEED || speed > MAX_SPEED) ? MOTOR_STOP : speed;
}

void updateMotorSpeed() {
    String speed = "";
    //left
    if (LastLeftMotorSpeed != LeftMotorSpeed) {
      LastLeftMotorSpeed = boundMotor(LeftMotorSpeed);
      nh.logwarn("Left Motor Set to:");
      String speed = String(LastLeftMotorSpeed);
      nh.logwarn(speed.c_str());
    }

    //right
    if (LastRightMotorSpeed != RightMotorSpeed) {
      LastRightMotorSpeed = boundMotor(RightMotorSpeed);
      nh.logwarn("Right Motor Set to:");
      
      String speed = String(LastRightMotorSpeed);
      nh.logwarn(speed.c_str());
    }

    if(motorEnable && !hardKill && !radioKill) {
      killRelay.enable();
      RightMotor->writeMicroseconds(LastRightMotorSpeed);
      LeftMotor->writeMicroseconds(LastLeftMotorSpeed); 
    } else {
      killRelay.dissable();
      RightMotor->writeMicroseconds(MOTOR_STOP);
      LeftMotor->writeMicroseconds(MOTOR_STOP);
    }
}

//Servo inilization

void attachServo(motor_side side, const byte pin) {
    nh.logwarn("Setting up Servo");
    if (side==Left) {
        nh.logwarn("Left Servo");
        LeftMotor = new(Servo);
        LeftMotor->attach(pin);
        LeftMotor->writeMicroseconds(MOTOR_STOP);
        killRelay.dissable();
    } else if(side==Right) {
        nh.logwarn("Right Servo");
        RightMotor = new(Servo);
        RightMotor->attach(pin);
        RightMotor->writeMicroseconds(MOTOR_STOP);
        killRelay.dissable();
    }
    nh.logwarn("Servo Attached");
}


//Servo inilization


void softKillCallBack( const std_msgs::Bool &soft_kill_msg) 
{
    if (soft_kill_msg.data == false) { //Note: if soft_kill is enabled (true) then motors should be disabled
      nh.logwarn("Enabling Motors - softKill");
      motorEnable = true;
    }
    else
    {
      nh.logwarn("Dissabling Motors - softKill");
      motorEnable = false;
    }
}

void hardKillCheck(byte pin, bool &killState) //note this is pulled low when connected to ground
{
  bool newState = digitalRead(pin);
  if (killState != newState) {
    killState = newState;
    nh.logwarn("HardKill State Changed (New State):");
    String state = String(newState);
    nh.logwarn(state.c_str());
    delay(100);
  }
}

void updateRadio(bool &radioKillState) 
{
  ThrottleValues curThroValues = parseThrottle(radio.read(Thro));
  radio_msg.Throttle = int16_t(curThroValues.speed);
  radio_msg.RadioConection = curThroValues.connected;

  radio_msg.Aileron = int16_t(radio.read(Aile));

  GearValues curGearValues = parseGear(radio.read(Gear));
  radio_msg.Gear = curGearValues.Gear;
  radio_msg.ElevdD_R = curGearValues.ElevD_R;
  radio_msg.Flap = curGearValues.Flap;
  radioPub.publish(&radio_msg);

  //change radioKill if needed
  if(!curThroValues.connected || curGearValues.Gear) {
    //radio Kill activated
    if (!radioKillState) {
      radioKillState = true;
      nh.logwarn("RadioKill State Changed (New State):");
      nh.logwarn("True");
      delay(100);
    }
  } else {
    //radio Kill deactivated
    if (radioKillState) {
      radioKillState = false;
      nh.logwarn("RadioKill State Changed (New State):");
      nh.logwarn("False");
      delay(100);
    }
  }
}

GearValues parseGear(int gearVal)
{
    GearValues acctivatedLevers;

    int curLeverState = 0;
    
    while(curLeverState<TOTAL_GEAR_OPTIONS_STATES && gearVal > GEAR_OPTIONS_VALUES[curLeverState]) 
    { 
      curLeverState++;
    }

    if (GEAR_OPTIONS[curLeverState][2]) {
      acctivatedLevers.ElevD_R = true;
    }

    if (GEAR_OPTIONS[curLeverState][1]) {
      acctivatedLevers.Flap = true;
    }

    if (GEAR_OPTIONS[curLeverState][0]) {
      acctivatedLevers.Gear = true;
    }

    return acctivatedLevers;
}

ThrottleValues parseThrottle(int throVal) {
  ThrottleValues curVals;

  if (throVal<THROTTLE_KILL_VALUE) 
  {
    curVals.connected = false;
  }
  else{
    curVals.connected = true;
  }

  curVals.speed = throVal;

  return curVals;
}