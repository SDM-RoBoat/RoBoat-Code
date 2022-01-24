#ifndef ARDUINO_H
#define ARDUINO_H

#define A0 0
#define A5 5

enum type {LOW, HIGH, INPUT, OUTPUT};

int abs( int val );

int analogRead( int pin );

bool analogWrite( int pin, type s );

void delayMicroseconds( int micro );

bool digitalWrite( int pin, type s );

bool pinMode( int pin, type s );

void analogWrite( int pin, int d );

long pulseIn( int pin, type s );

#endif //ARDUINO_H