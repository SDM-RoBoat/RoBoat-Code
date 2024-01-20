#include "relay.h"

relay::relay(byte pin)
{
  PIN = pin;
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  state = false;
}

void relay::enable() 
{
  if (!state) {
    digitalWrite(PIN, HIGH);
    state = true;
  }
}

void relay::dissable()
{
  if (state) {
    digitalWrite(PIN, LOW);
    state = false;
  }
}

void relay::toggle()
{
  state = !state;
  digitalWrite(PIN, state);
}
