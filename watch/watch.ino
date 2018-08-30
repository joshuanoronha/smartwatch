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
bool pixel_map[] = {

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 
  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
  1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 
  0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

const char *ssid     = "abc";
const char *password = "joshua1234";
long lastSecTime = 0;

WiFiUDP ntpUDP;
int sec = 0;
int battery = 10;
boolean blinking = false;
boolean notificationExists = true;
// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP, (long)(3600 * 5.5));


int charOffset , pixelOffset;
int lastMarqueeCall;
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
  Serial.println ( "\n Connecting" );

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  lastSecTime = millis();
  timeClient.begin();


  pixelOffset = 0;
  charOffset = 0;
  lastMarqueeCall = millis();
  display.clearDisplay();

}


void loop() {
  
  display.clearDisplay();

  timeClient.update();
  String c = timeClient.getFormattedTime();
  const char *time = c.c_str();
  drawStr(42, 0, const_cast<char*>(time));

  if (millis() - lastSecTime >= 1000)  {
    sec++;
    lastSecTime = millis();
    //    Serial.println( sec);
    blinking = !blinking;
  }
  
  if (sec == 67)
  {
    sec = 0;
    battery--;
    Serial.print("battery ");
    Serial.print( battery);

    if (battery < 3) battery = 3;
  }
  drawBattery(sec, battery);
  display.drawFastHLine(3, 8, 120, 1);
  heart(15, 14);
  char b[] = "Tommy is a good boy.";
  char bx[] = "by edwin";


  marquee_helper(10, 24, b, 19);
  marquee_helper(35, 13, bx, 4);

  //  display.fillRect(5, 24, 5, 7, 0);
  //  display.fillRect(113, 24, 5, 7, 0);

  if (notificationExists)
  {

    notification(blinking);

  }
  wifiSymbolDisplay(10,10);

  display.display();
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

void drawStrOffset(uint8_t x, uint8_t y, char* str) {
  display.setCursor(x, y);  /* Set x,y coordinates */
  display.println(str);
}


void marquee_helper(int x, int y, char* completeString, int dispSpace) {
  char output[30];

  if (millis() - lastMarqueeCall > 100) {
    pixelOffset -= 1;
    lastMarqueeCall  = millis();
  }
  if ( pixelOffset  == -5)  {
    charOffset += 1;
    pixelOffset = 0;
  }
  marquee(completeString, charOffset, dispSpace, output);
//
//  Serial.print(output);
//  Serial.print(" - " );
//
//  Serial.print(charOffset);
//  Serial.print(" - " );
//  Serial.println(x + pixelOffset);

  drawStr(x + pixelOffset, y, output);
  display.fillRect(x-5, y, 5, 7, 0);
  display.fillRect(x+dispSpace*6-5, y, 5, 7, 0);
//  marquee_helper(10, 24, b, 18);

}

void marquee(char *y, int offset, int dispSpace, char* output)
{
  int len = strlen(y);
  //  char output[30];

  for ( int i = 0; i < dispSpace; i++ ) {
    output[i] = y[(offset + i) % len];
  }

  output[dispSpace] = 0;
}

void wifiSymbolDisplay(int x,int y)
{
  int i,j=0;
  for (i=0;i<1024;i++)
  {
    if (i%32==0)
      j++;
    display.drawPixel(x+(i%32),y+j,1);
  }
}

