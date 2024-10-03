#ifndef castle_link_h
#define castle_link_h
#include "TeensyTimerTool.h"

class castleLink{
private:
    static TeensyTimerTool::PeriodicTimer t20ms;
    static TeensyTimerTool::OneShotTimer tthr;
    static volatile unsigned long startTime;
    static volatile int pulseCount;
    static volatile bool pulsed,ontimer;
    static int pin;
    #define conversion = {1f,20f,4f,50f,1f,0.2502f,20416.7f,4f,4f,30f,1f};
    //float values = {&voltage, &ripVoltage, &current, &escThrottle, &power, &rpm, &becVoltage, &becCurent, &temp };
    static void t20msISR();
    static void tthrISR();
    static void pulseISR();
public:
    static volatile int throttle;
    bool begin(int pin);
    void setThrottle(int throttle);
    
    static volatile float voltage,ripVoltage,current,escThrottle,power,rpm,becVoltage,becCurent,temp;

};

#endif