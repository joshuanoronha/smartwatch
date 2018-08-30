
#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
#include<string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET D5
Adafruit_SSD1306 display(OLED_RESET);

const char *ssid     = "abc";
const char *password = "joshua1234";

WiFiUDP ntpUDP;
int sec = 0;
int battery = 10;
boolean blinking = false;
boolean notificationExists = true;
// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP, (long)(3600 * 5.5));

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup() {
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
  drawStr(42, 0, const_cast<char*>(time));
  sec++;
  Serial.print( sec);

  if (sec == 5)
  {
    sec = 0;
    battery--;
    Serial.print("battery ");
    Serial.print( battery);

    if (battery < 3) battery = 3;
  }
  drawBattery(sec, battery);
  if (notificationExists)
  {
    blinking = !blinking;
    notification(blinking);
  }
  display.drawFastHLine(3, 8, 120, 1);
  heart(15, 14);
  char b[] = "Tommy is a good boy.";
  marquee(b , 6 , 10);
  display.display();
  delay(1000);
}


void drawStr(uint8_t x, uint8_t y, char* str) {
  display.setCursor(x, y);  /* Set x,y coordinates */
  display.println(str);
}

void drawBattery(int sec, int battery)
{
  display.fillRect(110, 1, battery, 6, 1);
  display.drawRect(110, 1, 15, 6, 1);
  display.fillRect(125, 3, 2, 2, 1);
}

void notification(boolean flag)
{
  if (flag)
  {
    display.fillRect(15, 1, 2, 4, 1);
    display.fillRect(15, 6, 2, 1, 1);
    //    display.drawCircle(20,4,4,1);/
  }
}

int heart_mat[6][6] = { {0, 1, 0 , 0, 1, 0},
  {1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 0, 0}
};

void heart(int x, int y)
{
  for (int i = 0; i < 12; i ++)  {

    for ( int j = 0; j < 6; j++) {

      if (heart_mat[j][(int)i / 2]) {
        display.drawPixel(x + i, y + j, 1);

      }
    }
  }
}

void marquee(char *y, int offset, int dispSpace)
{
  int len = strlen(y);
  char output[30];

  for ( int i = 0; i < dispSpace; i++ ) {
    output[i] = y[(offset + i) % len];
  }

  output[dispSpace] = 0;
  drawStr(0, 24, output);
}

