#include "TeensyTimerTool.h"
#include <castleLink.h>

bool castleLink::begin(int pin){
    pin = pin;
    t20ms.begin(t20msISR, 20'000, false);
    tthr.begin(tthrISR);
};

static void castleLink::t20msISR(){
    detachInterrupt(digitalPinToInterrupt(pin));
    pinMode(pin,OUTPUT);
    digitalWrite(pin,0);
    if(!pulsed){
        pulseCount = 0;
    }
    pulsed = false;
    ontimer = false;
    tthr.trigger(throttle);
    
    return;
};

static void castleLink::tthrISR(){
    if (ontimer){
        ontimer = false;
        pinMode(pin,INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(pin),pulseISR,FALLING);
    } else {
        digitalWrite(pin,1);
        ontimer = true;
        startTime = micros();
        tthr.trigger(10);
    }
    return;
}

static void castleLink::pulseISR(){
    pulsed = true;
    float pulseLen = (micros()-startTime)/1000;
    return;
}