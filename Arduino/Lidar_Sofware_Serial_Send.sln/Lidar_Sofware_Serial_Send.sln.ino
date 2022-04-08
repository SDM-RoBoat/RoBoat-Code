#include <RPLidar.h>
#include <SoftwareSerial.h>


#define MAX_COLLECTION_SIZE 100
#define MAX_ANGLE_COLLECTION 45
#define RPLIDAR_MOTOR 6
#define RANGE 50 //in mm

RPLidar lidar;
SoftwareSerial mySerial(2, 3); //2, 3, 10, 11

typedef struct {
  int x;
  int y;
  char type;
} data_t;
data_t storage[MAX_COLLECTION_SIZE] = {0};
data_t temp;

//temp vars use your own var in loop
int i = 0; //current spot in stroage
float angle  = 0; //this is the angle colleted from sensor.

char lidarIdent = 2;

//function Decloartions
bool sendData();



void setup()
{
  mySerial.begin(115200);
  
  lidar.begin(Serial);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}



void loop()
{
  if (IS_OK(lidar.waitPoint())) {
    //collect data
    float distance = lidar.getCurrentPoint().distance;
    float angle    = lidar.getCurrentPoint().angle;
    
    storage[i].x = (int)(distance * cos(angle));
    storage[i].y = (int)(distance * sin(angle));
    storage[i].type = (int)((distance - ((int)distance % RANGE))/RANGE); 
    
    //send data if ready
    if (((((int)(floor(angle)))%MAX_ANGLE_COLLECTION) == 0) || (i == MAX_COLLECTION_SIZE)) 
    {
      //makes sure zeros are set for unwriten data
      for (int j = i; j < MAX_COLLECTION_SIZE; j++)
      {
        storage[j].x = 0;
        storage[j].y = 0;
        storage[j].type = 0;
       }
      //sends data
      sendData();
    }
  } else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor

    // try to detect RPLIDAR...
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
      // detected...
      lidar.startScan();

      // start motor rotating at max allowed speed
      analogWrite(RPLIDAR_MOTOR, 255);
      delay(1000);
    }
  }
}



bool sendData()
{
    mySerial.write('S');
    mySerial.write(lidarIdent);
    byte* ptr = (byte*) &storage;
    byte counter = sizeof(storage);
    mySerial.write(counter);
    
    do {
      byte m = (byte*)*ptr;
      mySerial.write(m);
      ptr++;
      counter--; 
    } while (counter != 0);

    mySerial.write('E');
}
