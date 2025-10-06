#include "PluginEditor.h"
#include "../PluginProcessor.h"

//==============================================================================
SchroederReverbAudioProcessorEditor::SchroederReverbAudioProcessorEditor(
    SchroederReverbAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    mixParam = processorRef.dryWetMix;
    mixSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    mixSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible(mixSlider);

    mixSlider.setValue(mixParam->get());
    mixSlider.onValueChange = [this]()
    {
        if (mixParam != nullptr)
        {
            *mixParam = (float)mixSlider.getValue();
        }
    };

    setSize(400, 300);
}

SchroederReverbAudioProcessorEditor::~SchroederReverbAudioProcessorEditor() {}

//==============================================================================
void
SchroederReverbAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void
SchroederReverbAudioProcessorEditor::resized()
{
  mixSlider.setBounds(40, 80, getWidth() - 80, 20);
}
