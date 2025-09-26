#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "CombFilter.h"
#include "AllPassFilter.h"

class SchroederReverb {
public:
  void prepare(double sampleRate, int samplesPerBlock);
  void reset();
  void process(float* sample);

private:
  CombFilter combFilter0, combFilter1, combFilter2, combFilter3;
  AllPassFilter allPassFilter0, allPassFilter1;
};
