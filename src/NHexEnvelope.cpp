#include <Arduino.h>
#include "../include/NHexEnvelope.h"

void NHexEnvelope::noteOn(void)
{
  __disable_irq();

  __enable_irq();
}

void NHexEnvelope::noteOff(void)
{
  __disable_irq();

  __enable_irq();
}

void NHexEnvelope::update(void)
{
  audio_block_t *block;
  uint32_t *p, *end;
  block = receiveWritable();
  if (!block)
    return;
  if (state == IDLE)
  {
    release(block);
    return;
  }
  calculateEnvIncrement();
  p = (uint32_t *)(block->data);
  end = p + AUDIO_BLOCK_SAMPLES / 2;

  while (p < end)
  {
  }
  transmit(block);
  release(block);
}

void calculateEnvIncrement()
{
  int32_t currentStageEndLevel;
  uint8_t currentStageRate;
  uint8_t msElapsed;
  if (envState == -1)
  {
  }
}

void calculateState()
{
  int32_t currentPosition;
}