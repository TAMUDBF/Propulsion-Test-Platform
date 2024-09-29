#include <Arduino.h>
#include <Adafruit_BNO08x.h> //has the library
#include <HX711.h>
#include <SdFat.h>
#include <Adafruit_NeoPixel.h>

//LED Setup
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN 23 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 1 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

//Creating instance of the BNO08x IMU sensor
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_BNO08x bno08x;

//variables for storing IMU data
sh2_SensorValue_t sensorValue;
float acceleration[4];
float angular_velocity[4];
float linear_acceleration[4];
float gravity[4];
float magnet[4];
float orientation[5];

void setup() {
    //initialize serial communication for debugging
    Serial.begin(115200);

    pixels.begin(); //initialize the neopixel strip

    //IMU initialization
    Serial.println("Initializing IMU...");
    if(!bno08x.begin_I2C()){
        while(!bno08x.begin_I2C()){
            Serial.println("IMU not found");
            pixels.setPixelColor(0,pixels.Color(160, 32, 255)); 
            pixels.show(); // Purple
            delay(1000);  //one sec wait (og was 100)
        }
    }

    Serial.println("IMU initialized successfully!");

}

void loop() {
    //Read IMU
    bno08x.getSensorEvent(&sensorValue);
    switch (sensorValue.sensorId) {
        case SH2_ACCELEROMETER:
        acceleration[0] = sensorValue.un.accelerometer.x;
        acceleration[1] = sensorValue.un.accelerometer.y;
        acceleration[2] = sensorValue.un.accelerometer.z;
        acceleration[3] = sensorValue.timestamp;
        break;
      
        case SH2_GYROSCOPE_CALIBRATED:
        angular_velocity[0] = sensorValue.un.gyroscope.x;
        angular_velocity[1] = sensorValue.un.gyroscope.y;
        angular_velocity[2] = sensorValue.un.gyroscope.z;
        angular_velocity[3] = sensorValue.timestamp;
        break;
        
        case SH2_LINEAR_ACCELERATION:
        linear_acceleration[0] = sensorValue.un.linearAcceleration.x;
        linear_acceleration[1] = sensorValue.un.linearAcceleration.y;
        linear_acceleration[2] = sensorValue.un.linearAcceleration.z;
        linear_acceleration[3] = sensorValue.timestamp;
        break;
        
        case SH2_GRAVITY:
        gravity[0] = sensorValue.un.gravity.x;
        gravity[1] = sensorValue.un.gravity.y;
        gravity[2] = sensorValue.un.gravity.z;
        gravity[3] = sensorValue.timestamp;
        break;
        
        case SH2_MAGNETIC_FIELD_CALIBRATED:
        magnet[0] = sensorValue.un.magneticField.x;
        magnet[1] = sensorValue.un.magneticField.y;
        magnet[2] = sensorValue.un.magneticField.z;
        magnet[3] = sensorValue.timestamp;
        break;

        case SH2_ROTATION_VECTOR:
        orientation[0] = sensorValue.un.rotationVector.i;
        orientation[1] = sensorValue.un.rotationVector.j;
        orientation[2] = sensorValue.un.rotationVector.k;
        orientation[3] = sensorValue.un.rotationVector.real;
        orientation[4] = sensorValue.timestamp;
        break;
    }

  // Optional: Print the IMU data for debugging
  Serial.print("Acceleration: ");
  Serial.print(acceleration[0]); Serial.print(", ");
  Serial.print(acceleration[1]); Serial.print(", ");
  Serial.print(acceleration[2]); Serial.println(" m/s^2");

  // Add a delay to slow down the loop (if needed)
  delay(100); 


}

