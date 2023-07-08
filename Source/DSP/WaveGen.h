#pragma once

#include <vector>

#include "WaveSetup.h"
#include <JuceHeader.h>
#include <arm_neon.h>
#include <cmath>


enum class WavetableType
{
    Sine = 0,
    Triangle,
    Square,
    Saw,
    NumWavetableTypes
};
constexpr static int numWavetableTypes = static_cast<int> (WavetableType::NumWavetableTypes);

class GenerateWavetable
{
public:
    // Default Constructor
    GenerateWavetable() {}

    // Default Destructor
    ~GenerateWavetable() { wavetable_.clear(); }

    // Additional Constructor with arguments
    GenerateWavetable (float sampleRate, std::vector<float>& wavetable, float phase);

    // Sets up important variables used in the classes functions
    void setup (float sampleRate, std::vector<float>& wavetable, float phase);

    // When applies makes a wave semi bandlimited
    inline float poly_blep (float t, float dt);

    // Creates the wave type and sets it to the wavetable
    inline float prompt_WaveType (WavetableType waveNumber, float n);

    // Used to create modulators
    std::vector<Wavetable*> prompt_Modulator (std::vector<Wavetable*> gOscillators, WavetableType waveNumber);

    // Used to create carriers
    std::vector<float> prompt_Harmonics (WavetableType waveNumber);

private:
    // Buffer holding the wavetable
    std::vector<float> wavetable_;

    // 1 divided by the audio sample rate
    float inverseSampleRate_;

    float sampleRate_;

    float phaseIncrement_;

    float phase_;
};
