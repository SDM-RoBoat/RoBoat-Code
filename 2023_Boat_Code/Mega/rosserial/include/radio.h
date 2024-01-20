#ifndef __Radio_H__
#define __Radio_H__

#include "Arduino.h"
#include <math.h>

enum channel { Thro, Aile, Elev, Rudd, Gear, Aux1 }; //corralates to the channel on the reciver

class Radio
{
    public:

        Radio();
        //UBS is on 18 & 19 <-note cant use
        //interupt pins Mega 2560: 	2, 3, 18, 19, 20, 21
        bool set(channel Channel, uint8_t pin);

        int read(channel Channel);
        
    private:
        struct timeValues
        {
            unsigned long previousTime = 0;
            unsigned long curTime = 0;
            unsigned long value = 0;
        };

        struct cInfo
        {
            uint8_t pin = 0;
            bool enabled = false;
        };

        cInfo channelInfo[6];
        volatile timeValues values[6];

        const unsigned long MIN = 800; // actually 892
        const unsigned long MAX = 2100; // actually 2096

        unsigned long bound(unsigned long val); 

        static Radio* ISRWrapper;

        bool setChannelISR(channel Channel);
        void channelISR(channel Channel);

        static void ThroISR();
        static void AileISR();
        static void ElevISR();
        static void RuddISR();
        static void GearISR();
        static void Aux1ISR();
};

#endif