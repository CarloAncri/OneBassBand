#pragma once

#include <JuceHeader.h>


/*
 * @class SampleRateIncapsulator
  * @brief This class is a wrapper for the JUCE oversampling class.
  * 
  * Given a target sample rate, it will create a "block" where the processing will be done at the target sample rate, and then downsampled to the original sample rate.
  * This operation is useful for non-linear processing, such as distortion.
 */
class SampleRateIncapsulator
{
public:
  SampleRateIncapsulator();
  ~SampleRateIncapsulator() = default;

  float prepareToPlay(double sampleRate, int targetSampleRate, int samplesPerBlock, int numChannels);
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

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleRateIncapsulator);
};