#include <SoftwareSerial.h>

#define MAX_COLLECTION_SIZE 100
#define MAX_ANGLE_COLLECTION 45

SoftwareSerial mySerial(2, 3); //2, 3, 10, 11


typedef struct {
  int x;
  int y;
  char type;
} data_t;
data_t storage[MAX_COLLECTION_SIZE] = {0};


//temp vars use your own var in loop
int i = 0; //current spot in stroage
float angle  = 0; //this is the angle colleted from sensor.


//function Decloartions
bool sendData();



void setup()
{
  mySerial.begin(115200);
}



void loop()
{
  //collect data
  
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
}



bool sendData()
{
    byte* ptr = (byte*) &storage;
    byte counter = sizeof(storage);
    do {
      byte m = (byte*)*ptr;
      mySerial.write(m);
      ptr++;
      counter--; 
    } while (counter != 0);
}