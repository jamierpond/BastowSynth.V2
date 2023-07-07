#pragma once
#include "WaveGen.h"
#include "WaveSetup.h"
#include <JuceHeader.h>

class WavetableSynthesiserSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel (int /*midiChannel*/) override { return true; }
};

class WavetableSynthesiserVoice : public juce::SynthesiserVoice
{
public:
    WavetableSynthesiserVoice()
        : waveType_ (kNumOscillators_, 4)
    {
        // Initialize any necessary member variables
        CreateWaveTable();
        CreateOscillator();
    }

    void promptInitialWavetable()
    {
        for (unsigned int n = 0; n < kNumOscillators_; ++n)
        {
            gains_[n] = 1.0f / kNumOscillators_; // Initial gain value
        }
    }

    void setMasterGain (float masterVol)
    {
        masterGain_ = masterVol * level_;
    }

    void setGain (unsigned int index, float gain)
    {
        if (index < kNumOscillators_)
            gains_[index] = gain;
    }

    void setFrequency (unsigned int index, int frequency)
    {
        if (index < kNumOscillators_)
        {
            frequencyP_[index] = static_cast<int> (frequency) / 24;
        }
    }

    bool canPlaySound (juce::SynthesiserSound*) override { return true; }

    static float noteHz (int midiNoteNumber, double centsOffset)
    {
        double hertz = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        hertz *= std::pow (4.0, centsOffset / 4800);
        return (float) hertz;
    }

    void setWaveType (unsigned int index, int waveType)
    {
        // this is very confusing, is waveType changing size?
        if (4 < waveType_.size())
        {
            waveType_[index] = waveType;
            buttonPressed = true;
            std::cout << "The value of number is: " << waveType << std::endl;
            std::cout << "The vector of number is: " << waveType_[index] << std::endl;
        }
    }

    float pitchBendCents (int index)
    {
        if (frequencyP_[static_cast<std::vector<float>::size_type> (index)] >= 0.0f)
        {
            // shifting up
            return frequencyP_[static_cast<std::vector<float>::size_type> (index)] * pitchBendUpSemitones_ * 100;
        }
        else
        {
            // shifting down
            return -1 * frequencyP_[static_cast<std::vector<float>::size_type> (index)] * pitchBendDownSemitones_ * 100;
        }
    }

    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        float oscillatorFrequency;
        float oscGain;

        if (buttonPressed == true)
        {
            changeOscillator();
            buttonPressed = false; // Reset the flag after changing the oscillator
        }
        else
        {
            buttonPressed = true;
        }

        for (unsigned int n = 0; n < kNumOscillators_; ++n)
        {
            float frequencyOffset = ((n + 1) * frequencyP_[n]) * (n * frequencyIncrement_);
            float harmonicFrequency = noteHz (midiNoteNumber, 0) * (n + 1); // calculate frequency for the current harmonic
            frequencyN_[n] = harmonicFrequency + frequencyOffset;
            level_ = velocity;
            for (unsigned int s = 0; s < 4; ++s)
            {
                oscillatorFrequency = frequencyN_[n];
                oscillators_[n]->setFrequency (oscillatorFrequency);

                oscGain = gains_[n];

                oscillators_[n]->setAmplitude (oscGain);
            }
        }
    }

    void stopNote (float /*velocity*/, bool /*allowTailOff*/) override
    {
        clearCurrentNote();
    }

    void pitchWheelMoved (int /*newValue*/) override {}

    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override {}

    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float value = 0.0f;
            for (unsigned int i = 0; i < oscillators_.size(); ++i)
            {
                value += (oscillators_[i]->process()) * gains_[i];
            }

            value *= masterGain_;

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                outputBuffer.addSample (channel, startSample + sample, value);
        }
    }

    // TODO
    std::vector<int> waveType_;
    bool buttonPressed = false;

private:
    void CreateWaveTable()
    {
        sineTable_.clear();
        sineTable_.resize (wavetableSize_);
        generation_ = std::make_unique<GenerateWavetable> ((float) getSampleRate(), sineTable_, phase_);
        for (unsigned int n = 0; n < kNumOscillators_; ++n)
        {
            sineTable_ = generation_->prompt_Harmonics ((1));
        }
    }

    void CreateNewWaveTable()
    {
        sineTable_.clear();
        sineTable_.resize (wavetableSize_);
        generation_ = std::make_unique<GenerateWavetable> ((float) getSampleRate(), sineTable_, phase_);
        for (unsigned int n = 0; n < kNumOscillators_; ++n)
        {
            sineTable_ = generation_->prompt_Harmonics (static_cast<unsigned int> (waveType_[n]));
        }
    }

    void CreateOscillator()
    {
        CreateWaveTable();
        for (unsigned int n = 0; n < kNumOscillators_; ++n)
        {
            oscillators_[n] = std::make_unique<Wavetable> ((float) getSampleRate(), sineTable_, phase_);
        }
    }
    void changeOscillator()
    {
        if (buttonPressed == true)
        {
            CreateNewWaveTable();
            buttonPressed = false; // Reset the flag after changing the oscillator

            for (unsigned int n = 0; n < kNumOscillators_; ++n)
            {
                oscillators_[n] = std::make_unique<Wavetable> ((float) getSampleRate(), sineTable_, phase_);
            }
        }
        else
        {
            buttonPressed = true; // Set the flag to false if it was previously true
        }
    }
    constexpr static unsigned int kNumOscillators_ = 33;
    constexpr static size_t wavetableSize_ = 1024;

    float level_ = 0.0f;
    float phase_ = 0.0f;
    float masterGain_ = 0.0f;
    float frequencyIncrement_ = 0.5f;
    int pitchBendUpSemitones_ = 24;
    int pitchBendDownSemitones_ = 12;

    std::array<float, kNumOscillators_> gains_;
    std::array<float, kNumOscillators_> frequencyP_;
    std::array<float, kNumOscillators_> frequencyN_;
    std::array<std::unique_ptr<Wavetable>, kNumOscillators_> oscillators_;

    std::vector<float> sineTable_;

    std::unique_ptr<GenerateWavetable> generation_;
};