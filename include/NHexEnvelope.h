#include "Arduino.h"
#include "AudioStream.h"
#include "utility/dspinst.h"

#define SAMPLES_PER_MSEC (AUDIO_SAMPLE_RATE_EXACT / 1000.0)
#define IDLE -1
#define STAGE_0 0
#define STAGE_1 1
#define STAGE_2 2

class NHexEnvelope : public AudioStream
{
public:
  NHexEnvelope() : AudioStream(1, inputQueueArray)
  {
    state(0);
    stage0Level(1.0f);
    stage0Rate(0);
    stage1Level(0.0f);
    stage1Rate(50);
    loop(false);
    invert(false);
    retrigFromStart(true);
  }
  void noteOn();
  void noteOff();
  void state(uint8_t state);
  void stage0Level(float level);
  void stage0Rate(int16_t ms);
  void stage1Level(float level);
  void stage1Rate(int16_t ms);
  void loop(bool loop);
  void invert(bool polarity);
  void retrigFromStart(bool retrigFromStart);
  using AudioStream::release;
  virtual void update(void);

private:
  audio_block_t *inputQueueArray[1];
  uint8_t envState = IDLE; // see defines above.
  int32_t envPrevious;     // previous sample value.
  int32_t envCurrent;      // current sample value.
  int32_t envDecrement;    // how each sample deviates from previous.
  int16_t buffersElapsedThisStage;
  bool looping;
  bool inverted;
  bool trigFromStart;
  float envLevel0;
  uint16_t envRate0;
  float envLevel1;
  uint16_t envRate1;
};

#undef SAMPLES_PER_MSEC
