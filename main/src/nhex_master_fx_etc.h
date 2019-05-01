#pragma once

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioMixer4              fx_flange_inst_mix_1;         //xy=456,355
AudioMixer4              fx_flange_inst_mix_2;         //xy=456,420
AudioMixer4              fx_shaper_inst_mix_1;         //xy=457,227
AudioMixer4              fx_shaper_inst_mix_2;         //xy=457,291
AudioMixer4              fx_verb_inst_mix_1;        //xy=461,483
AudioMixer4              fx_verb_inst_mix_2;        //xy=463,548
AudioMixer4              inst_mix_1;        //xy=493,88
AudioMixer4              inst_mix_2;        //xy=493,157
AudioMixer4              fx_verb_merge_mix;         //xy=733,416
AudioMixer4              fx_flange_merge_mix;         //xy=737,351
AudioMixer4              fx_shaper_merge_mix;         //xy=738,285
AudioMixer4              instrument_merge_mix;         //xy=740,206
AudioEffectFreeverb      fx_verb;      //xy=918,415
AudioEffectWaveshaper    fx_shaper;     //xy=919,285
AudioEffectFlange        fx_flanger;        //xy=919,350
AudioMixer4              final_mix;         //xy=1098,268
AudioOutputI2S           audioOut;           //xy=1101,175
AudioConnection          patchCord1(fx_flange_inst_mix_1, 0, fx_flange_merge_mix, 0);
AudioConnection          patchCord2(fx_flange_inst_mix_2, 0, fx_flange_merge_mix, 1);
AudioConnection          patchCord3(fx_shaper_inst_mix_1, 0, fx_shaper_merge_mix, 0);
AudioConnection          patchCord4(fx_shaper_inst_mix_2, 0, fx_shaper_merge_mix, 1);
AudioConnection          patchCord5(fx_verb_inst_mix_1, 0, fx_verb_merge_mix, 0);
AudioConnection          patchCord6(fx_verb_inst_mix_2, 0, fx_verb_merge_mix, 1);
AudioConnection          patchCord7(inst_mix_1, 0, instrument_merge_mix, 0);
AudioConnection          patchCord8(inst_mix_2, 0, instrument_merge_mix, 1);
AudioConnection          patchCord9(fx_verb_merge_mix, fx_verb);
AudioConnection          patchCord10(fx_flange_merge_mix, fx_flanger);
AudioConnection          patchCord11(fx_shaper_merge_mix, fx_shaper);
AudioConnection          patchCord12(instrument_merge_mix, 0, final_mix, 0);
AudioConnection          patchCord13(fx_verb, 0, final_mix, 3);
AudioConnection          patchCord14(fx_verb, 0, fx_shaper_inst_mix_2, 3);
AudioConnection          patchCord15(fx_verb, 0, fx_flange_inst_mix_2, 3);
AudioConnection          patchCord16(fx_shaper, 0, final_mix, 1);
AudioConnection          patchCord17(fx_shaper, 0, fx_flange_inst_mix_2, 2);
AudioConnection          patchCord18(fx_shaper, 0, fx_verb_inst_mix_2, 2);
AudioConnection          patchCord19(fx_flanger, 0, final_mix, 2);
AudioConnection          patchCord20(fx_flanger, 0, fx_shaper_inst_mix_2, 2);
AudioConnection          patchCord21(fx_flanger, 0, fx_verb_inst_mix_2, 3);
AudioConnection          patchCord22(final_mix, 0, audioOut, 0);
AudioConnection          patchCord23(final_mix, 0, audioOut, 1);
AudioControlSGTL5000     audioShield;     //xy=1093,213
// GUItool: end automatically generated code
