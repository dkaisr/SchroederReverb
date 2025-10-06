#include "Delay.h"

void
Delay::prepare(double sampleRate, int samplesPerBlock)
{
    int maxDelayTimeMs = 2000;
    int maxDelaySamples = static_cast<int>(sampleRate * maxDelayTimeMs / 1000.0);

    delayBuffer.resize(maxDelaySamples, 0.0f);
    std::fill(delayBuffer.begin(), delayBuffer.end(), 0.0f);
    delayBufferWritePos = 0;
    this->sampleRate = sampleRate;
}

void
Delay::process(float& sample)
{
    if (delayInSamples == 0)
    {
        return;
    }
    int delayBufferLength = (int)delayBuffer.size();
    int delayReadPos
        = (delayBufferWritePos - delayInSamples + delayBufferLength) % delayBufferLength;
    float delayedSample = delayBuffer[delayReadPos];

    delayBuffer[delayBufferWritePos] = sample;
    sample = delayedSample;

    delayBufferWritePos = (delayBufferWritePos + 1) % delayBufferLength;
}

void
Delay::setDelayMs(float ms)
{
    delayInSamples = static_cast<int>(sampleRate * (ms / 1000.0f));
}
