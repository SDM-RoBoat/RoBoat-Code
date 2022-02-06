#include "interupts.h"

volatile long zone3Start = 0;
volatile long zone3End = 0;
volatile bool mode3 = 0;
volatile long zone2Start = 0;
volatile long zone2End = 0;
volatile bool mode2 = 0;
volatile long zone1Start = 0;
volatile long zone1End = 0;
volatile bool mode1 = 0;
volatile long zone0Start = 0;
volatile long zone0End = 0;
volatile bool mode0 = 0;

//this fuction fully handles setting up the intrupt pins
void setInterupts()
{
    //dissable intrupts tempurarly
    cli();

    //gets the intrupt pins set correctly
    zone0Setup();
    zone1Setup();
    zone2Setup();
    zone3Setup();

    //re-inable intrupts
    sei();
}

//zone 3

void zone3Setup() //pin 19
{
    //equivlent to doing pinMode(pin, INPUT);
    DDRD &= ~(1 << 2);
    PORTD &= ~(1 << 2); //makes sure its pulldown resistor

    //this will cange the intrupt registors
    //Equivlent of doing attachInterrupt(digitalPinToInterrupt(19), ISR(INT2_vect),CHANGE)
    //This is faster and I have more control
    EICRA |= (1 << ISC20);  //sets ISC20 to 1
    EICRA &= ~(1 << ISC21); //sets ISC21 to 0
    EIMSK |= (1 << INT2); //sets the inable for INT2
}

ISR( INT2_vect ) //interuput call function
{ //called when ever pin 19 changes
    if (!mode3)
    {
        zone3Start = micros();
    }
    else
    {
        zone3End = micros();
    }
    mode3 = !mode3;
}

//zone 2

void zone2Setup() //pin 18
{
    //equivlent to doing pinMode(pin);
    //equivlent to doing pinMode(pin, INPUT);
    DDRD &= ~(1 << 3);
    PORTD &= ~(1 << 3); //makes sure its pulldown resistor

    //this will cange the intrupt registors
    //Equivlent of doing attachInterrupt(digitalPinToInterrupt(18), ISR(INT3_vect),CHANGE)

    //This is faster and I have more control
    EICRA |= (1 << ISC30);  //sets ISC20 to 1
    EICRA &= ~(1 << ISC31); //sets ISC21 to 0
    EIMSK |= (1 << INT3); //sets the inable for INT3
}

ISR( INT3_vect ) //interuput call function
{ //called when ever pin 18 changes
    if (!mode2)
    {
        zone2Start = micros();
    }
    else
    {
        zone2End = micros();
    }
    mode2 = !mode2;
}

//zone 1

void zone1Setup() //pin 3
{
    //equivlent to doing pinMode(pin, INPUT);
    DDRE &= ~(1 << 5);
    PORTE &= ~(1 << 5); //makes sure its pulldown resistor

    //this will cange the intrupt registors
    //Equivlent of doing attachInterrupt(digitalPinToInterrupt(3), ISR(INT5_vect),CHANGE)

    //This is faster and I have more control
    EICRB |= (1 << ISC50);  //sets ISC50 to 1
    EICRB &= ~(1 << ISC51); //sets ISC51 to 0
    EIMSK |= (1 << INT5); //sets the inable for INT5
}

ISR( INT5_vect ) //interuput call function
{ //called when ever pin 3 changes
    if (!mode1)
    {
        zone1Start = micros();
    }
    else
    {
        zone1End = micros();
    }
    mode1 = !mode1;
}
//zone 0

void zone0Setup() //pin 2
{
    //equivlent to doing pinMode(pin);
    //equivlent to doing pinMode(pin, INPUT);
    DDRE &= ~(1 << 4);
    PORTE &= ~(1 << 4); //makes sure its pulldown resistor

    //this will cange the intrupt registors
    //Equivlent of doing attachInterrupt(digitalPinToInterrupt(2), ISR(INT4_vect),CHANGE)

    //This is faster and I have more control
    EICRB |= (1 << ISC40);  //sets ISC40 to 1
    EICRB &= ~(1 << ISC41); //sets ISC41 to 0
    EIMSK |= (1 << INT4); //sets the inable for INT4
}

ISR( INT4_vect ) //interuput call function
{ //called when ever pin 2 changes
    if (!mode0)
    {
        zone0Start = micros();
    }
    else
    {
        zone0End = micros();
    }
    mode0 = !mode0;
}

long getZone( int zone)
{
    switch (zone)
    {
    case 0:
        return (long)(zone0Start - zone0End);
        break;
    case 1:
        return (long)(zone1Start - zone1End);
        break;
    case 2:
        return (long)(zone2Start - zone2End);
        break;
    case 3:
        return (long)(zone3Start - zone3End);
        break;
    default:
        break;
    }
}