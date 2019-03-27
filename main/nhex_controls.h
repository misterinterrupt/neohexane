#pragma once

#ifndef nhex_controls_h_
#define nhex_controls_h_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

class NHexControls
{
public:
  NHexControls(Adafruit_SSD1306 &libref) : display(libref)
  {
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  }
  void setup(void)
  {
    testdrawstyles();
  }

private:
  void testdrawstyles(void) {
    this->display.clearDisplay();

    this->display.setTextSize(1);             // Normal 1:1 pixel scale
    this->display.setTextColor(WHITE);        // Draw white text
    this->display.setCursor(0,0);             // Start at top-left corner
    this->display.println(F("NHEX"));

    this->display.setTextColor(BLACK, WHITE); // Draw 'inverse' text
    this->display.println("percussion synth module");

    this->display.setTextSize(2);             // Draw 2X-scale text
    this->display.setTextColor(WHITE);
    this->display.print("NitroSky");

    this->display.display();
  }

  Adafruit_SSD1306& display;
};
#endif