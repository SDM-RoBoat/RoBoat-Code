/** ***************************************************************************
 * @file
 *
 * @brief   deffinitions for pin interupts
 *****************************************************************************/
#include "interupts.h"

//temp data for zone 3
volatile unsigned long zone3Start = 0;
volatile unsigned long zone3End = 0;
volatile bool mode3 = 0;

//temp data for zone 2
volatile unsigned long zone2Start = 0;
volatile unsigned long zone2End = 0;
volatile bool mode2 = 0;

//temp data for zone 1
volatile unsigned long zone1Start = 0;
volatile unsigned long zone1End = 0;
volatile bool mode1 = 0;

//temp data for zone 0
volatile unsigned long zone0Start = 0;
volatile unsigned long zone0End = 0;
volatile bool mode0 = 0;

bool getMode(int zone_num)
{
    switch (zone_num)
    {
    case 0:
        return mode0;
    case 1:
        return mode1;
    case 2:
        return mode2;
    case 3: 
        return mode3;
    default:
        return true;
    }
}

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
    if (!mode3)
    {
        zone3Start = micros();
        mode3 = !mode3;
        return;
    }
    zone3End = micros();
    mode3 = !mode3;

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
    if (!mode2)
    {
        zone2Start = micros();
        mode2 = !mode2;
        return;
    }
    zone2End = micros();
    mode2 = !mode2;
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
    if (!mode1)
    {
        zone1Start = micros();
        mode1 = !mode1;
        return;
    }
    zone1End = micros();
    mode1 = !mode1;
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
    if (!mode0)
    {
        zone0Start = micros();
        mode0 = !mode0;

        return;
    }
    zone0End = micros();
    mode0 = !mode0;
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
        /*Serial.print("Zone0Start: ");
        Serial.println(zone0Start);
        Serial.print("Zone0End: ");
        Serial.println(zone0End);*/
        return (long)(zone0End - zone0Start);
        break;
    case 1:
        return (long)(zone1End - zone1Start);
        break;
    case 2:
        return (long)(zone2End - zone2Start);
        break;
    case 3:
        return (long)(zone3End - zone3Start);
        break;
    default:
        break;
    }
}