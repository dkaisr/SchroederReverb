#include "SchroederReverb.h"

void SchroederReverb::prepare(double sampleRate, int samplesPerBlock) {
  combFilter0.prepare(sampleRate, samplesPerBlock, 4799, 0.742f);
  combFilter1.prepare(sampleRate, samplesPerBlock, 4999, 0.733f);
  combFilter2.prepare(sampleRate, samplesPerBlock, 5399, 0.715f);
  combFilter3.prepare(sampleRate, samplesPerBlock, 5801, 0.697f);
  allPassFilter0.prepare(sampleRate, samplesPerBlock, 1051, 0.7f);
  allPassFilter1.prepare(sampleRate, samplesPerBlock, 337, 0.7f);    
}

void SchroederReverb::process(float *sample) {
  juce::ScopedNoDenormals noDenormals;
  
  float in0 = *sample;
  float in1 = *sample;
  float in2 = *sample;
  float in3 = *sample;

  combFilter0.process(&in0);
  combFilter1.process(&in1);
  combFilter2.process(&in2);
  combFilter3.process(&in3);

  float allPassIn = 0.25f * (in0 + in1 + in2 + in3);
  allPassFilter0.process(&allPassIn);
  allPassFilter1.process(&allPassIn);

  *sample = allPassIn;
}
