#include "KnobWithLabel.h"

KnobWithLabel::KnobWithLabel(const juce::String& text, juce::AudioParameterFloat* param)
    : param(param)
{
    addAndMakeVisible(label);
    label.setText(text, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(juce::Font(juce::FontOptions().withHeight(10.0f)));
    addAndMakeVisible(knob);
    knob.setSliderStyle(juce::Slider::Rotary);
    knob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    knob.setValue(param->get());

    auto range = param->getNormalisableRange();
    knob.setRange(range.start, range.end, range.interval);

    knob.onValueChange = [this]()
    {
        if (this->param != nullptr)
        {
	  *this->param = (float) knob.getValue();
	}
    };
}

KnobWithLabel::~KnobWithLabel() {}

void
KnobWithLabel::resized()
{
    knob.setBounds(0, 0, getWidth(), getHeight());
    label.setBounds(0, -10, getWidth(), getHeight());
}
