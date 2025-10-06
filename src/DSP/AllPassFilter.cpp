#include "AllPassFilter.h"

void
AllPassFilter::prepare(double sampleRate, int samplesPerBlock, int delayInSamples, float gain)
{
    int maxDelayTimeMs = 100;
    int maxDelaySamples = static_cast<int>(sampleRate * maxDelayTimeMs / 1000.0);

    delayBuffer.resize(maxDelaySamples, 0.0f);
    std::fill(delayBuffer.begin(), delayBuffer.end(), 0.0f);
    delayBufferWritePos = 0;
    this->delayInSamples = delayInSamples;
    this->gain = gain;
}

void
AllPassFilter::process(float& sample)
{
    int delayBufferLength = (int)delayBuffer.size();
    int delayReadPos
        = (delayBufferWritePos - delayInSamples + delayBufferLength) % delayBufferLength;
    float delayedSample = delayBuffer[delayReadPos];
    
    delayBuffer[delayBufferWritePos] = sample + gain * delayedSample;
    sample = -gain * sample + delayedSample;

    delayBufferWritePos = (delayBufferWritePos + 1) % delayBufferLength;
}
