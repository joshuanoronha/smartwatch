#include <NTPClient.h> 
#include <MPU9250_asukiaaa.h> 
#include <ESP8266WiFi.h> 
#include <WiFiUdp.h> 
#include <SPI.h> 
#include <Wire.h> 
#include <string.h> 

#include <EEPROM.h> 
#include "displaySystem.h"

MPU9250 mySensor;

uint8_t sensorId;
float aX,aY,aZ,aSqrt,gX,gY,gZ,mDirection,mX,mY,mZ;

const char * ssid = "TP-Link_6329";
const char * password = "2051313908";
long lastSecTime = 0;

WiFiUDP ntpUDP;
int sec = 0;
int battery = 10;


char* b = "Notification: Crocin Time ";
boolean blinking = false;
boolean notificationExists = true;

NTPClient timeClient(ntpUDP, (long)(3600 * 5.5));
DisplaySystem displaySystem;


void connectToWifi()    {
    WiFi.begin(ssid, password);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)  {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected");
}

void setup() {
    Serial.begin(115200);

    displaySystem.drawStartScreen(ssid);


    connectToWifi();

    lastSecTime = millis();
    timeClient.begin();

    mySensor.setWire(& Wire);
    mySensor.beginAccel();
    mySensor.beginGyro();
    mySensor.beginMag();

}



char* getTime() {
    timeClient.update();
    String c = timeClient.getFormattedTime();
    char * time = const_cast < char *>(c.c_str());
    return time;
}


void batteryUpdate()  {
  if (sec == 67) {
    sec = 0;
    battery--;
    if (battery < 3) 
      battery = 3;
  }
}


void drawNormalScreen() {

    displaySystem.clearDisplay();
    displaySystem.drawStr(42, 0, getTime());      // draw Time

    displaySystem.drawBattery(sec, battery);
    displaySystem.drawBar();

    displaySystem.drawHeartBeat(15, 14, 90);
    displaySystem.marquee_helper(10, 24, b, 19);

    if (notificationExists) {
         displaySystem.notification(blinking);
    }

    display.display();
}

void loop() {
    mySensor.accelUpdate();
    aSqrt = mySensor.accelSqrt();
    // Serial.println(String(aSqrt));

    mySensor.gyroUpdate();

    mySensor.magUpdate();
    mX = mySensor.magX();
    mY = mySensor.magY();
    mZ = mySensor.magZ();
    mDirection = mySensor.magHorizDirection();

    if (millis() - lastSecTime >= 1000) {
        sec++;
        lastSecTime = millis();
        blinking = !blinking;
    }
    batteryUpdate();
    drawNormalScreen();

}

