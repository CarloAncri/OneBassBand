#pragma once

#include <JuceHeader.h>

#include "../PluginParameters.h"


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
};