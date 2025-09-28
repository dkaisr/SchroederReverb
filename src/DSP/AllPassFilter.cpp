#include "AllPassFilter.h"

void AllPassFilter::prepare(double sampleRate, int samplesPerBlock, int delayInSamples, float gain) {
  int maxDelayTimeMs = 100;
  int maxDelaySamples = static_cast<int>(sampleRate * maxDelayTimeMs / 1000.0);

  delayBuffer.resize(maxDelaySamples, 0.0f);
  //delayInSamples = static_cast<int>(sampleRate * delayInSeconds);
  delayBufferWritePos = 0;
  this->delayInSamples_ = delayInSamples;
  this->gain = gain;
}

void AllPassFilter::process(float* sample) {
  int delayBufferLength = (int)delayBuffer.size();
  int delayReadPos =
      (delayBufferWritePos - delayInSamples_ + delayBufferLength) %
      delayBufferLength;


  float delayedSample = delayBuffer[delayReadPos];
  float xn = *sample;

  float bufferInput = xn + gain * delayedSample;
  float yn = -gain * xn + delayedSample;  

  delayBuffer[delayBufferWritePos] = bufferInput;
  *sample = yn;
  delayBufferWritePos = (delayBufferWritePos + 1) % delayBufferLength;
}
