#pragma once

#include "AllPassFilter.h"
#include "CombFilter.h"
#include "Delay.h"
#include <juce_audio_processors/juce_audio_processors.h>

class SchroederReverb
{
  public:
    void prepare(double sampleRate, int samplesPerBlock);
    void reset();
    void process(float& sample, float dryWetMix, float decayFactor);

    void setPreDelayMs(float ms);

  private:
    CombFilter combFilter0, combFilter1, combFilter2, combFilter3;
    AllPassFilter allPassFilter0, allPassFilter1;
    Delay preDelay;
};
