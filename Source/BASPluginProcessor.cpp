/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "BASPluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BASAudioProcessor::BASAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (
        BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
            .withInput ("Input", juce::AudioChannelSet::stereo(), true)
#endif
            .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
            ),
      tree (*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    keyboardState.addListener (this);

    numVoices = 4;
    initialiseSynth();
}

BASAudioProcessor::~BASAudioProcessor() = default;

void BASAudioProcessor::initialiseSynth()
{
    synthesiser.clearVoices();
    synthesiser.clearSounds();
    for (int i = numVoices; --i >= 0;)
    {
        synthesiser.addVoice (new WavetableSynthesiserVoice());
    }

    synthesiser.addSound (new WavetableSynthesiserSound());
}
juce::AudioProcessorValueTreeState::ParameterLayout
    BASAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.reserve ((3 * 33) + 4); // Reserve space for 33 sets of parameters

    constexpr static auto createParamIdWithIndex = [] (auto name, auto index)
    {
        return juce::ParameterID { std::string { name } + std::to_string (index),
                                   versionHint };
    };

    constexpr static auto createParameterNameWithIndex = [] (auto name,
                                                             auto index)
    {
        return concatenateStringAndInt (name, index);
    };

    for (int i = 0; i < 33; i++)
    {
        const auto gainId = createParamIdWithIndex (baseGainId, i);
        const auto gainName = createParameterNameWithIndex (baseGainName, i);

        const auto freqId = createParamIdWithIndex (baseFreqId, i);
        const auto freqName = createParameterNameWithIndex (baseFreqName, i);

        const auto wavetypeId = createParamIdWithIndex (baseWaveTypeId, i);
        const auto wavetypeName = createParameterNameWithIndex (baseWaveTypeName, i);

        auto gainParameter = std::make_unique<juce::AudioParameterFloat> (
            gainId, gainName, juce::NormalisableRange<float> (-64.0f, -12.0f, 1.0), -64.0f);

        auto freqParameter = std::make_unique<juce::AudioParameterFloat> (
            freqId, freqName, juce::NormalisableRange<float> (-24.0f, +24.0f, 0.0), 1.0f);

        auto waveTypeParameter = std::make_unique<juce::AudioParameterBool> (
            wavetypeId, wavetypeName, false);

        params.push_back (std::move (waveTypeParameter));
        params.push_back (std::move (gainParameter));
        params.push_back (std::move (freqParameter));
    }

    const auto masterGainParamId = juce::ParameterID { "gainIdM", versionHint };
    auto MasterGainParameter = std::make_unique<juce::AudioParameterFloat> (
        masterGainParamId, GainNameM, juce::NormalisableRange<float> (-60.0f, 6.0f, 1.0), -64.0f);
    // Component Volume Button1 - 3
    const auto cvb1ParamId = juce::ParameterID { cvb1Id, versionHint };
    auto CVB1 =
        std::make_unique<juce::AudioParameterBool> (cvb1ParamId, CVB1Name, false);
    const auto cvb2ParamId = juce::ParameterID { cvb2Id, versionHint };
    auto CVB2 =
        std::make_unique<juce::AudioParameterBool> (cvb2ParamId, CVB2Name, false);
    const auto cvb3ParamId = juce::ParameterID { cvb3Id, versionHint };
    auto CVB3 =
        std::make_unique<juce::AudioParameterBool> (cvb3ParamId, CVB3Name, false);

    params.push_back (std::move (CVB1));
    params.push_back (std::move (CVB2));
    params.push_back (std::move (CVB3));
    params.push_back (std::move (MasterGainParameter));

    return { params.begin(), params.end() };
}

void BASAudioProcessor::handleIncomingMidiMessage (
    juce::MidiInput*,
    const juce::MidiMessage& message)
{
    const juce::ScopedValueSetter<bool> scopedInputFlag (isAddingFromMidiInput,
                                                         true);
    keyboardState.processNextMidiEvent (message);
}

