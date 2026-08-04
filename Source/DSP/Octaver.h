#pragma once

#include <JuceHeader.h>

class Octaver
{
public:
  Octaver() = default;
  ~Octaver() = default;

  void prepareToPlay(double sampleRate, int samplesPerBlock) {}
  void processBlock(juce::AudioBuffer<float>& buffer) {}

private:

};