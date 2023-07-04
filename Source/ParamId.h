
#pragma once
#include <JuceHeader.h>

// https://corecoding.com/utilities/rgb-or-hex-to-float.php

// Component Volume Button 1 - 3 ID's
constexpr static int versionHint = 1;
const static juce::String cvb1Id =  "cvb1";
const static juce::String CVB1Name =  "CVB1";
const static juce::String cvb2Id =  "cvb2";
const static juce::String CVB2Name =  "CVB2";
const static juce::String gain0Id =  "gain0Id";
const static juce::String Gain0Name =  "Gain0ID";
const static juce::String cvb3Id =  "cvb3";
const static juce::String CVB3Name =  "CVB3";

constexpr static std::string_view baseGainId = "gainId";
constexpr static std::string_view baseGainName = "GainName";
constexpr static std::string_view baseFreqId = "freqId";
constexpr static std::string_view baseFreqName = "FreqName";
constexpr static std::string_view baseWaveTypeId = "waveTypeId";
constexpr static std::string_view baseWaveTypeName = "WaveTypeName";

template <typename T>
constexpr static std::string concatenateStringAndInt(T base, int index)
{
    return std::string(base) + std::to_string(index);
}

constexpr static std::string getWaveTypeId(int index)
{
    return concatenateStringAndInt(baseWaveTypeId, index);
}

constexpr static std::string getGainId(int index)
{
    return concatenateStringAndInt(baseGainId, index);
}

namespace C1
{
    const juce::Colour red = juce::Colour::fromFloatRGBA (0.91f, 0.25f, 0.25f, 1.0f);
    const juce::Colour orange = juce::Colour::fromFloatRGBA (0.91f, 0.62f, 0.25f, 1.0f);
    const juce::Colour yellow = juce::Colour::fromFloatRGBA (0.81f, 0.74f, 0.15f, 1.0f);
    const juce::Colour brightGreen = juce::Colour::fromFloatRGBA (0.64f, 0.81f, 0.15f, 1.0f);
    const juce::Colour limeGreen = juce::Colour::fromFloatRGBA (0.31f, 0.91f, 0.25f, 1.0f);
    const juce::Colour brightBlue = juce::Colour::fromFloatRGBA (0.25f, 0.66f, 0.91f, 1.0f);
    const juce::Colour blue = juce::Colour::fromFloatRGBA (0.25f, 0.42f, 0.91f, 1.0f);
    const juce::Colour violet = juce::Colour::fromFloatRGBA (0.62f, 0.25f, 0.91f, 1.0f);
    const juce::Colour magenta = juce::Colour::fromFloatRGBA (0.91f, 0.25f, 0.80f, 1.0f);
    const juce::Colour cosmic = juce::Colour::fromFloatRGBA (0.914f, 0.251f, 0.439f, 1.0f);
    const juce::Colour grey = juce::Colour::fromFloatRGBA (0.42f, 0.42f, 0.42f, 1.0f);
    const juce::Colour black = juce::Colour::fromFloatRGBA (0.0f, 0.0f, 0.0f, 1.0f);
} // namespace ParamNames

namespace C2
{

    const juce::Colour red = juce::Colour::fromFloatRGBA (0.616f, 0.286f, 0.286f, 1.0f);
    const juce::Colour orange = juce::Colour::fromFloatRGBA (0.714f, 0.549f, 0.349f, 1.0f);
    const juce::Colour yellow = juce::Colour::fromFloatRGBA (0.616f, 0.612f, 0.349f, 1.0f);
    const juce::Colour brightGreen = juce::Colour::fromFloatRGBA (0.545f, 0.616f, 0.353f, 1.0f);
    const juce::Colour limeGreen = juce::Colour::fromFloatRGBA (0.376f, 0.612f, 0.353f, 1.0f);
    const juce::Colour brightBlue = juce::Colour::fromFloatRGBA (0.357f, 0.518f, 0.616f, 1.0f);
    const juce::Colour blue = juce::Colour::fromFloatRGBA (0.333f, 0.396f, 0.588f, 1.0f);
    const juce::Colour violet = juce::Colour::fromFloatRGBA (0.412f, 0.251f, 0.541f, 1.0f);
    const juce::Colour magenta = juce::Colour::fromFloatRGBA (0.494f, 0.282f, 0.459f, 1.0f);
    const juce::Colour cosmic = juce::Colour::fromFloatRGBA (0.494f, 0.251f, 0.322f, 1.0f);
    const juce::Colour grey = juce::Colour::fromFloatRGBA (0.361f, 0.329f, 0.329f, 1.0f);
    const juce::Colour white = juce::Colour::fromFloatRGBA (0.f, 0.f, 0.f, 1.0f);
} // namespace ParamNames

