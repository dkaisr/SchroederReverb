#include "CombFilter.h"

void
CombFilter::prepare(double sampleRate, int samplesPerBlock, int delayInSamples)
{
    int maxDelayTimeMs = 50;
    int maxDelaySamples = static_cast<int>(sampleRate * maxDelayTimeMs / 1000.0);

    delayBuffer.resize(maxDelaySamples, 0.0f);
    std::fill(delayBuffer.begin(), delayBuffer.end(), 0.0f);
    delayBufferWritePos = 0;
    this->sampleRate = sampleRate;
    this->delayInSamples = delayInSamples;
}

void
CombFilter::process(float& sample, float decayFactor)
{    
    int delayBufferLength = (int)delayBuffer.size();
    int delayReadPos
        = (delayBufferWritePos - delayInSamples + delayBufferLength) % delayBufferLength;
    float delayedSample = delayBuffer[delayReadPos];

    float gain = std::pow(10.0f, -3.0f * delayInSamples / (decayFactor * sampleRate));
    
    delayBuffer[delayBufferWritePos] = sample + gain * delayedSample;
    sample = delayedSample;

    delayBufferWritePos = (delayBufferWritePos + 1) % delayBufferLength;
}
