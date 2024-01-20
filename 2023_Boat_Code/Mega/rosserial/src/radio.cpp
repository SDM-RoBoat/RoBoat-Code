#include "radio.h"

Radio* Radio::ISRWrapper = nullptr;

Radio::Radio() {
    ISRWrapper = this;
}

bool Radio::set(channel Channel, uint8_t pin)
{
    //interupt pins Mega 2560: 	2, 3, 18, 19, 20, 21
    if (!(pin==2 || pin==3 || pin==18 || pin==19 || pin==20 || pin==21)) {
        return false;
    }

    //channel allready setup
    if (channelInfo[Channel].enabled) {
        return false;
    }

    channelInfo[Channel].enabled = true;
    channelInfo[Channel].pin = pin;

    return setChannelISR(Channel);
}

int Radio::read(channel Channel) 
{
    //channel allready setup
    if (!channelInfo[Channel].enabled) {
        return -1;
    }

    unsigned long value = bound(values[Channel].value);

    value = value - (value%10);
    return int(value);
}

bool Radio::setChannelISR(channel Channel)
{
    switch (Channel)
    {
    case Thro:
        attachInterrupt(digitalPinToInterrupt(channelInfo[Channel].pin), ThroISR, CHANGE);
        break;
    case Aile:
        attachInterrupt(digitalPinToInterrupt(channelInfo[Channel].pin), AileISR, CHANGE);
        break;
    case Elev:
        attachInterrupt(digitalPinToInterrupt(channelInfo[Channel].pin), ElevISR, CHANGE);
        break;
    case Rudd:
        attachInterrupt(digitalPinToInterrupt(channelInfo[Channel].pin), RuddISR, CHANGE);
        break;
    case Gear:
        attachInterrupt(digitalPinToInterrupt(channelInfo[Channel].pin), GearISR, CHANGE);
        break;
    case Aux1:
        attachInterrupt(digitalPinToInterrupt(channelInfo[Channel].pin), Aux1ISR, CHANGE);
        break;
    default:
        return false; //not a channel
    }

    return true;
}

void Radio::channelISR(channel Channel)
{
    if (digitalRead(channelInfo[Channel].pin)) 
    { //HIGH
        values[Channel].previousTime = micros();
    }
    else
    { //LOW
        values[Channel].curTime = micros();
        values[Channel].value = values[Channel].curTime - values[Channel].previousTime;
    }
}

void Radio::ThroISR()
{
    ISRWrapper->channelISR(Thro);
}

void Radio::AileISR()
{
    ISRWrapper->channelISR(Aile);
}

void Radio::ElevISR()
{
    ISRWrapper->channelISR(Elev);
}

void Radio::RuddISR()
{
    ISRWrapper->channelISR(Rudd);
}

void Radio::GearISR()
{
    ISRWrapper->channelISR(Gear);
}

void Radio::Aux1ISR()
{
    ISRWrapper->channelISR(Aux1);
}

unsigned long Radio::bound(unsigned long val)
{
    if (val < MIN || val > MAX)
    {
        return 0;
    }

    return val;
}