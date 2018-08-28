
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
// i2Cdev library and MPU9250 must be installed as libraries, or else the .cpp/.h file
// for both clsses must be in the inlcude path of your projects. 

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9250.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here

// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69

MPU9250 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

#define LED_PIN 13 //Define as pin 13 LED on Arduino Board

bool blinkState = false;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
  
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
  
    Serial.begin(19200); //Initializing serial communication 

    // initialize device
  Serial.println("14CORE | MPU9250 TEST CODE")
    Serial.println("Initializing I2C devices, please wait...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Verifiying device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU9250 connection successful" : "MPU9250 connection failed");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT); //Define as LED pin13 Output
}

void loop() {
  //Define as read raw Accelaration / Gyroscope measurement from the device.
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

    //these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // display tab-separated accel/gyro x/y/z values
  
    Serial.print("a/g/m:\t");
    Serial.print(ax); Serial.print("\t"); // Serial print AX
    Serial.print(ay); Serial.print("\t"); // Serial print AY
    Serial.print(az); Serial.print("\t"); // Serial print AZ
    Serial.print(gx); Serial.print("\t"); // Serial print GX
    Serial.print(gy); Serial.print("\t"); // Serial print GY
    Serial.print(gz); Serial.print("\t"); // Serial print GZ
    Serial.print(mx); Serial.print("\t"); // Serial print MX
    Serial.print(my); Serial.print("\t"); // Serial print MY
    Serial.println(mz);           // Serial print MZ

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
