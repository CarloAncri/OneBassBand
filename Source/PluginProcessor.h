#pragma once

#include <JuceHeader.h>

#include "PluginParameters.h"
#include "DSP/Octaver.h"
#include "DSP/SampleRate-Incapsulator.h"
#include "DSP/Distortion.h"

# define TARGET_SAMPLE_RATE 96000.0f

class OneBassBandAudioProcessor : public juce::AudioProcessor, private juce::AudioProcessorValueTreeState::Listener
{
public:
  //==============================================================================
  OneBassBandAudioProcessor();
  ~OneBassBandAudioProcessor() override;

  //==============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  void parameterChanged(const juce::String &parameterID, float newValue) override;

  //==============================================================================
  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

private:
  juce::AudioProcessorValueTreeState apvts;

  Octaver octaver;
  SampleRateIncapsulator sampleRateManager{2, TARGET_SAMPLE_RATE};
  Distortion distortion;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OneBassBandAudioProcessor)
};
