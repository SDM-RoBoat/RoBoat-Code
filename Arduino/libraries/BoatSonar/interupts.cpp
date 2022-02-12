/** ***************************************************************************
 * @file
 *
 * @brief   deffinitions for pin interupts
 *****************************************************************************/
#include "interupts.h"

//temp data for zone 3
volatile long zone3Start = 0;
volatile long zone3End = 0;
volatile bool mode3 = 0;

//temp data for zone 2
volatile long zone2Start = 0;
volatile long zone2End = 0;
volatile bool mode2 = 0;

//temp data for zone 1
volatile long zone1Start = 0;
volatile long zone1End = 0;
volatile bool mode1 = 0;

//temp data for zone 0
volatile long zone0Start = 0;
volatile long zone0End = 0;
volatile bool mode0 = 0;



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction fully handles setting up the intrupt pins
 *
 *****************************************************************************/
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
/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction sets up the intrupts on pin 19 for zone 3
 *
 *****************************************************************************/
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

/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction is the interupt function that is called when the pin changes
 * state for zone 3.
 *
 *****************************************************************************/
ISR( INT2_vect ) //interuput call function
{ //called when ever pin 19 changes
    !mode3 ? zone3Start = micros() : zone3End = micros();
}



//zone 2
/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction sets up the intrupts on pin 18 for zone 2
 *
 *****************************************************************************/
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

/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction is the interupt function that is called when the pin changes
 * state for zone 2.
 *
 *****************************************************************************/
ISR( INT3_vect ) //interuput call function
{ //called when ever pin 18 changes
    !mode2 ? zone2Start = micros() : zone2End = micros();
}



//zone 1
/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction sets up the intrupts on pin 3 for zone 1
 *
 *****************************************************************************/
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

/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction is the interupt function that is called when the pin changes
 * state for zone 1.
 *
 *****************************************************************************/
ISR( INT5_vect ) //interuput call function
{ //called when ever pin 3 changes
    !mode1 ? zone1Start = micros() : zone1End = micros();
}



//zone 0
/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction sets up the intrupts on pin 2 for zone 0
 *
 *****************************************************************************/
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

/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * This fuction is the interupt function that is called when the pin changes
 * state for zone 0.
 *
 *****************************************************************************/
ISR( INT4_vect ) //interuput call function
{ //called when ever pin 2 changes
    !mode0 ? zone0Start = micros() : zone0End = micros();
}



/** ***************************************************************************
 * @author Kyle Houchin
 *
 * @par Description:
 * this funtion returns the data from the interupt collections on the echo pins
 * equivenlt of running a pulseIn(echoPin). However this allows for a faster
 * collection time for lots of sonars
 * 
 * @returns The temp data for the zone. In a long
 *
 *****************************************************************************/
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