void BASAudioProcessor::handleNoteOn (juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    synthesiser.noteOn (midiChannel, midiNoteNumber, velocity);
}

void BASAudioProcessor::handleNoteOff (juce::MidiKeyboardState*,
                                       int midiChannel,
                                       int midiNoteNumber,
                                       float velocity)
{
    synthesiser.noteOff (midiChannel, midiNoteNumber, velocity, true);
}

void BASAudioProcessor::handlePitchWheel (juce::MidiKeyboardState*,
                                          int midiChannel,
                                          int wheelValue)
{
    synthesiser.handlePitchWheel (midiChannel, wheelValue);
}
//==============================================================================
const juce::String BASAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BASAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool BASAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool BASAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double BASAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int BASAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0
        // programs, so this should be at least 1, even if you're not really
        // implementing programs.
}

int BASAudioProcessor::getCurrentProgram() { return 0; }

void BASAudioProcessor::setCurrentProgram (int) {}

const juce::String BASAudioProcessor::getProgramName (int) { return {}; }

void BASAudioProcessor::changeProgramName (int, const juce::String&) {}

//==============================================================================
void BASAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused (samplesPerBlock);
    auto lastSampleRate = sampleRate;
    double currentGain =
        juce::Decibels::decibelsToGain (*tree.getRawParameterValue (gainIdM) + 0.0);
    smooth.reset (sampleRate, 0.1);
    smooth.setTargetValue (static_cast<float> (currentGain));
    smooth.getNextValue();
    synthesiser.setCurrentPlaybackSampleRate (lastSampleRate);
}

void BASAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BASAudioProcessor::isBusesLayoutSupported (
    const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void BASAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                      juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    midiMessages.clear();

    for (int i = 0; i < synthesiser.getNumVoices(); i++)
    {
        if ((voice = dynamic_cast<WavetableSynthesiserVoice*> (
                 synthesiser.getVoice (i))))
        {
            double currentGainMaster = juce::Decibels::decibelsToGain (
                *tree.getRawParameterValue (gainIdM) + 0.0);
            voice->setMasterGain (static_cast<float> (currentGainMaster));
            int frequency[33];
            float currentGain[33];
            float button[33];
            for (unsigned int n = 0; n < 33; ++n)
            {
                currentGain[n] = juce::Decibels::decibelsToGain (
                    *tree.getRawParameterValue (
                        "gainId" + std::to_string (static_cast<std::size_t> (n)))
                    + 0.0);
                voice->setGain (n, currentGain[n]);
                frequency[n] = static_cast<int> (*tree.getRawParameterValue (
                    "freqId" + std::to_string (static_cast<std::size_t> (n))));
                button[n] = static_cast<int> (*tree.getRawParameterValue (
                    "waveTypeId" + std::to_string (static_cast<std::size_t> (n))));
                voice->setFrequency (n, frequency[n]);
            }
        }
    }
    // Render the next block of audio using the synthesizer
    synthesiser.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

void BASAudioProcessor::getNextAudioBlock (
    const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    juce::MidiBuffer incomingMidi;
    midiCollector.removeNextBlockOfMessages (incomingMidi,
                                             bufferToFill.numSamples);
    keyboardState.processNextMidiBuffer (incomingMidi, 0, bufferToFill.numSamples, true);

    // synthesiser.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0,
    // bufferToFill.numSamples);
}

juce::MidiMessageCollector* BASAudioProcessor::getMidiCollector()
{
    return &midiCollector;
}

//==============================================================================
bool BASAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BASAudioProcessor::createEditor()
{
    return new BASAudioProcessorEditor (*this);
}

//==============================================================================
void BASAudioProcessor::getStateInformation (juce::MemoryBlock& /*destData*/)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BASAudioProcessor::setStateInformation (const void* /*data*/,
                                             int /*sizeInBytes*/)
{
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BASAudioProcessor();
}
