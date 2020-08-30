#include <NTPClient.h> 
#include <MPU9250_asukiaaa.h> 
#include <ESP8266WiFi.h> 
#include <WiFiUdp.h> 
#include <SPI.h> 
#include <Wire.h> 
#include <string.h> 

#include <PubSubClient.h>

#include <EEPROM.h> 
#include "displaySystem.h"

#include "connectionSystem.h"


MPU9250 mySensor;

uint8_t sensorId;
float aX,aY,aZ,aSqrt,gX,gY,gZ,mDirection,mX,mY,mZ;

long lastSecTime = 0;

WiFiUDP ntpUDP;
int sec = 0;
int battery = 10;
int count = 0;
char *device = "Edwin-watch";

char* b = "Notification: Crocin Time ";
boolean blinking = false;

boolean notificationExists = true;


void mqtt_callback(char *topic, byte *payload, unsigned int length){
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println();
    Serial.println("-----------------------");
}

NTPClient timeClient(ntpUDP, (long)(3600 * 5.5));
DisplaySystem displaySystem;
ConnectionSystem connectionSystem(device, mqtt_callback);


void setup() {
    Serial.begin(115200);

    connectionSystem.searchAndConnectWifi(&displaySystem);
    connectionSystem.connectToMQTT();
    timeClient.begin();


    lastSecTime = millis();

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


        count += 1;

        char buf[100];
        String s = "count : =  ";
        s.toCharArray(buf, s.length());
        String m1 = String(count);

        m1.toCharArray(buf +  s.length() - 1 , 100 - s.length()+1);

        // connectionSystem.sendMessage("esp/test", buf );
    }
    batteryUpdate();
    drawNormalScreen();


    connectionSystem.loop();    // put on top later
    connectionSystem.reconnectOnDisconnect(2000);
}
