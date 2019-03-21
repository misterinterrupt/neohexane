#include <Audio.h>
#include "./bass_hit.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>

const int SDCARD_CS_PIN = 10;
const int SDCARD_MOSI_PIN = 7;
const int SDCARD_SCK_PIN = 14;

// GUItool: begin automatically generated code
NeoHexaneBassHit         bassHitSynth;          //xy=87,308
AudioEffectFlange        bassHitFlange;        	//xy=283,408
AudioMixer4              bassHitMixer;         	//xy=508,
AudioOutputI2S           audioOut;           		//xy=658,3 67
AudioConnection          c0(bassHitSynth, 0, bassHitMixer, 0);
// AudioConnection          c1(bassHitFlange, 0, bassHitMixer, 0);
AudioConnection          c2(bassHitMixer, 0, audioOut, 0);
AudioConnection          c3(bassHitMixer, 0, audioOut, 1);
AudioControlSGTL5000     audioShield;     		//xy=208,617
// GUItool: end automatically generated code

elapsedMillis ledOnMillis;
bool midiActivity = false;
byte bassHitSynthNote1 = 41;
byte bassHitSynthNote2 = 73;

void setup()
{
  Serial.begin(115200);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);

  if(!(SD.begin(SDCARD_CS_PIN))) {
    Serial.print("Cannot access SD card");
  }
  pinMode(13, OUTPUT); // LED pin
  digitalWrite(13, LOW);
  usbMIDI.setHandleNoteOn(myNoteOn);
  // usbMIDI.setHandleNoteOff(myNoteOff);
  // usbMIDI.setHandleControlChange(myControlChange);
  AudioMemory(15);
  AudioNoInterrupts();
  bassHitSynth.frequency(60);
  bassHitSynth.length(1500);
  bassHitSynth.secondMix(0.4);
  bassHitSynth.pitchMod(0.55);
  audioShield.enable();
  bassHitMixer.gain(0, 0.9);
  audioShield.volume(0.9);
  AudioInterrupts();
  Serial.print("setup");
}

void loop()
{
  usbMIDI.read();

  // blink the LED when any activity has happened
  if (midiActivity) {
    digitalWriteFast(13, HIGH); // LED on
    ledOnMillis = 0;
  }
  if (ledOnMillis > 15) {
    digitalWriteFast(13, LOW);  // LED off
  }
  midiActivity = false;
}

void myNoteOn(byte channel, byte note, byte velocity) {
  // When using MIDIx4 or MIDIx16, usbMIDI.getCable() can be used
  // to read which of the virtual MIDI cables received this message.
  Serial.print("Note On, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  if(note == bassHitSynthNote1 || note == bassHitSynthNote2) {
    midiActivity = true;
    bassHitSynth.noteOn();
  }
}

void myNoteOff(byte channel, byte note, byte velocity) {
  Serial.print("Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  if(note == bassHitSynthNote1 || note == bassHitSynthNote2) {
    midiActivity = true;
  }
}

void myControlChange(byte channel, byte control, byte value) {
  Serial.print("Control Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.println(value, DEC);
  // midiActivity = true;
}
