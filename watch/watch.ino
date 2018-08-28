#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET D5
Adafruit_SSD1306 display(OLED_RESET);

const char *ssid     = "TP-Link_6329";
const char *password = "2051313908";

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP, (long)(3600*5.5));

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /* Initialize display with address 0x3C */
  display.clearDisplay();  /* Clear display */
  display.setTextSize(1);  /* Select font size of text. Increases with size of argument. */
  display.setTextColor(WHITE);  /* Color of text*/
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();
  String c = timeClient.getFormattedTime();
  display.clearDisplay();
  const char *time = c.c_str();
  drawStr(80,15,const_cast<char*>(time));
 Serial.println(new_time);
  display.display();
  delay(1000);
}


void drawStr(uint8_t x, uint8_t y, char* str){
  display.setCursor(x, y);  /* Set x,y coordinates */
  display.println(str);
}