namespace C3
{
    const juce::Colour red = juce::Colour::fromFloatRGBA (0.569f, 0.f, 0.f, 1.0f);
    const juce::Colour orange = juce::Colour::fromFloatRGBA (0.686f, 0.376f, 0.f, 1.0f);
    const juce::Colour yellow = juce::Colour::fromFloatRGBA (0.616f, 0.604f, 0.f, 1.0f);
    const juce::Colour brightGreen = juce::Colour::fromFloatRGBA (0.427f, 0.584f, 0.f, 1.0f);
    const juce::Colour limeGreen = juce::Colour::fromFloatRGBA (0.063f, 0.576f, 0.008f, 1.0f);
    const juce::Colour brightBlue = juce::Colour::fromFloatRGBA (0.f, 0.38f, 0.62f, 1.0f);
    const juce::Colour blue = juce::Colour::fromFloatRGBA (0.008f, 0.173f, 0.671f, 1.0f);
    const juce::Colour violet = juce::Colour::fromFloatRGBA (0.306f, 0.f, 0.545f, 1.0f);
    const juce::Colour magenta = juce::Colour::fromFloatRGBA (0.478f, 0.f, 0.396f, 1.0f);
    const juce::Colour cosmic = juce::Colour::fromFloatRGBA (0.49f, 0.149f, 0.243f, 1.0f);
    const juce::Colour grey = juce::Colour::fromFloatRGBA (0.247f, 0.231f, 0.255f, 1.0f);
    const juce::Colour white = juce::Colour::fromFloatRGBA (0.f, 0.f, 0.f, 1.0f);
    
} // namespace ParamNames

namespace C4
{
    const juce::Colour offWhite = juce::Colour::fromFloatRGBA (0.83f, 0.83f, 0.89f, 1.0f);
  //  const juce::Colour darkGrey = juce::Colour::fromFloatRGBA (0.42f, 0.42f, 0.42f, 1.0f);
    const juce::Colour darkGrey = juce::Colour::fromFloatRGBA (0.16f, 0.15f, 0.15f, 1.0f);
    const juce::Colour lightGrey = juce::Colour::fromFloatRGBA (0.74f, 0.76f, 0.76f, 1.0f);
    const juce::Colour lightBlack = juce::Colour::fromFloatRGBA (0.13f, 0.13f, 0.13f, 1.0f);
    const juce::Colour shadeGrey = juce::Colour::fromFloatRGBA (0.2f, 0.2f, 0.2f, 1.0f);
    const juce::Colour lightblack = juce::Colour::fromFloatRGBA (0.01f, 0.01f, 0.01f, 1.0f);
    
} // namespace ParamNames

/*
class ParameterNames
{
public:
    struct IdAndName
    {
        std::string id;
        std::string name;
    };

    ParameterNames()
    {
        // Gain names and IDs
        gainNamesAndIds_.emplace_back(IdAndName{"gainIdM", "GainNameM"});
        for (int i = 0; i < NUM_GAINS; ++i)
        {
            auto id = "gainId" + std::to_string(i);
            auto name = "GainName" + std::to_string(i);
            gainNamesAndIds_.emplace_back(IdAndName{id, name});
        }

        // Frequency names and IDs
        for (int i = 0; i < NUM_FREQS; ++i)
        {
            auto id = "freqId" + std::to_string(i);
            auto name = "FreqName" + std::to_string(i);
            freqNamesAndIds_.emplace_back(IdAndName{id, name});
        }

        // Wave type names and IDs
        for (int i = 0; i < NUM_WAVES; ++i)
        {
            auto id = "waveTypeId" + std::to_string(i);
            auto name = "WaveTypeName" + std::to_string(i);
            waveTypeNamesAndIds_.emplace_back(IdAndName{id, name});
        }
    }

    const std::vector<std::string>& getGainNames() const { return getNamesFromVector(gainNamesAndIds_); }
    const std::vector<std::string>& getGainIds() const { return getIdsFromVector(gainNamesAndIds_); }

    const std::vector<std::string>& getFreqNames() const { return getNamesFromVector(freqNamesAndIds_); }
    const std::vector<std::string>& getFreqIds() const { return getIdsFromVector(freqNamesAndIds_); }

    const std::vector<std::string>& getWaveTypeNames() const { return getNamesFromVector(waveTypeNamesAndIds_); }
    const std::vector<std::string>& getWaveTypeIds() const { return getIdsFromVector(waveTypeNamesAndIds_); }

private:
    static const int NUM_GAINS = 34;
    static const int NUM_FREQS = 34;
    static const int NUM_WAVES = 34;

    std::vector<IdAndName> gainNamesAndIds_;
    std::vector<IdAndName> freqNamesAndIds_;
    std::vector<IdAndName> waveTypeNamesAndIds_;

    const std::vector<std::string>& getNamesFromVector(const std::vector<IdAndName>& vector) const
    {
        static std::vector<std::string> names;
        names.clear();
        names.reserve(vector.size());
        for (const auto& element : vector)
            names.emplace_back(element.name);
        return names;
    }

    const std::vector<std::string>& getIdsFromVector(const std::vector<IdAndName>& vector) const
    {
        static std::vector<std::string> ids;
        ids.clear();
        ids.reserve(vector.size());
        for (const auto& element : vector)
            ids.emplace_back(element.id);
        return ids;
    }
};*/
#define gainIdM "gainIdM"
#define GainNameM "GainNameM"

