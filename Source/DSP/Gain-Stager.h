#pragma once

#include <JuceHeader.h>

#include "../PluginParameters.h"


/**
 * @class GainStager
 * @brief This class handles gain staging functionality.
 * 
 * It regulates the gain applied to the audio signal through a smoothed value.
 */
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

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainStager);
};