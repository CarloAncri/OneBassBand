#include "SampleRate-Incapsulator.h"


SampleRateIncapsulator::SampleRateIncapsulator(int channels) : numChannels(channels), exponent(0) {}


void SampleRateIncapsulator::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  double ratio = TARGET_SAMPLE_RATE / sampleRate;
  exponent = std::max(0, static_cast<int>(std::round(std::log2(ratio)))); // 2^exponent = oversample quantity.

  if (exponent > 0)
  {
    oversampler = std::make_unique<juce::dsp::Oversampling<float>>(
      numChannels, 
      exponent, 
      juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR,
      true,
      false);

    oversampler->initProcessing(static_cast<size_t>(samplesPerBlock));
    oversampler->reset();
  } else
    oversampler.reset();
}


void SampleRateIncapsulator::reset()
{
  if (oversampler != nullptr)
    oversampler->reset();
}


float SampleRateIncapsulator::getLatencyInSamples() const
{
  return oversampler != nullptr ? oversampler->getLatencyInSamples() : 0.0f;
}