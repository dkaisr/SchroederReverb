#pragma once

#include "../PluginProcessor.h"

//==============================================================================
class SchroederReverbAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit SchroederReverbAudioProcessorEditor (SchroederReverbAudioProcessor&);
    ~SchroederReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SchroederReverbAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SchroederReverbAudioProcessorEditor)
};