#define gainIdM "gainIdM"
#define GainNameM "GainNameM"

#define gainId0 "gainId0"
#define GainName0 "GainName0"
#define gainId1 "gainId1"
#define GainName1 "GainName1"
#define gainId2 "gainId2"
#define GainName2 "GainName2"
#define gainId3 "gainId3"
#define GainName3 "GainName3"
#define gainId4 "gainId4"
#define GainName4 "GainName4"
#define gainId5 "gainId5"
#define GainName5 "GainName5"
#define gainId6 "gainId6"
#define GainName6 "GainName6"
#define gainId7 "gainId7"
#define GainName7 "GainName7"
#define gainId8 "gainId8"
#define GainName8 "GainName8"
#define gainId9 "gainId9"
#define GainName9 "GainName9"
#define gainId10 "gainId10"
#define GainName10 "GainName10"
#define gainId11 "gainId11"
#define GainName11 "GainName11"
#define gainId12 "gainId12"
#define GainName12 "GainName12"
#define gainId13 "gainId13"
#define GainName13 "GainName13"
#define gainId14 "gainId14"
#define GainName14 "GainName14"
#define gainId15 "gainId15"
#define GainName15 "GainName15"
#define gainId16 "gainId16"
#define GainName16 "GainName16"
#define gainId17 "gainId17"
#define GainName17 "GainName17"
#define gainId18 "gainId18"
#define GainName18 "GainName18"
#define gainId19 "gainId19"
#define GainName19 "GainName19"
#define gainId20 "gainId20"
#define GainName20 "GainName20"
#define gainId21 "gainId21"
#define GainName21 "GainName21"
#define gainId22 "gainId22"
#define GainName22 "GainName22"
#define gainId23 "gainId23"
#define GainName23 "GainName23"
#define gainId24 "gainId24"
#define GainName24 "GainName24"
#define gainId25 "gainId25"
#define GainName25 "GainName25"
#define gainId26 "gainId26"
#define GainName26 "GainName26"
#define gainId27 "gainId27"
#define GainName27 "GainName27"
#define gainId28 "gainId28"
#define GainName28 "GainName28"
#define gainId29 "gainId29"
#define GainName29 "GainName29"
#define gainId30 "gainId30"
#define GainName30 "GainName30"
#define gainId31 "gainId31"
#define GainName31 "GainName31"
#define gainId32 "gainId32"
#define GainName32 "GainName32"
#define gainId33 "gainId33"
#define GainName33 "GainName33"

#define freqId0 "freqId0"
#define FreqName0 "FreqName0"
#define freqId1 "freqId1"
#define FreqName1 "FreqName1"
#define freqId2 "freqId2"
#define FreqName2 "FreqName2"
#define freqId3 "freqId3"
#define FreqName3 "FreqName3"
#define freqId4 "freqId4"
#define FreqName4 "FreqName4"
#define freqId5 "freqId5"
#define FreqName5 "FreqName5"
#define freqId6 "freqId6"
#define FreqName6 "FreqName6"
#define freqId7 "freqId7"
#define FreqName7 "FreqName7"
#define freqId8 "freqId8"
#define FreqName8 "FreqName8"
#define freqId9 "freqId9"
#define FreqName9 "FreqName9"
#define freqId10 "freqId10"
#define FreqName10 "FreqName10"
#define freqId11 "freqId11"
#define FreqName11 "FreqName11"
#define freqId12 "freqId12"
#define FreqName12 "FreqName12"
#define freqId13 "freqId13"
#define FreqName13 "FreqName13"
#define freqId14 "freqId14"
#define FreqName14 "FreqName14"
#define freqId15 "freqId15"
#define FreqName15 "FreqName15"
#define freqId16 "freqId16"
#define FreqName16 "FreqName16"
#define freqId17 "freqId17"
#define FreqName17 "FreqName17"
#define freqId18 "freqId18"
#define FreqName18 "FreqName18"
#define freqId19 "freqId19"
#define FreqName19 "FreqName19"
#define freqId20 "freqId20"
#define FreqName20 "FreqName20"
#define freqId21 "freqId21"
#define FreqName21 "FreqName21"
#define freqId22 "freqId22"
#define FreqName22 "FreqName22"
#define freqId23 "freqId23"
#define FreqName23 "FreqName23"
#define freqId24 "freqId24"
#define FreqName24 "FreqName24"
#define freqId25 "freqId25"
#define FreqName25 "FreqName25"
#define freqId26 "freqId26"
#define FreqName26 "FreqName26"
#define freqId27 "freqId27"
#define FreqName27 "FreqName27"
#define freqId28 "freqId28"
#define FreqName28 "FreqName28"
#define freqId29 "freqId29"
#define FreqName29 "FreqName29"
#define freqId30 "freqId30"
#define FreqName30 "FreqName30"
#define freqId31 "freqId31"
#define FreqName31 "FreqName31"
#define freqId32 "freqId32"
#define FreqName32 "FreqName32"
#define freqId33 "freqId33"
#define FreqName33 "FreqName33"

