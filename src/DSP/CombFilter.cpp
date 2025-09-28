#include "CombFilter.h"

void CombFilter::prepare(double sampleRate, int samplesPerBlock, int delayInSamples, float gain) {
  int maxDelayTimeMs = 100;
  int maxDelaySamples = static_cast<int>(sampleRate * maxDelayTimeMs / 1000.0);

  delayBuffer.resize(maxDelaySamples, 0.0f);
  std::fill(delayBuffer.begin(), delayBuffer.end(), 0.0f);
  delayBufferWritePos = 0;
  this->delayInSamples_ = delayInSamples;
  this->gain = gain;
}

void CombFilter::process(float* sample) {
  int delayBufferLength = (int)delayBuffer.size();
  int delayReadPos = (delayBufferWritePos - delayInSamples_ + delayBufferLength) % delayBufferLength;
  float delayedSample = delayBuffer[delayReadPos];
  float yn = *sample + gain * delayedSample;
  delayBuffer[delayBufferWritePos] = yn;
  *sample = yn;
  delayBufferWritePos = (delayBufferWritePos + 1) % delayBufferLength;
}
