#pragma once

#include <JuceHeader.h>

#include "../PluginParameters.h"

class GainStager
{
public:
  GainStager(float initGain = Parameters::defaultInputGain);
  ~GainStager() = default;

  void prepareToPlay(double sampleRate);
  void processBlock(juce::AudioBuffer<float> &buffer);

  void setGainDb(float newGain);
private:
  juce::SmoothedValue<float> smoothedGain;
};