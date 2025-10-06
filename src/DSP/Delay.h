#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class Delay
{
  public:
    void prepare(double sampleRate, int samplesPerBlock);
    void reset();
    void process(float& sample);
    void setDelayMs(float ms);

  private:
    std::vector<float> delayBuffer;
    int delayBufferWritePos = 0;
    int delayInSamples = 0;
    double sampleRate = 0.0;
};
