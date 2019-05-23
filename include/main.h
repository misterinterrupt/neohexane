#include <Arduino.h>
#include <Wire.h>
#include <Audio.h>
#include "nhex_bass_hit.h"
#include "nhex_controls.cpp"
#include "../include/nhex_dual_fm_hit.h"
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void myNoteOn(byte channel, byte note, byte velocity);
void myNoteOff(byte channel, byte note, byte velocity);
void myControlChange(byte channel, byte control, byte value);
void showNeoHexaneSplash(Adafruit_SSD1306 *screen);
float convertRange(
    float originalStart, float originalEnd,
    float newStart, float newEnd,
    float value);
int32_t convertRange(
    int32_t originalStart, int32_t originalEnd,
    int32_t newStart, int32_t newEnd,
    int32_t value);
