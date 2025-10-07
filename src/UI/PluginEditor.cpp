#include "PluginEditor.h"
#include "../PluginProcessor.h"

//==============================================================================
SchroederReverbAudioProcessorEditor::SchroederReverbAudioProcessorEditor(
    SchroederReverbAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p), preDelayKnob("Pre-Delay", p.preDelay),
      decayKnob("Decay", p.decayFactor), mixKnob("Dry/Wet", p.dryWetMix)
{
    addAndMakeVisible(preDelayKnob);
    addAndMakeVisible(decayKnob);
    addAndMakeVisible(mixKnob);

    setSize(380, 140);
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
    preDelayKnob.setBounds(20, 20, 100, 100);
    decayKnob.setBounds(140, 20, 100, 100);
    mixKnob.setBounds(260, 20, 100, 100);
}
