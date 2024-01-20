#include "Adafruit_VCNL4010.h"
#include "math.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//defined vars
  //speed sensor
    float wheel_dist = (M_PI*3.5); //cercumfrance of wheel in
    float num_of_black_tape = 4.0;
    int threshold = 3000;
    long int timeout = 2000; //2 sec
    bool timeoutB = false;
    
    long int last_encoder_time = 0;
    int last_encoder_state = 0;
    bool last_on_black = false;
  
  //motor
    int min_value = 150;
    //int max_value = 250;
    int max_value = 255;
    float min_speed = 4.0; // (in/sec) without stall
    float max_speed = 12.0; // (in/sec) cans fall off
    
    float set_speed = 7.0; // (in/sec)
    
    float last_speed = 0.0;

  //PID
    //0.9 = P 10.8 error is 255 motor
    float P = 2.5;
    float D = 0;
    float I = 0;

  //moving avg
    int ii = 0;
    int num_avg = 5;
    float avgArray[5] = {0};


//Function Declorations
  bool encoder_State();
  long int update_encoder_state();
  float convert_speed(long int espeed);
  float get_speed();
  int motorMap(float E, float minS, float maxS, int minV, int maxV);
  float movingAvgerage(float new_number);
  float getSerialNewSpeed();
// initiate libs
  Adafruit_VCNL4010 vcnl;
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

//main code
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  if (! vcnl.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.println("Found VCNL4010");

  AFMS.begin();
  myMotor->setSpeed(0);
  myMotor->run(FORWARD);

  last_encoder_time = millis();

  set_speed = 6.0; // (in/sec)
}

void loop() {

    //update set speed
    set_speed = getSerialNewSpeed();
    
    float cSpeed = get_speed(); // (in/sec)
    float avgSpeed = movingAvgerage(cSpeed);

    float error = set_speed - avgSpeed;
    error *= P;
    Serial.print("Set Speed: ");
    Serial.print(set_speed);
    Serial.print("    Avg Speed: ");
    Serial.print(avgSpeed);
    Serial.print("    Error: ");
    Serial.print(error);
    
    int motor_val = motorMap(error, min_speed, max_speed, min_value, max_value);
    //bound motor
    if (motor_val != 0) {
      if (motor_val < min_value) {
        motor_val = min_value;
      } else if (motor_val > max_value) {
        motor_val = max_value;
      }
    }

    if (set_speed == 0) {
      motor_val = 0;
    }
    myMotor->setSpeed(motor_val);
    myMotor->run(FORWARD);

    Serial.print("   Motor val: ");
    Serial.println(motor_val);
}

//function code
float getSerialNewSpeed() {
    float newspeed = set_speed;
    if (Serial.available()!=0) {
      float temp_speed = Serial.parseFloat();
      if (temp_speed != 0) {
        if (temp_speed < min_speed) {
          Serial.print("Can not set speed under ");
          Serial.print(min_speed);
          Serial.println(" in/sec");
        } else if (temp_speed == 100) {
          Serial.println("Stoping");
          newspeed = 0;
        } else if (temp_speed > (max_speed - 2.0)) {
          Serial.print("Can not set speed over ");
          Serial.print(max_speed-2);
          Serial.println(" in/sec");
        } else {
          newspeed = temp_speed;
          Serial.print("Changed speed to: ");
          Serial.println(newspeed); 
        }
      }
    }
    return newspeed;
}

float movingAvgerage(float new_number) {
    avgArray[ii] = new_number;
    float avg = 0;
    for(int i=0; i<num_avg; i++) {
        avg += avgArray[i];
    }
    avg /= num_avg;
    
    ii++;
    if (ii>=num_avg) {
      ii = 0;
    }

    return avg;
}

int motorMap(float E, float minS, float maxS, int minV, int maxV) {
  if (E != 0) {
    return int( minV + (((E-minS)*(maxV-minV))/(maxS - minS)));
  }
  return 0;
}

float get_speed() {
    long int result = update_encoder_state();
    float cSpeed = convert_speed(result);
    if (cSpeed != -1) {
      //Serial.println(cSpeed);
      last_speed = cSpeed;
    } else {
      cSpeed = last_speed;
    }

    return cSpeed;
}

float convert_speed(long int espeed) {
  if (espeed == 0) {
    return 0;
  } else if (espeed == -1) {
    return -1;
  } else {
    float rope_speed = (wheel_dist/num_of_black_tape)/(espeed/1000.0);
    return rope_speed;  
  }
}

long int update_encoder_state() {
  bool current_state = encoder_State();

  long int current_time = millis();
  long int diff_time = current_time-last_encoder_time;
  
  if (last_on_black) {
    if (!current_state) {
      //Serial.println("State Change: Black->White");
      last_on_black = current_state;
    } else {
      //no change in state
      if (diff_time > timeout){
        //Serial.println("Time Out");
        timeoutB = true;
        return 0;
      }
    }
  } else {
    if (current_state) {
      //Serial.println("State Change: White->Black");
      //Serial.print("Diff Time: ");
      //Serial.println(diff_time);

      last_on_black = current_state;
      last_encoder_time = current_time;
      
      if (timeoutB) {
            timeoutB = false;
            return 0;
      }
      return diff_time;
    } else {
      //no change in state
      if (diff_time > timeout){
        //Serial.println("Time Out");
        timeoutB = true;
        return 0;
      }
    }
  }
  return -1;
}

 bool encoder_State() {
    //Serial.print(" - Encoder_State: ");
    int current_val = vcnl.readProximity();
    //Serial.print(current_val);
    //Serial.print(" ");
    if (current_val > threshold) {
        //Serial.println("Black");
        return true;  
    }
    //Serial.println("White");
    return false;
 }
