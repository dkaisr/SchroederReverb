#include "SchroederReverb.h"

void
SchroederReverb::prepare(double sampleRate, int samplesPerBlock)
{
    combFilter0.prepare(sampleRate, samplesPerBlock, 1557, 0.742f);
    combFilter1.prepare(sampleRate, samplesPerBlock, 1613, 0.733f);
    combFilter2.prepare(sampleRate, samplesPerBlock, 1499, 0.715f);
    combFilter3.prepare(sampleRate, samplesPerBlock, 1427, 0.697f);
    allPassFilter0.prepare(sampleRate, samplesPerBlock, 347, 0.7f);
    allPassFilter1.prepare(sampleRate, samplesPerBlock, 1137, 0.7f);
}

void
SchroederReverb::process(float& sample, float dryWetMix)
{
    juce::ScopedNoDenormals noDenormals;

    float in0 = sample;
    float in1 = sample;
    float in2 = sample;
    float in3 = sample;

    combFilter0.process(in0);
    combFilter1.process(in1);
    combFilter2.process(in2);
    combFilter3.process(in3);

    float allPassIn = 0.25f * (in0 + in1 + in2 + in3);
    allPassFilter0.process(allPassIn);
    allPassFilter1.process(allPassIn);

    sample = dryWetMix * allPassIn + (1.0f - dryWetMix) * sample;
}
