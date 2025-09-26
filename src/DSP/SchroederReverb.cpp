#include "SchroederReverb.h"

void SchroederReverb::prepare(double sampleRate, int samplesPerBlock) {
  combFilter0.prepare(sampleRate, samplesPerBlock);
  combFilter1.prepare(sampleRate, samplesPerBlock);
  combFilter2.prepare(sampleRate, samplesPerBlock);
  combFilter3.prepare(sampleRate, samplesPerBlock);
  allPassFilter0.prepare(sampleRate, samplesPerBlock);
  allPassFilter1.prepare(sampleRate, samplesPerBlock);    
}

void SchroederReverb::process(float *sample) {
  float in0 = *sample;
  float in1 = *sample;
  float in2 = *sample;
  float in3 = *sample;

  combFilter0.process(&in0);
  combFilter1.process(&in1);
  combFilter2.process(&in2);
  combFilter3.process(&in3);

  float allPassIn = in0 + in1 + in2 + in3;
  allPassFilter0.process(&allPassIn);
  allPassFilter1.process(&allPassIn);
  *sample = allPassIn;
}
