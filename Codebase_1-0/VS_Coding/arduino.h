#ifndef ARDUINO_H
#define ARDUINO_H

#include <math.h>
#include <functional>

#define A0 0
#define A5 5
#define LOW false
#define HIGH true
enum type {INPUT, OUTPUT};
enum interuptTypes { CHANGE };

//int abs( int val );

int analogRead( int pin );

bool analogWrite( int pin, bool s );

void delayMicroseconds( int micro );

bool digitalWrite( int pin, bool s );

void pinMode( int pin, type s );

void analogWrite( int pin, int d );

long pulseIn( int pin, bool s );

int map(int a, int b, int c, int d, int e);

bool attachInterrupt( int pin, bool f, interuptTypes type );

int digitalPinToInterrupt( int pin);

bool detachInterrupt( int pin );

long millis();

#endif //ARDUINO_H