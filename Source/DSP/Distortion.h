#pragma once

#include <JuceHeader.h>

#include "../PluginParameters.h"


/**
 * @class Distortion
 * @brief This class handles distortion functionality.
 * 
 * The distortion is applied to the audio signal through a waveshaping function, which is controlled by the distortion amount parameter.
 * This class do not operates on a juce::AudioBuffer<float> directly, but on a juce::dsp::AudioBlock<float>, for architectural reasons (see SampleRate-Incapsulator).
 */
class Distortion
{
public:
  Distortion(float distAmount = Parameters::defaultDistortionAmount);
  ~Distortion() = default;

  void prepareToPlay(double sampleRate, int samplesPerBlock);

  void setDistortionAmount(float newAmount);

  void processBlock(juce::dsp::AudioBlock<float> &buffer);
private:
  float amount = 0.0f;
  float thr = 1.0f;
  float drive = 1.0f;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Distortion);
};