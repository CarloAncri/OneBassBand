#pragma once

#include <JuceHeader.h>
#include <atomic>

#include "../PluginParameters.h"


/**
 * @class Octaver
 * @brief This class handles octave shifting functionality.
 *
 * The signal can be pitched up or down in this octaves: [-2, -1, 0, 1, 2].
 * The pitch shifting is done by a delay line and two modulated read positions.
 */
class Octaver
{
public:
  Octaver(int currentOctave = Parameters::defaultPitchShiftedOctave);
  ~Octaver() = default;

  void prepareToPlay(double sampleRate, int numChannels);
  void releaseResources();
  void processBlock(juce::AudioBuffer<float> &buffer);

  void setOctave(int newOctave);
private:
  void updateParameters();

  float getLinearSample(int channel, float readPos, int bufferLength);

  juce::AudioBuffer<float> delayBuffer;
  int writePosition = 0;
  int numChannels = 0;

  float currentPhase = 0.0f;
  float phaseIncrement = 0.0f;

  double mSampleRate = 44100.0;
  int currentOctave = 0;
  std::atomic<int> targetOctave{0};

  float amplitudeSamples = 0.0f;
  bool isPitchUp = false;

  const float modFrequency = 15.0f;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Octaver);
};