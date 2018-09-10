#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include "image_arrays.h"
#define OLED_RESET D5


Adafruit_SSD1306 display(OLED_RESET);


class DisplaySystem {
    
   public : 

    int charOffset,
    pixelOffset;
    int lastMarqueeCall;

    void marqueeGlobalSetup()   {

        pixelOffset = 0;
        charOffset = 0;
        lastMarqueeCall = millis();

    }
   void drawStr(uint8_t x, uint8_t y, char * str) {
        display.setCursor(x, y);/* Set x,y coordinates */
        display.println(str);
    }

    void drawBattery(int sec, int battery) {
        display.fillRect(110, 1, battery, 6, 1);
        display.drawRect(110, 1, 15, 6, 1);
        display.fillRect(125, 3, 2, 2, 1);
    }

    void notification(boolean flag) {
        if (flag) {
            display.fillRect(15, 1, 2, 4, 1);
            display.fillRect(15, 6, 2, 1, 1);
            //    display.drawCircle(20,4,4,1);/
        }
    }

    void heart(int x, int y) {
        for (int i = 0; i < 12; i++) {

            for (int j = 0; j < 6; j++) {

                if (heart_mat[j][(int)i / 2]) {
                    display.drawPixel(x + i, y + j, 1);

                }
            }
        }
    }

    void drawHeartBeat(int x, int y, int beats)    {
        heart(x, y);
        display.setCursor(x + 20, y); /* Set x,y coordinates */
        display.println(beats);
    }


    void drawStrOffset(uint8_t x, uint8_t y, char * str) {
        display.setCursor(x, y);/* Set x,y coordinates */
        display.println(str);
    }

    void marquee_helper(int x, int y, char * completeString, int dispSpace) {
        char output[30];

        if (millis() - lastMarqueeCall > 100) {
            pixelOffset -= 1;
            lastMarqueeCall = millis();
        }
        if (pixelOffset == -5) {
            charOffset += 1;
            pixelOffset = 0;
        }
        marquee(completeString, charOffset, dispSpace, output);

        drawStr(x + pixelOffset, y, output);
        display.fillRect(x - 5, y, 5, 7, 0);
        display.fillRect(x + dispSpace * 6 - 5, y, 5, 7, 0);

    }

    void marquee(char * y, int offset, int dispSpace, char * output) {
        int len = strlen(y);
        //  char output[30];

        for (int i = 0; i < dispSpace; i++) {
            output[i] = y[(offset + i) % len];
        }

        output[dispSpace] = 0;
    }

    void wifiSymbolDisplay(int x, int y, float scaling) {
        for (int i = 0; i < 32 * scaling; i++) {
            for (int j = 0; j < 32 * 2 * scaling; j++) {
                if (wifi_pixel_map[(int)(i / (scaling))][(int)(j / (2 * scaling))]) {
                    display.drawPixel(x + j, y + i, 1);

                }
            }

        }
    }
    DisplaySystem() {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);/* Initialize display with address 0x3C */
        display.clearDisplay();/* Clear display */
        display.setTextSize(1);/* Select font size of text. Increases with size of argument. */
        display.setTextColor(WHITE);/* Color of text*/

        marqueeGlobalSetup();
    }

    void clearDisplay() {
        display.clearDisplay();

    }

    void drawStartScreen(const char * ssid) {

      drawBar();

      wifiSymbolDisplay(1, 10, 0.5);
      drawStr(10, 0, "Connecting to Wifi");
      drawStr(45, 11, "SSID:");
      drawStr(45, 20, const_cast<char *>(ssid));
      display.display();

    }

    void drawBar()  {
          display.drawFastHLine(3, 8, 120, 1);

    }

};