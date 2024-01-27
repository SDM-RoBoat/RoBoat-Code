#include "main.h"



/* Putting this here fort the sake of establishing a 'pretend' nh->node handler

 <MAX_Subscribers, MAX_Publishers, Input_Size, Output_Size>
ros::NodeHandle_<ArduinoHardware, MAX_SUBSCRIBERS, MAX_PUBLISHERS, INPUT_SIZE, OUTPUT_SIZE> nh;

custom
  */

void setup() {
    for (int i =0; i<arrSize; i++) {
        tmp[i] = new Temp_Sens(i);
    }
    //nh.logwarn("Temperature sensors connected!");
}

void loop() {
    if (tmp!=nullptr) {
        for (int i = 0; i<arrSize; i++) {
            String holding = "Temperature Sensor " + i; 
            holding += " reads "; 
            holding += tmp[i]->get_temp(); 
            holding += " Celsius";
            //nh.logwarn(holding.c_str());
        }
    }
    
}