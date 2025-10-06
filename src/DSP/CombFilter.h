#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class CombFilter
{
  public:
    void prepare(double sampleRate, int samplesPerBlock, int delayInSamples);
    void reset();
    void process(float& sample, float decayFactor);

  private:
    std::vector<float> delayBuffer;
    int delayBufferWritePos = 0;
    double sampleRate = 0.0;
    int delayInSamples = 0;
};
