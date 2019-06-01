#include "../include/main.h"

const uint8_t SDCARD_CS_PIN = 10;
const uint8_t SDCARD_MOSI_PIN = 7;
const uint8_t SDCARD_SCK_PIN = 14;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// GUItool: begin automatically generated code
NHexBassHit bassHitSynth; //xy=87,208
AudioSynthWaveformDc dc;
NHex3StageEnvelope testEnv;
AudioMixer4 bassHitMixer; //xy=508,
AudioOutputI2S audioOut;  //xy=658,3 67
AudioConnection c28(dc, 0, testEnv, 0);
AudioConnection c29(testEnv, 0, bassHitMixer, 1);
AudioConnection c30(bassHitSynth, 0, bassHitMixer, 0);
AudioConnection c32(bassHitMixer, 0, audioOut, 0);
// AudioConnection c33(bassHitMixer, 0, audioOut, 1);
AudioControlSGTL5000 audioShield; //xy=108,617
// GUItool: end automatically generated code
// NHexDualFMHit *dualFMHit1;

elapsedMillis ledOnMillis;
bool midiActivity = false;
float basicNyquist = (float)220050;

byte bassHitSynthNote1 = 41;
byte bassHitSynthNote2 = 73;

byte bassHitSynthPTCHCC00 = 28;
byte bassHitSynthPTCHCC01 = 29;
byte bassHitSynthPTCHCC02 = 30;
byte bassHitSynthPTCHCC03 = 31;

Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(115200);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);

  if (!(SD.begin(SDCARD_CS_PIN)))
  {
    Serial.print("Cannot access SD card");
  }
  if (!screen.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, true))
  {
    Serial.print("Cannot begin display");
  }
  screen.dim(true);
  showNeoHexaneSplash(&screen);
  pinMode(13, OUTPUT); // LED pin
  digitalWrite(13, LOW);
  usbMIDI.setHandleNoteOn(myNoteOn);
  // usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleControlChange(myControlChange);
  AudioMemory(60);
  AudioNoInterrupts();

  // dualFMHit1 = new NHexDualFMHit(bassHitMixer, 0, audioOut, 1);

  bassHitSynth.frequency(50);
  bassHitSynth.length(1500);
  bassHitSynth.secondMix(0.5);
  bassHitSynth.pitchMod(0.65);
  bassHitMixer.gain(0, 0.8);
  testEnv.delay(0.0f); // default values...
  testEnv.attack(1500.5f);
  testEnv.hold(800.5f);
  testEnv.decay(350.0f);
  testEnv.sustain(8.0f);
  testEnv.release(3000.0f);
  testEnv.releaseNoteOn(5.0f);
  audioShield.enable();
  audioShield.volume(0.8);
  AudioInterrupts();
  Serial.println("setup");
}

void loop()
{
  usbMIDI.read();

  // blink the LED when any activity has happened
  if (midiActivity)
  {
    digitalWriteFast(13, HIGH); // LED on
    ledOnMillis = 0;
  }
  if (ledOnMillis > 15)
  {
    digitalWriteFast(13, LOW); // LED off
  }
  midiActivity = false;
}

void myNoteOn(byte channel, byte note, byte velocity)
{
  // When using MIDIx4 or MIDIx16, usbMIDI.getCable() can be used
  // to read which of the virtual MIDI cables received this message.
  // Serial.print("Note On, ch=");
  // Serial.print(channel, DEC);
  // Serial.print(", note=");
  // Serial.print(note);
  // Serial.print(", velocity=");
  // Serial.println(velocity, DEC);
  if (note == bassHitSynthNote1)
  {
    midiActivity = true;
    bassHitSynth.noteOn();
    testEnv.noteOn();
  }
  if (note == bassHitSynthNote2)
  {
    midiActivity = true;
  }
}

void myNoteOff(byte channel, byte note, byte velocity)
{
  Serial.print("Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  if (note == bassHitSynthNote1 || note == bassHitSynthNote2)
  {
    midiActivity = true;
  }
}

void myControlChange(byte channel, byte control, byte value)
{
  Serial.print("Control Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.println(value, DEC);
  midiActivity = true;
  if (control == bassHitSynthPTCHCC00)
  {
    float val = convertRange((float)(0), (float)(127), (float)(0), (float)(1), value);
    Serial.println(val);
    bassHitSynth.pitchMod(val);
    midiActivity = true;
  }
  if (control == bassHitSynthPTCHCC01)
  {
    float val = convertRange((float)(0), (float)(127), (float)(0.0), (float)(1.0), value);
    Serial.print(val);
    bassHitSynth.secondMix(val);
    midiActivity = true;
  }
  if (control == bassHitSynthPTCHCC02)
  {
    float val = convertRange((float)(0), (float)(127), (float)(20), 128, value);
    Serial.print(val);
    bassHitSynth.frequency(val);
    midiActivity = true;
  }
  if (control == bassHitSynthPTCHCC03)
  {
    int32_t val = convertRange((int32_t)(0), (int32_t)(127), (int32_t)(20), (int32_t)(5000), (int32_t)(value));
    Serial.print(val);
    bassHitSynth.length(val);
    midiActivity = true;
  }
}
void showNeoHexaneSplash(Adafruit_SSD1306 *screen)
{
  screen->clearDisplay();
  screen->setTextColor(WHITE);
  screen->setTextSize(2);  // Draw 2X-scale text
  screen->setCursor(9, 7); // Start at top-left corner
  screen->print("NeoHexane");
  screen->setTextSize(1);
  screen->setCursor(20, 35);
  screen->println(F("V O I D"));
  screen->setCursor(38, 50);
  screen->println(F("R U N N E R"));
  screen->display();
}

float convertRange(
    float originalStart, float originalEnd,
    float newStart, float newEnd,
    float value)
{
  float range1 = originalEnd - originalStart;
  float range2 = newEnd - newStart;
  float finalValue = ((value - originalStart) * range2) / range1 + newStart;
  return finalValue;
}

int32_t convertRange(
    int32_t originalStart, int32_t originalEnd,
    int32_t newStart, int32_t newEnd,
    int32_t value)
{
  int32_t range1 = originalEnd - originalStart;
  int32_t range2 = newEnd - newStart;
  int32_t finalValue = ((value - originalStart) * range2) / range1 + newStart;
  return finalValue;
}
