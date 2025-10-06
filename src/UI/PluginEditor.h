#pragma once

#include "../PluginProcessor.h"

//==============================================================================
class SchroederReverbAudioProcessorEditor final : public juce::AudioProcessorEditor
{
  public:
    explicit SchroederReverbAudioProcessorEditor(SchroederReverbAudioProcessor&);
    ~SchroederReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

  private:
    SchroederReverbAudioProcessor& processorRef;
    juce::Slider mixSlider;
    juce::AudioParameterFloat* mixParam = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SchroederReverbAudioProcessorEditor)
};
