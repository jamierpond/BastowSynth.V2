#pragma once
#include "../../Source/ParamId.h"
#include <JuceHeader.h>
class GainSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    GainSliderLookAndFeel();
    ~GainSliderLookAndFeel() override;

    void drawLinearSlider (juce::Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;

    void drawCross (juce::Graphics& g, int crossX, int crossY, int crossSize, juce::Colour colour);

    float thumbPosition (int x);

    void setSliderColour (juce::Colour colourToUse)
    {
        mainSliderColour_ = colourToUse;
    }

    void setSliderText (std::string textToUse)
    {
        mainText_ = textToUse;
    }

    void setSliderFont (juce::Font fontToUse)
    {
        mainFont_ = fontToUse;
    }

private:
    juce::Colour mainSliderColour_ = juce::Colours::transparentBlack;
    std::string mainText_ = " hello ";
    juce::Font mainFont_ = 10.f;
    float maxPoint_ = 0.f;
    //-------------------------------------------------------------------------------
    // Used for paint cross for loop
    const int crossSize_ = 3;
    static constexpr int colourSchemeSize_ = 33;
    static constexpr int textSize_ = 33;
    //-------------------------------------------------------------------------------

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainSliderLookAndFeel)
};
