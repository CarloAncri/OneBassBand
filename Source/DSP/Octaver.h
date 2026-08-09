#pragma once

#include <JuceHeader.h>
#include <atomic>

class Octaver
{
public:
  Octaver() = default;
  ~Octaver() = default;

  void prepareToPlay(double sampleRate, int samplesPerBlock);
  void processBlock(juce::AudioBuffer<float> &buffer);

  void setOctave(int newOctave);
private:
  void updateParameters();

  float getLinearSample(int channel, float readPos, int bufferLength);

  juce::AudioBuffer<float> delayBuffer;
  int writePosition = 0;

  float currentPhase = 0.0f;
  float phaseIncrement = 0.0f;

  double mSampleRate = 44100.0;
  int currentOctave = 0;
  std::atomic<int> targetOctave{0};

  float amplitudeSamples = 0.0f;
  bool isPitchUp = false;

  const float modFrequency = 15.0f;
};