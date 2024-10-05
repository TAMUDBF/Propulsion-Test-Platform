#ifndef castle_link_h
#define castle_link_h
#include "TeensyTimerTool.h"

class castleLink{
private:
    inline static TeensyTimerTool::PeriodicTimer t20ms;
    inline static TeensyTimerTool::OneShotTimer tthr;
    inline static volatile unsigned long startTime;
    inline static volatile int pulseCount,pulseOffset,pulse1ms;
    inline static volatile float pulseCal;
    inline static volatile bool pulsed,ontimer;
    inline static int pin;
    inline static volatile int throttle;
    inline static constexpr float conversion[11] = {1,20,4,50,1,0.2502,20416.7,4,4,30,1};
    static void t20msISR();
    static void tthrISR();
    static void pulseISR();
public:
    bool begin(int pin);
    void setThrottle(int throttle);
    inline static volatile float voltage,ripVoltage,current,escThrottle,power,rpm,becVoltage,becCurent,temp;
};

#endif