#define waveTypeId0 "waveTypeId0"
#define WaveTypeName0 "WaveTypeName0"
#define waveTypeId1 "waveTypeId1"
#define WaveTypeName1 "WaveTypeName1"
#define waveTypeId2 "waveTypeId2"
#define WaveTypeName2 "WaveTypeName2"
#define waveTypeId3 "waveTypeId3"
#define WaveTypeName3 "WaveTypeName3"
#define waveTypeId4 "waveTypeId4"
#define WaveTypeName4 "WaveTypeName4"
#define waveTypeId5 "waveTypeId5"
#define WaveTypeName5 "WaveTypeName5"
#define waveTypeId6 "waveTypeId6"
#define WaveTypeName6 "WaveTypeName6"
#define waveTypeId7 "waveTypeId7"
#define WaveTypeName7 "WaveTypeName7"
#define waveTypeId8 "waveTypeId8"
#define WaveTypeName8 "WaveTypeName8"
#define waveTypeId9 "waveTypeId9"
#define WaveTypeName9 "WaveTypeName9"
#define waveTypeId10 "waveTypeId10"
#define WaveTypeName10 "WaveTypeName10"
#define waveTypeId11 "waveTypeId11"
#define WaveTypeName11 "WaveTypeName11"
#define waveTypeId12 "waveTypeId12"
#define WaveTypeName12 "WaveTypeName12"
#define waveTypeId13 "waveTypeId13"
#define WaveTypeName13 "WaveTypeName13"
#define waveTypeId14 "waveTypeId14"
#define WaveTypeName14 "WaveTypeName14"
#define waveTypeId15 "waveTypeId15"
#define WaveTypeName15 "WaveTypeName15"
#define waveTypeId16 "waveTypeId16"
#define WaveTypeName16 "WaveTypeName16"
#define waveTypeId17 "waveTypeId17"
#define WaveTypeName17 "WaveTypeName17"
#define waveTypeId18 "waveTypeId18"
#define WaveTypeName18 "WaveTypeName18"
#define waveTypeId19 "waveTypeId19"
#define WaveTypeName19 "WaveTypeName19"
#define waveTypeId20 "waveTypeId20"
#define WaveTypeName20 "WaveTypeName20"
#define waveTypeId21 "waveTypeId21"
#define WaveTypeName21 "WaveTypeName21"
#define waveTypeId22 "waveTypeId22"
#define WaveTypeName22 "WaveTypeName22"
#define waveTypeId23 "waveTypeId23"
#define WaveTypeName23 "WaveTypeName23"
#define waveTypeId24 "waveTypeId24"
#define WaveTypeName24 "WaveTypeName24"
#define waveTypeId25 "waveTypeId25"
#define WaveTypeName25 "WaveTypeName25"
#define waveTypeId26 "waveTypeId26"
#define WaveTypeName26 "WaveTypeName26"
#define waveTypeId27 "waveTypeId27"
#define WaveTypeName27 "WaveTypeName27"
#define waveTypeId28 "waveTypeId28"
#define WaveTypeName28 "WaveTypeName28"
#define waveTypeId29 "waveTypeId29"
#define WaveTypeName29 "WaveTypeName29"
#define waveTypeId30 "waveTypeId30"
#define WaveTypeName30 "WaveTypeName30"
#define waveTypeId31 "waveTypeId31"
#define WaveTypeName31 "WaveTypeName31"
#define waveTypeId32 "waveTypeId32"
#define WaveTypeName32 "WaveTypeName32"
#define waveTypeId33 "waveTypeId33"
#define WaveTypeName33 "WaveTypeName33"
