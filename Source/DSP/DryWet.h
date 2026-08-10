#pragma once

#include <JuceHeader.h>

#include "../PluginParameters.h"

class DryWet
{
public:
  // =================================================================
  DryWet(float defaultDW = Parameters::defaultDryWetAmount);
  ~DryWet();
  // =================================================================
  void prepareToPlay(double sampleRate, int maxBlockSize);
  void releaseResources();
  // =================================================================
  void copyDrySignal(juce::AudioBuffer<float> &sourceBuffer);
  void mixDrySignal(juce::AudioBuffer<float> &destinationBuffer);
  void setDWRatio(float newValue);
  void setDelaySamples(float newDelaySamples);
  // =================================================================
private:
  void updateState();

  juce::AudioBuffer<float> drySignal;
  juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine {4096};

  float dwRatio = 0.5f;

  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> dryLevel;
  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> wetLevel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DryWet)
};
