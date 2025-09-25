#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class CombFilter {
public:
  void prepare(double sampleRate, int samplesPerBlock);
  void reset();
  void process(float* sample);

private:
  std::vector<float> delayBuffer;
  int delayBufferWritePos = 0;
  int delayInSamples = 0;
  float gain = 0.7f;
};
