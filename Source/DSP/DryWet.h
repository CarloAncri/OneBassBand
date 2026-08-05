#pragma once

#include <JuceHeader.h>

class DryWet
{
public:
  // =================================================================
  DryWet(double defaultDW);
  ~DryWet();
  // =================================================================
  void prepareToPlay(double sampleRate, int maxBlockSize);
  void releaseResources();
  // =================================================================
  void copyDrySignal(juce::AudioBuffer<float> &sourceBuffer);
  void mixDrySignal(juce::AudioBuffer<float> &destinationBuffer);
  void setDWRatio(float newValue);
  // =================================================================
private:
  void updateState();

  juce::AudioBuffer<float> drySignal;

  float dwRatio = 0.5f;

  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> dryLevel;
  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> wetLevel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DryWet)
};
