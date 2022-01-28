#ifndef ARDUINO_H
#define ARDUINO_H

#define A0 0
#define A5 5
#define LOW false
#define HIGH true
enum type {INPUT, OUTPUT};

int abs( int val );

int analogRead( int pin );

bool analogWrite( int pin, bool s );

void delayMicroseconds( int micro );

bool digitalWrite( int pin, bool s );

bool pinMode( int pin, type s );

void analogWrite( int pin, int d );

long pulseIn( int pin, bool s );

#endif //ARDUINO_H