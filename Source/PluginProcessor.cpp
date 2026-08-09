#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OneBassBandAudioProcessor::OneBassBandAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         ),
#endif
      apvts(*this, nullptr, "PARAMETERS", Parameters::createParameterLayout())
{
  Parameters::addListenerToAllParameters(apvts, this);
}

OneBassBandAudioProcessor::~OneBassBandAudioProcessor()
{
}

//==============================================================================
const juce::String OneBassBandAudioProcessor::getName() const
{
  return JucePlugin_Name;
}

bool OneBassBandAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool OneBassBandAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool OneBassBandAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double OneBassBandAudioProcessor::getTailLengthSeconds() const
{
  return 0.0;
}

int OneBassBandAudioProcessor::getNumPrograms()
{
  return 1;
}

int OneBassBandAudioProcessor::getCurrentProgram()
{
  return 0;
}

void OneBassBandAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String OneBassBandAudioProcessor::getProgramName(int index)
{
  return {};
}

void OneBassBandAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
}

//==============================================================================
void OneBassBandAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  octaver.prepareToPlay(sampleRate, samplesPerBlock);
  sampleRateManager.prepareToPlay(sampleRate, samplesPerBlock);
  distortion.prepareToPlay(TARGET_SAMPLE_RATE, samplesPerBlock);
}

void OneBassBandAudioProcessor::releaseResources()
{
}

void OneBassBandAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
  juce::ScopedNoDenormals noDenormals;
  juce::ignoreUnused(midiMessages);

  octaver.processBlock(buffer);
  sampleRateManager.processBlock(buffer, [this](juce::dsp::AudioBlock<float> &block) {
    distortion.processBlock(block);
  });
}

void OneBassBandAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{ 
  if (parameterID == Parameters::pitchShiftedOctave)
    octaver.setOctave(static_cast<int>(newValue));

  if (parameterID == Parameters::distortionAmount)
    distortion.setDistortionAmount(newValue);
  
}

//==============================================================================
bool OneBassBandAudioProcessor::hasEditor() const
{
  return false;
}

juce::AudioProcessorEditor *OneBassBandAudioProcessor::createEditor()
{
  return new OneBassBandAudioProcessorEditor(*this);
}

//==============================================================================
void OneBassBandAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
}

void OneBassBandAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
  // You should use this method to restore your parameters from this memory block,
  // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
  return new OneBassBandAudioProcessor();
}
