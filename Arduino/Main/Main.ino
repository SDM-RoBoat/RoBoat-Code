#include <IR_Sensor.h>
#include <SonarSensor.h>
#include <Robot.h>

int triggerPin = 3;
int echoPin = 4;

int Motor_Left[3] = {5, 10, 7}; // motorSpeed pin (PWM), A3 pin, A4 pin 
int Motor_Right[3] = {6, 8, 7}; // motorSpeed pin (PWM), A1 pin, A2 pin

long distance = 0;

Robot robot1(Motor_Left, Motor_Right,3);
Sonar front(triggerPin, echoPin, 5, 40);
IR_Sensor IRLeft(A0);
IR_Sensor IRMiddle(A1);
IR_Sensor IRRight(A2);


void setup() {
  //front.useBound(true); //enable cliping on sonar distance reading  
  //serial used for terminal messages
  Serial.begin(9600);
}
  

long avg;
void loop() {
  Serial.print("Left: ");
  Serial.print(IRLeft.Read());
  Serial.print(" Middle: ");
  Serial.print(IRMiddle.Read());
  Serial.print(" Right: ");
  Serial.println(IRRight.Read());
  
  if (front.getAvgDistance(avg, 5)) // bad read
  {
    if (avg < 13)
    {
      robot1.forward(-255);  
    }
    else
    {
      robot1.forward(255);
    }
  }
  else
  {
    robot1.hult();
  }
}
