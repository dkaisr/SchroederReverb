#include "AllPassFilter.h"

void AllPassFilter::prepare(double sampleRate, int samplesPerBlock) {
  int maxDelayTimeMs = 100;
  int maxDelaySamples = static_cast<int>(sampleRate * maxDelayTimeMs / 1000.0);

  delayBuffer.resize(maxDelaySamples, 0.0f);
  delayInSamples = static_cast<int>(sampleRate * 0.02);
  delayBufferWritePos = 0;
}

void AllPassFilter::process(float* sample) {
  int delayBufferLength = (int)delayBuffer.size();
  int delayReadPos =
      (delayBufferWritePos - delayInSamples + delayBufferLength) %
      delayBufferLength;
  float xn = *sample;
  float delayedSample = delayBuffer[delayReadPos];
  float yn = -gain * xn + delayedSample;  

  delayBuffer[delayBufferWritePos] = xn + gain * yn;
  *sample = yn;
  delayBufferWritePos = (delayBufferWritePos + 1) % delayBufferLength;
}
