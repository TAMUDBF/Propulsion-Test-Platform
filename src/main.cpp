#include <Arduino.h>
#include <Adafruit_BNO08x.h>
#include <HX711.h>
#include <SdFat.h>
#include "CastleLink.h"
const int esc_pin = 3;
castleLink esc;

void setup() {
    Serial.begin(9600);
    esc.begin(esc_pin);
}

void loop() {
    Serial.printf("Voltage: %.2f V\t",esc.voltage);
    Serial.printf("Cureent: %.2f A\t",esc.current);
    Serial.printf("Throttle: %.2f ms\t",esc.escThrottle);
    Serial.printf("RPM: %.2f rpm\t",esc.rpm);
    Serial.printf("Temp: %.2f C\t",esc.temp);
    Serial.println();
}

