#include "DryWet.h"

DryWet::DryWet(float defaultDW) { dwRatio = defaultDW; }
DryWet::~DryWet() {}


void DryWet::prepareToPlay(double sampleRate, int maxBlockSize)
{
  drySignal.setSize(2, maxBlockSize);
  drySignal.clear();

  dryLevel.reset(sampleRate, 0.01);
  wetLevel.reset(sampleRate, 0.01);

  // delay line (compensate for anti-aliasing filters)
  juce::dsp::ProcessSpec info;
  info.sampleRate = sampleRate;
  info.maximumBlockSize = static_cast<uint32_t>(maxBlockSize);
  info.numChannels = 2;
  delayLine.prepare(info);
  delayLine.reset();

  updateState();
}


void DryWet::releaseResources() { drySignal.setSize(0, 0); }


void DryWet::copyDrySignal(juce::AudioBuffer<float> &sourceBuffer)
{
  auto numCh = sourceBuffer.getNumChannels();
  auto numSamples = sourceBuffer.getNumSamples();

  for (int ch = 0; ch < numCh; ++ch)
    drySignal.copyFrom(ch, 0, sourceBuffer, ch, 0, numSamples);

  juce::dsp::AudioBlock<float> block(drySignal);
  juce::dsp::ProcessContextReplacing<float> context(block);
  delayLine.process(context);
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


void DryWet::setDelaySamples(float newDelaySamples)
{
  delayLine.setDelay(newDelaySamples);
}


void DryWet::updateState()
{
  dryLevel.setTargetValue(std::sqrt(1.0f - dwRatio));
  wetLevel.setTargetValue(std::sqrt(dwRatio));
}