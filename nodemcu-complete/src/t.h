#include <Arduino.h>
#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN D2
#define SCL_PIN D1
#endif

MPU9250 mySensor;

uint8_t sensorId;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

void setup() {
  Serial.begin(921600);
  delay(1000);
  Serial.println("started");

#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN); // SDA, SCL
#else
  Wire.begin();
#endif

  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  // You can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;

  sensorId = mySensor.readId();
}

void loop() {
//   Serial.println("sensorId: " + String(sensorId));

  mySensor.accelUpdate();
//   aX = mySensor.accelX();
//   aY = mySensor.accelY();
//   aZ = mySensor.accelZ();
  aSqrt = mySensor.accelSqrt();
//   Serial.println("accelX: " + String(aX));
//   Serial.println("accelY: " + String(aY));
//   Serial.println("accelZ: " + String(aZ));
  // Serial.println("accelSqrt: " + String(aSqrt));
   Serial.println( String(aSqrt));

  mySensor.gyroUpdate();
//   gX = mySensor.gyroX();
//   gY = mySensor.gyroY();
//   gZ = mySensor.gyroZ();
//   Serial.println("gyroX: " + String(gX));
//   Serial.println("gyroY: " + String(gY));
//   Serial.println("gyroZ: " + String(gZ));

  mySensor.magUpdate();
  mX = mySensor.magX();
  mY = mySensor.magY();
  mZ = mySensor.magZ();
  mDirection = mySensor.magHorizDirection();
//   Serial.println("magX: " + String(mX));
//   Serial.println("maxY: " + String(mY));
//   Serial.println("magZ: " + String(mZ));
//   Serial.println("horizontal direction: " + String(mDirection));

//   Serial.println("at " + String(millis()) + "ms");
//   Serial.println(""); // Add an empty line
  delay(10);
}

