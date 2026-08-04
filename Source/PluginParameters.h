#pragma once
#include <JuceHeader.h>

namespace Parameters
{
  static const String inputGain = "inG";
  static const String outputGain = "ouG";
  static const String cutoffFreq = "coF";
  static const String compressorThr = "cmT";
  static const String pitchShiftedOctave = "psO";
  static const String distortionAmount = "dsA";
  static const String dryWetAmount = "dwA";

  static const float defaultInputGain = 1.0f;
  static const float defaultOutputGain = 1.0f;
  static const float defaultCutoffFreq = 200.0f;
  static const float defaultCompressorThr = 1.0f;
  static const int defaultPitchShiftedOctave = 0;
  static const float defaultDistortionAmount = 0.5f;
  static const float defaultDryWetAmount = 1.0f;


  
  static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
  {
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>(inputGain, "Input Gain", NormalisableRange<float>(0.0f, 2.0f, 0.001f, 0.5f), defaultInputGain));
    params.push_back(std::make_unique<AudioParameterFloat>(outputGain, "Output Gain", NormalisableRange<float>(0.0f, 2.0f, 0.001f, 0.5f), defaultOutputGain));
    params.push_back(std::make_unique<AudioParameterFloat>(cutoffFreq, "Cutoff Frequency", NormalisableRange<float>(20.0f, 20000.0f, 0.001f, 0.25f), defaultCutoffFreq));
    params.push_back(std::make_unique<AudioParameterFloat>(compressorThr, "Compressor Threshold", NormalisableRange<float>(-60.0f, 0.0f, 0.01f, 1.0f), defaultCompressorThr));
    params.push_back(std::make_unique<AudioParameterInt>(pitchShiftedOctave, "Pitch Shifted Octave", -2, 2, defaultPitchShiftedOctave));
    params.push_back(std::make_unique<AudioParameterFloat>(distortionAmount, "Distortion Amount", NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f), defaultDistortionAmount));
    params.push_back(std::make_unique<AudioParameterFloat>(dryWetAmount, "Dry Wet Amount", NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f), defaultDryWetAmount));

    return {params.begin(), params.end()};
  }



  static void addListenerToAllParameters(AudioProcessorValueTreeState &valueTreeState, AudioProcessorValueTreeState::Listener *listener)
  {
    std::unique_ptr<XmlElement> xml(valueTreeState.copyState().createXml());

    for (auto element : xml->getChildWithTagNameIterator("PARAM"))
    {
      const String &id = element->getStringAttribute("id");
      valueTreeState.addParameterListener(id, listener);
    }
  }
}