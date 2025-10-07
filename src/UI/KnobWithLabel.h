#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class KnobWithLabel : public juce::Component
{
  public:
  KnobWithLabel(const juce::String& text, juce::AudioParameterFloat* param);
    ~KnobWithLabel();

    void resized() override;

  private:
    juce::Slider knob;
    juce::Label label;
    juce::AudioParameterFloat* param = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobWithLabel);
};
