#include "CustomButton.h"

CustomButton::CustomButton (WavetableSynthesiserVoice& voice)
    : juce::Button ("CustomButton"),
      currentWaveType (WavetableType::Sine),
      voice_ (&voice)
{
    setClickingTogglesState (true);
}

CustomButton::~CustomButton()
{
}

void CustomButton::paintButton (juce::Graphics& /*g*/, bool /*isMouseOver*/, bool /*isButtonDown*/)
{
}

void CustomButton::drawSineWave (juce::Graphics& g, int startX, int startY, int amplitude, int wavelength, int period, juce::Colour colour)
{
    g.setColour (colour);

    const int waveLengthPixels = wavelength * period;
    const int sineSize = 1;
    const int waveHeight = sineSize * 2;

    // Calculate the new startY position
    startY += waveHeight + 3; // Adjust the value as needed

    // Starts for loop 4 pixels in and ends at 4 pixels less than waveLengthPixels
    for (int i = 4; i < waveLengthPixels - 4; i++)
    {
        float x = startX + i;
        float sine = amplitude * std::sin (2 * juce::MathConstants<float>::pi * i / wavelength);
        float y = startY + sine;

        g.drawLine (static_cast<int> (x), static_cast<int> (y), static_cast<int> (x), static_cast<int> (y + 1 + waveHeight));
    }
}

void CustomButton::drawTriangleWave (juce::Graphics& g, int startX, int startY, int amplitude, int wavelength, int period, juce::Colour colour)
{
    g.setColour (colour);
    const int sineSize = 1;
    const int waveLengthPixels = wavelength * period;
    const int waveHeight = sineSize * 2;

    // Calculate the new startY position
    startY += waveHeight + 3; // Adjust the value as needed

    // Starts for loop 4 pixels in and ends at 4 pixels less than waveLengthPixels
    for (int i = 4; i < waveLengthPixels - 4; i++)
    {
        float x = startX + i;
        float triangle = (2 * amplitude / juce::MathConstants<float>::pi) * std::asin (std::sin (2 * juce::MathConstants<float>::pi * i / wavelength));
        float y = startY + triangle;

        g.drawLine (static_cast<int> (x), static_cast<int> (y), static_cast<int> (x), static_cast<int> (y + 1 + waveHeight));
    }
}

void CustomButton::drawSquareWave (juce::Graphics& g, int startX, int startY, juce::Colour colour)
{
    g.setColour (colour);
    const int sineSize = 2;
    const int period = 1;
    const int amplitude = 20;
    const int wavelength = 15;
    const int waveLengthPixels = wavelength * period;
    const int waveHeight = sineSize * 2;

    startY += waveHeight - 2;
    startX += 5; // Adjust the value as needed to move the wave to the right

    // Vertical line at the start
    g.drawLine (startX, startY, startX, startY + waveHeight * 2);

    // First loop
    for (int i = 0; i < waveLengthPixels - 10; i += wavelength)
    {
        float x1 = startX + i;
        float y1 = startY;
        float x2 = startX + i + wavelength / 2;
        float x3 = startX + i + wavelength;
        int sizeInc = 1;

        // Draw lines with increased thickness
        g.drawLine (static_cast<int> (x1), static_cast<int> (y1), static_cast<int> (x1), static_cast<int> (y1 + waveHeight * 2), 2);
        g.drawLine (static_cast<int> (x1), static_cast<int> (y1), static_cast<int> (x2), static_cast<int> (y1), 2);
        g.drawLine (static_cast<int> (x2), static_cast<int> (y1), static_cast<int> (x2), static_cast<int> (y1 + waveHeight * 2), 2);
        g.drawLine (static_cast<int> (x2), static_cast<int> (y1 + waveHeight * 2), static_cast<int> (x3), static_cast<int> (y1 + waveHeight * 2), 2);
        g.drawLine (static_cast<int> (x3), static_cast<int> (y1 + sizeInc), static_cast<int> (x3), static_cast<int> (y1 + waveHeight * 2), 2);
    }
}

void CustomButton::drawSawWave (juce::Graphics& g, int startX, int startY, juce::Colour colour)
{
    g.setColour (colour);
    const int amplitude = 10;
    const int wavelength = 25;
    const int period = 1;

    const int waveLengthPixels = wavelength * period;

    startX += 5;

    g.drawLine (startX, startY, startX, startY + amplitude, 2);

    // First loop
    for (int i = 0; i < waveLengthPixels; i += wavelength)
    {
        float x1 = startX + i;
        float y1 = startY;
        float x2 = startX + i + wavelength / 2;
        float y2 = startY + amplitude;

        g.drawLine (static_cast<int> (x1), static_cast<int> (y1), static_cast<int> (x2), static_cast<int> (y2), 2);
        g.drawLine (static_cast<int> (x2), static_cast<int> (y2), static_cast<int> (x2), static_cast<int> (y1 / 2), 2);
    }
}

void CustomButton::mouseDown (const juce::MouseEvent& event)
{
    if (event.mods.isLeftButtonDown())
    {
        const auto newWavetypeIndex = (static_cast<int> (currentWaveType) + 1) % numWavetableTypes;
        currentWaveType = static_cast<WavetableType> (newWavetypeIndex);

        repaint(); // Trigger a repaint to update the button appearance
    }
    for (unsigned int n = 0; n < kNumOscillators_; ++n)
    {
        voice_->setWaveType (n, currentWaveType);
    }
}
void CustomButton::setButtonColour (juce::Colour colourToUse)
{
    mainSliderColour_ = colourToUse;
}
void CustomButton::paint (juce::Graphics& g)
{
    switch (currentWaveType)
    {
        case (WavetableType::Sine):
            drawSineWave (g, 0, 0, amplitude_, wavelength_, period_, mainSliderColour_);
            break;
        case (WavetableType::Triangle):
            drawTriangleWave (g, 0, 0, amplitude_, wavelength_, period_, mainSliderColour_);
            break;
        case (WavetableType::Square):
            drawSquareWave (g, 0, 0, mainSliderColour_);
            break;
        case (WavetableType::Saw):
            drawSawWave (g, 0, 0, mainSliderColour_);
            break;
        default:
            // Oops, you're using an invalid wave type
            jassertfalse;
            break;
    }
}
