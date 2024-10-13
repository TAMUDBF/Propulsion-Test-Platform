#include <Arduino.h>
#include <Adafruit_BNO08x.h>
#include <HX711.h>
#include <SdFat.h>
#include "CastleLink.h"
const int esc_pin = 3;
castleLink esc;

void setup() {
    Serial.begin(115200);
    delay(2000);
    esc.begin(esc_pin);
    // esc arming: might not be needed
    // esc.setThrottle(0.5);
    // delay(500);
    // esc.setThrottle(0);
}

void loop() {
    Serial.printf("Voltage: %.2f V\t",esc.voltage);
    Serial.printf("Current: %.2f A\t",esc.current);
    Serial.printf("Throttle: %.2f ms\t",esc.escThrottle);
    Serial.printf("RPM: %.2f rpm\t",esc.rpm);
    Serial.printf("Temp: %.2f C\t",esc.temp);
    Serial.println();
    delay(20);
}

