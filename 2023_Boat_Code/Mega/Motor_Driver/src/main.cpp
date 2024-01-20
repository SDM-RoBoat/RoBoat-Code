#include <Arduino.h>
#include <Servo.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>

byte motor_pin = 6;
Servo motor1;

ros::NodeHandle nh;


//publiusher
std_msgs::String str_msg;
ros::Publisher logger("log", &str_msg);

char default_msg[50] = "Enter PWM signal value 1100 to 1900, 1500 to stop";
char notvalid_msg[50] = "not valid";
char valid_msg[50] = "valid seting value";

//subsriber
std_msgs::Int16 Int16_msg;

int LeftMotorSetSpeed = 1500;

void MotorLeftControl(const std_msgs::Int16& Int16_msg) {
  LeftMotorSetSpeed = int(Int16_msg.data);
}

ros::Subscriber<std_msgs::Int16> motorLeft("MotorLeft", &MotorLeftControl);


void setup() {
  nh.initNode();
  nh.advertise(logger);

  motor1.attach(motor_pin);

	motor1.writeMicroseconds(1500); // send "stop" signal to ESC.

	delay(7000); // delay to allow the ESC to recognize the stopped signal
}

int incomingByte = 0;
int setSpeed = 0;
int LeftMotorSpeed= 1500;

void loop() {
  str_msg.data = default_msg;
  logger.publish(&str_msg);
  
  if (LeftMotorSetSpeed != LeftMotorSpeed) {
    if(LeftMotorSetSpeed < 1100 || LeftMotorSetSpeed > 1900)
    {
      str_msg.data = notvalid_msg; //not valid
      logger.publish(&str_msg);

      LeftMotorSetSpeed = LeftMotorSpeed; //set setSpeed so it ony processes once
    } 
    else
    {
      str_msg.data = valid_msg; //valid
      logger.publish(&str_msg);

      LeftMotorSpeed = LeftMotorSetSpeed;
      motor1.writeMicroseconds(LeftMotorSpeed);
    }
  }

  nh.spinOnce();
  delay(1);
}