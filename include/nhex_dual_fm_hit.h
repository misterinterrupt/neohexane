#pragma once

#include "Audio.h"

class NHexDualFMHit
{
private:
  AudioSynthWaveformSineModulated sine_carrier1;
  AudioSynthWaveformSine sine_modulator1;
  AudioEffectEnvelope amp_envelope1;
  AudioEffectEnvelope amp_envelope2;
  AudioEffectEnvelope mod_envelope1;
  AudioMixer4 out_mixl;
  AudioConnection *patch00;

public:
  NHexDualFMHit(AudioStream &from, unsigned char from_channel, AudioStream &to, unsigned char to_channel);
  void carrierFrequency(float freq);
  void carrierPhase(float angle);
  void carrierAmplitude(float n);
  void modulatorFrequency(float freq);
  void modulatorPhase(float angle);
  void modulatorAmplitude(float n);
  ~NHexDualFMHit();
};

NHexDualFMHit::NHexDualFMHit(AudioStream &from, unsigned char from_channel, AudioStream &to, unsigned char to_channel)
{
  patch00 = new AudioConnection(from, from_channel, to, to_channel);
}

NHexDualFMHit::~NHexDualFMHit()
{
}
