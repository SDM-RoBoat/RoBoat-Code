#include <IR_Sensor.h>
#include <SonarSensor.h>
#include <Robot.h>

int triggerPin = 3;
int echoPin = 4;

int Motor_Left[3] = {5, 10, 7}; // motorSpeed pin (PWM), A3 pin, A4 pin 
int Motor_Right[3] = {6, 8, 7}; // motorSpeed pin (PWM), A1 pin, A2 pin
long distance = 0;

const int LINE_THRESHOLD = 700;

Robot robot1(Motor_Left, Motor_Right, 3);
Sonar front(triggerPin, echoPin, 5, 40);
IR_Sensor IRLeft(A0);
IR_Sensor IRMiddle(A1);
IR_Sensor IRRight(A2);

//function delarations
bool detectedLine(IR_Sensor &sensor);

void setup() {
  //front.useBound(true); //enable cliping on sonar distance reading  
  //serial used for terminal messages
  //Serial.begin(9600);
}

int state = 0;
long avg;
bool LLeft = 0; //line left
bool LMiddle = 0; //line middle
bool LRight = 0; //line right
bool last = false; //false = left, true = right
void loop() {
  LLeft = detectedLine(IRLeft);
  LMiddle = detectedLine(IRMiddle);
  LRight = detectedLine(IRRight);
  
  if (state == 0 and LLeft == false and LMiddle == false and LRight == false) // in the box
  {
    robot1.forward(255);
  }
  else if (state == 0 && (LLeft == true or LMiddle == true or LRight or true)) //on the line of the box
  {
    state = 1;  
  }
  else if (state == 1 and LLeft == false and LMiddle == false and LRight == false) //outside the box
  {
    robot1.hult();
    state = 2;
    robot1.left(255);
  }
  else if (state == 2 && LRight == true && LMiddle == true) //turning right
  {
    state = 3;
    robot1.forward(200);
  }
  else if (state == 3 || state == 4)// on line
  {
      //line follower
    if (LLeft == true && LMiddle == false) // on right side
    {
      robot1.left(255);
      last = false;
    }
    else if (LRight == true && LMiddle == false) // on left side
    {
      last = true;
      robot1.right(255);
    }
    else if (LMiddle == true && (LLeft == false || LRight == false)) // on the line
    {
      robot1.forward(255);
    }
    else if(LLeft == true && LRight == true && LMiddle == true)
    {
      if (state == 3) //first time
      {
        robot1.forward(255);
        state = 4;
      }
      else
      {
        robot1.hult();
      }
    }
    else // off the line, could be at end
    {
      if (last) 
      {
       robot1.right(255);
      }
      else
      {
        robot1.left(255);
      }
    }
  }

  delay(0.5);
}

bool detectedLine(IR_Sensor &sensor)
{
    int value;
    if (sensor.Read(value))
    {
      if (value > LINE_THRESHOLD)
        return true;
    }
    return false;
}


bool thresh(int val, int threshold)
{
  if threshold < val
    return true;
   return false;
}

}
