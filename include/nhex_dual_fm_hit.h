#pragma once

#include "Audio.h"
/*
3-stage invertable envelope with rate and level control for each stage, 
*/
class NHexDualFMHit
{
private:
  AudioSynthWavetable carrier;
  AudioSynthWavetable modulator;
  AudioEffectEnvelope amp_envelope1;
  AudioEffectEnvelope amp_envelope2;
  AudioEffectEnvelope mod_envelope1;
  AudioEffectWaveshaper waveShaper;
  AudioMixer4 out_mixer;

  AudioConnection *patch00;
  AudioStream *audioInput;
  AudioStream *audioOutput;
  AudioStream *modulationIn0;
  AudioStream *modulationIn1;
  AudioStream *modulationIn2;
  AudioStream *modulationIn3;
  AudioStream *modulationIn4;
  AudioStream *modulationIn5;
  AudioStream *modulationOut0;
  AudioStream *modulationOut1;
  AudioStream *modulationOut2;
  AudioStream *modulationOut3;
  AudioStream *modulationOut4;
  AudioStream *modulationOut5;

public:
  NHexDualFMHit(AudioStream &from, unsigned char from_channel, AudioStream &to, unsigned char to_channel);
  void carrierFrequency(float freq);
  void carrierPhase(float angle);
  void carrierAmplitude(float level);
  void modulatorFrequency(float freq);
  void modulatorPhase(float angle);
  void modulatorAmplitude(float level);

  void carrierModulation(float level);
  void modulatorFeedback(float level);
  void modulatorPhaseReset(float onOff);
  void carrierWaveform(float index);   // choose form any of the waveforms
  void modulatorWaveform(float index); // choose form any of the waveforms

  void waveShapeSend(float level);
  void waveShapeAmount(float amount);
  void waveShapeVolume(float level);
  void masterVolume(float level);

  void env1Length1(float length);
  void env1Level1(float level);
  void env1Length2(float rate);
  void env1Level2(float level);
  void env1Length3(float rate);
  void env1Level3(float level);
  void env1Loop(float onOff);
  void env1Invert(float onOff);
  void env1Sustain(float onOff);
  void env1Shape1(float index); // linear, exponential, log
  void env1Shape2(float index); // linear, exponential, log
  void env1Shape3(float index); // linear, exponential, log

  void env2Length1(float length);
  void env2Level1(float level);
  void env2Length2(float rate);
  void env2Level2(float level);
  void env2Length3(float rate);
  void env2Level3(float level);
  void env2Loop(float onOff);
  void env2Invert(float onOff);
  void env2Sustain(float onOff);
  void env2Shape1(float index); // linear, exponential, log
  void env2Shape2(float index); // linear, exponential, log
  void env2Shape3(float index); // linear, exponential, log

  void env3Length1(float length);
  void env3Level1(float level);
  void env3Length2(float rate);
  void env3Level2(float level);
  void env3Length3(float rate);
  void env3Level3(float level);
  void env3Loop(float onOff);
  void env3Invert(float onOff);
  void env3Sustain(float onOff);
  void env3Shape1(float index); // linear, exponential, log
  void env3Shape2(float index); // linear, exponential, log
  void env3Shape3(float index); // linear, exponential, log

  ~NHexDualFMHit();
};

NHexDualFMHit::NHexDualFMHit(AudioStream &from, unsigned char from_channel, AudioStream &to, unsigned char to_channel)
{
  patch00 = new AudioConnection(from, from_channel, to, to_channel);
}

NHexDualFMHit::~NHexDualFMHit()
{
}
