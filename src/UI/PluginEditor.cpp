#include "../PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SchroederReverbAudioProcessorEditor::SchroederReverbAudioProcessorEditor (SchroederReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    gainParam = processorRef.gain;

    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    gainSlider.setRange(0.0, 5.0, 0.01);

    addAndMakeVisible(gainSlider);
    gainSlider.setValue(gainParam->get());

    gainSlider.onValueChange = [this]() {
      if (gainParam != nullptr) {
	*gainParam = (float)gainSlider.getValue();
        }
    };
    
    setSize (400, 300);
}

SchroederReverbAudioProcessorEditor::~SchroederReverbAudioProcessorEditor()
{
}

//==============================================================================
void SchroederReverbAudioProcessorEditor::paint (juce::Graphics& g)
{}

void SchroederReverbAudioProcessorEditor::resized()
{
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  gainSlider.setBounds(40, 80, getWidth() - 80, 20);
}
