#include "TeensyTimerTool.h"
#include <CastleLink.h>


bool castleLink::begin(int pin){
    pin = pin;
    t20ms.begin(t20msISR, 20'000, false);
    tthr.begin(tthrISR);
    pulseOffset = 500;
    throttle = 1000;
    return true;
};

void castleLink::t20msISR(){
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

void castleLink::tthrISR(){
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

void castleLink::pulseISR(){
    pulsed = true;
    float pulseLen = (micros()-startTime)/1000;
    switch (pulseCount){
        case 0:
            pulse1ms = pulseLen;
            break;
        case 1:
            voltage = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 2:
            ripVoltage = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 3:
            current = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 4:
            escThrottle = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 5:
            power = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 6:
            rpm = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 7:
            becVoltage = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 8:
            becCurent = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 9:
            temp = (pulseLen-pulseOffset)*conversion[pulseCount];
            break;
        case 10:
            pulseOffset = pulseLen;
            pulseCal = (float)(pulse1ms-pulseOffset)/500.0;
            break;
        default:
            break;
        
        pulseCount++;
        // sets pin back to high after pulse. may not be needed
        // detachInterrupt(digitalPinToInterrupt(pin));
        // pinMode(pin,OUTPUT);
        // digitalWrite(pin,1);
    }
    return;
}

void castleLink::setThrottle(int throttlePer){
    throttle = 1000+1000*throttlePer;
}