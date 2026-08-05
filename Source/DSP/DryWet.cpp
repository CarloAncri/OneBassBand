#include "DryWet.h"

DryWet::DryWet(double defaultDW) { dwRatio = defaultDW; }
DryWet::~DryWet() {}


void DryWet::prepareToPlay(double sampleRate, int maxBlockSize)
{
  drySignal.setSize(2, maxBlockSize);
  drySignal.clear();

  dryLevel.reset(sampleRate, 0.01);
  wetLevel.reset(sampleRate, 0.01);

  updateState();
}


void DryWet::releaseResources() { drySignal.setSize(0, 0); }


void DryWet::copyDrySignal(juce::AudioBuffer<float> &sourceBuffer)
{
  auto numCh = sourceBuffer.getNumChannels();
  auto numSamples = sourceBuffer.getNumSamples();

  for (int ch = 0; ch < numCh; ++ch)
    drySignal.copyFrom(ch, 0, sourceBuffer, ch, 0, numSamples);
}


void DryWet::mixDrySignal(juce::AudioBuffer<float> &destinationBuffer)
{
  auto numCh = destinationBuffer.getNumChannels();
  auto numSamples = destinationBuffer.getNumSamples();

  dryLevel.applyGain(drySignal, numSamples);
  wetLevel.applyGain(destinationBuffer, numSamples);

  for (int ch = 0; ch < numCh; ++ch)
    destinationBuffer.addFrom(ch, 0, drySignal, ch, 0, numSamples);
}


void DryWet::setDWRatio(float newValue)
{
  dwRatio = newValue;
  updateState();
}


void DryWet::updateState()
{
  dryLevel.setTargetValue(std::sqrt(1.0f - dwRatio));
  wetLevel.setTargetValue(std::sqrt(dwRatio));
}