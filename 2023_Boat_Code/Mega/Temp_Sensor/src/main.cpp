#include <Arduino.h>
#include <math.h>

#include <ros.h>
#include <std_msgs/Float32.h>

int B = 4275; // B value of the thermistor
float R0 = 100000; // R0 = 100k

float getTemp(int pin);
int tempPin1 = A0;


ros::NodeHandle  nh;


std_msgs::Float32 temp_msg;
ros::Publisher pub_temp("temperature", &temp_msg);


void setup()
{
    nh.initNode();
    nh.advertise(pub_temp);
}

unsigned long publisher_timer;

void loop() 
{
  if (millis() > publisher_timer) {
      float temperature = getTemp(tempPin1);
      temp_msg.data = temperature;
      pub_temp.publish(&temp_msg);
      publisher_timer = millis() + 1000;
  }
  
  nh.spinOnce();
}


float getTemp(int pin) {
    int a = analogRead(pin);
    float R = 1023.0 / (a - 1.0);
    R = R0*R;
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // Convert to temperature via datasheet
    return temperature;
}