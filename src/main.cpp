#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3; 
const int LOADCELL_SCK_PIN = 2;

HX711 scale;

//callibration parameters 
const float calibrationFactor = 0.0047;
const float offset = 199.94;   


void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  //optional, tare the reading. 
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read();

    //apply new formula
    long mapRead = (calibrationFactor * reading) - offset;

    Serial.print("HX711 reading: ");
    Serial.println(mapRead);
    Serial.print(" g");
  } else {
    Serial.println("HX711 not found.");
  }

  delay(100);
  
}
