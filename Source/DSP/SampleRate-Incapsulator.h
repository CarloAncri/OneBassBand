#pragma once

#include <JuceHeader.h>


class SampleRateIncapsulator
{
public:
  SampleRateIncapsulator(int numChannels);
  ~SampleRateIncapsulator() = default;

  float prepareToPlay(double sampleRate, int targetSampleRate, int samplesPerBlock);
  void reset();
  float getLatencyInSamples() const;

  // incapsulates the dsp processing (dspFunc) in a oversampled block.
  template <typename ProcessCallback>
  void processBlock(juce::AudioBuffer<float> &buffer, ProcessCallback &&dspFunc)
  {
    if (exponent == 0 || oversampler == nullptr)
    {
      juce::dsp::AudioBlock<float> audioBlock(buffer);
      dspFunc(audioBlock);
      return;
    }

    juce::dsp::AudioBlock<float> audioBlock(buffer);
    juce::dsp::AudioBlock<float> upsampledBlock = oversampler->processSamplesUp(audioBlock);

    dspFunc(upsampledBlock);

    oversampler->processSamplesDown(audioBlock);
  }
private:
  std::unique_ptr<juce::dsp::Oversampling<float>> oversampler;
  int numChannels;
  int exponent;
};