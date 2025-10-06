#include "PluginProcessor.h"
#include "UI/PluginEditor.h"

//==============================================================================
SchroederReverbAudioProcessor::SchroederReverbAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    addParameter(dryWetMix = new juce::AudioParameterFloat("mix", "Mix", 0.0f, 1.0f, 0.5f));
    addParameter(decayFactor = new juce::AudioParameterFloat("decay", "Decay", 0.1f, 10.0f, 1.0f));
    addParameter(preDelay
                 = new juce::AudioParameterFloat("predelay", "Pre-Delay", 0.0f, 0.2f, 0.0f));
}

SchroederReverbAudioProcessor::~SchroederReverbAudioProcessor() {}

//==============================================================================
const juce::String
SchroederReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool
SchroederReverbAudioProcessor::acceptsMidi() const
{
    return false;
}

bool
SchroederReverbAudioProcessor::producesMidi() const
{
    return false;
}

bool
SchroederReverbAudioProcessor::isMidiEffect() const
{
    return false;
}

double
SchroederReverbAudioProcessor::getTailLengthSeconds() const
{
    return 10.0;
}

int
SchroederReverbAudioProcessor::getNumPrograms()
{
    return 1;
}

int
SchroederReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void
SchroederReverbAudioProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String
SchroederReverbAudioProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void
SchroederReverbAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void
SchroederReverbAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    schroederReverb.prepare(sampleRate, samplesPerBlock);
}

void
SchroederReverbAudioProcessor::releaseResources()
{
}

// The plugin only supports layouts with the same number of input and output channels
bool
SchroederReverbAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == layouts.getMainInputChannelSet();
}

void
SchroederReverbAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                            juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    juce::ScopedNoDenormals noDenormals;

    int totalNumInputChannels = getTotalNumInputChannels();
    int totalNumOutputChannels = getTotalNumOutputChannels();

    float currentPreDelay = preDelay->get();
    if (currentPreDelay != lastPreDelay)
    {
      schroederReverb.setPreDelayMs(currentPreDelay * 1000.0f);
        lastPreDelay = currentPreDelay;
    }

    // Clear extra channels
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            // Apply effect to sample
            schroederReverb.process(channelData[i], dryWetMix->get(), decayFactor->get());
        }
    }
}

//==============================================================================
bool
SchroederReverbAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor*
SchroederReverbAudioProcessor::createEditor()
{
    return new SchroederReverbAudioProcessorEditor(*this);
}

//==============================================================================
void
SchroederReverbAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::ignoreUnused(destData);
}

void
SchroederReverbAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE
createPluginFilter()
{
    return new SchroederReverbAudioProcessor();
}
