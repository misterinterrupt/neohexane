#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     bassHitSynth;          //xy=87,308
AudioEffectFlange        bassHitFlange;        	//xy=283,408
AudioMixer4              bassHitMixer;         	//xy=508,
AudioOutputI2S           audioOut;           		//xy=658,367
AudioConnection          c0(bassHitSynth, 0, bassHitFlange, 0);
AudioConnection          c1(bassHitFlange, 0, bassHitMixer, 0);
AudioConnection          c2(bassHitMixer, 0, audioOut, 0);
AudioConnection          c3(bassHitMixer, 0, audioOut, 1);
AudioControlSGTL5000     audioShield;     		//xy=208,617
// GUItool: end automatically generated code

elapsedMillis ledOnMillis;
bool midiActivity = false;
uint8_t bassHitSynthNote = 41;

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT); // LED pin
  digitalWrite(13, LOW);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleControlChange(myControlChange);
  AudioMemory(8);
  audioShield.enable();
  audioShield.volume(0.8);
  bassHitMixer.gain(0, 0.8);

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
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  midiActivity = true;
}

void myNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  Serial.print("Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  if(note == bassHitSynthNote) {

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
  midiActivity = true;
}
