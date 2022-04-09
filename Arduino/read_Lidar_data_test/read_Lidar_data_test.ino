#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); 
#define MAX_COLLECTION_SIZE 100


typedef struct {
  int x;
  int y;
  char type;
} data_t;

data_t storage[MAX_COLLECTION_SIZE] = {0};

void setup() {
    mySerial.begin(115200);
    Serial.begin(115200);
}

void loop() {
  if(retrive_data() == true)
  {
    Serial.println("Data Retreved");  
  }
}


bool retrive_data()
{
  if (mySerial.available() > 0)
  {
    // This makes sure that we are at the start of a message
    while (((char)mySerial.read())!='S')
    {
      //Serial.println("Off Center readjusting");
    }
    Serial.println("readingData");
    char sensor_type = (char)mySerial.read();
    //    int sizeof_data = (int)mySerial.read();
    //    sizeof_data << 8;
    int sizeof_data = mySerial.read();
    
    
    Serial.println(sizeof_data);

    byte* ptr = (byte*) &storage;
    for (int i = 0; i < sizeof_data; i++)
    {
      byte m = mySerial.read();
      *ptr = m;
      ptr++;
    }

    if (((char)mySerial.read())!='E')
    {
      Serial.println("ReadData Wrong");
      return false;
    }
    return true;
  }
  else
  {
    Serial.println("No Data");
  }
  return false;
}
