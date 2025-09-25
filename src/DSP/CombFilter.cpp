#include "CombFilter.h"

void CombFilter::prepare(double sampleRate, int samplesPerBlock) {
  int maxDelayTimeMs = 100;
  int maxDelaySamples = static_cast<int>(sampleRate * maxDelayTimeMs / 1000.0);

  delayBuffer.resize(maxDelaySamples, 0.0f);
  delayInSamples = static_cast<int>(sampleRate * 0.02);
  delayBufferWritePos = 0;
}

void CombFilter::process(float* sample) {
  int delayBufferLength = (int)delayBuffer.size();
  int delayReadPos = (delayBufferWritePos - delayInSamples + delayBufferLength) % delayBufferLength;
  float delayedSample = delayBuffer[delayReadPos];
  float out = *sample + gain * delayedSample;
  delayBuffer[delayBufferWritePos] = *sample;
  *sample = out;
  delayBufferWritePos = (delayBufferWritePos + 1) % delayBufferLength;
}
