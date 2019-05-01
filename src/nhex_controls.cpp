
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// #define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// class nhex_controls
// {
// private:
//   /* data */
// public:
//   nhex_controls(Adafruit_SSD1306 *screen);
//   void showNeoHexaneSplash();

//   ~nhex_controls();
// };

// nhex_controls::nhex_controls(Adafruit_SSD1306 *screen) :
// {
// }

// nhex_controls::~nhex_controls()
// {
// }

// void showNeoHexaneSplash(Adafruit_SSD1306 *screen)
// {
//   screen->clearDisplay();
//   screen->setTextColor(WHITE);
//   screen->setTextSize(2);  // Draw 2X-scale text
//   screen->setCursor(9, 7); // Start at top-left corner
//   screen->print("NeoHexane");
//   screen->setTextSize(1);
//   screen->setCursor(20, 35);
//   screen->println(F("V O I D"));
//   screen->setCursor(38, 50);
//   screen->println(F("R U N N E R"));
//   screen->display();
// }
