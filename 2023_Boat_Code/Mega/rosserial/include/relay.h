#ifndef __RELAY_H__
#define __RELAY_H__

#include <Arduino.h>

class relay
{
  public:
    relay(byte pin);
    void enable();
    void dissable();
    void toggle();
  private:
    byte PIN;
    bool state;
};

#endif