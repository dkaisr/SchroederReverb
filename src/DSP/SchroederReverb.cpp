#include "SchroederReverb.h"

void
SchroederReverb::prepare(double sampleRate, int samplesPerBlock)
{
    preDelay.prepare(sampleRate, samplesPerBlock);
    combFilter0.prepare(sampleRate, samplesPerBlock, 1557);
    combFilter1.prepare(sampleRate, samplesPerBlock, 1613);
    combFilter2.prepare(sampleRate, samplesPerBlock, 1499);
    combFilter3.prepare(sampleRate, samplesPerBlock, 1427);
    allPassFilter0.prepare(sampleRate, samplesPerBlock, 347, 0.7f);
    allPassFilter1.prepare(sampleRate, samplesPerBlock, 1137, 0.7f);
}

void
SchroederReverb::process(float& sample, float dryWetMix, float decayFactor)
{
    juce::ScopedNoDenormals noDenormals;

    float in = sample;


    float cf0in = in;
    float cf1in = in;
    float cf2in = in;
    float cf3in = in;

    combFilter0.process(cf0in, decayFactor);
    combFilter1.process(cf1in, decayFactor);
    combFilter2.process(cf2in, decayFactor);
    combFilter3.process(cf3in, decayFactor);

    float allPassIn = 0.25f * (cf0in + cf1in + cf2in + cf3in);
    allPassFilter0.process(allPassIn);
    allPassFilter1.process(allPassIn);

    sample = dryWetMix * allPassIn + (1.0f - dryWetMix) * sample;
}
