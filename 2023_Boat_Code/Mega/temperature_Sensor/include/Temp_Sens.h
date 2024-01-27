#ifndef __TEMP_SENS__
#define __TEMP_SENS__

#include <arduino.h>

#define B  4275   //Refer to Thermistor wiki ~ Beta equation; Beta range 4250K -> 4299K for temperature sensing range of -40C->125C
#define R0 100000 // ↑ ~ R0 is the rough resistance of the thermistor(to current) at 25C

class Temp_Sens {
  private:
    byte PIN;

  public:
    Temp_Sens(byte pin);
    float get_temp();

};

#endif