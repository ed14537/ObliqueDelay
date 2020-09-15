/*
  ==============================================================================

    OtherLookAndFeel.h
    Created: 10 Sep 2020 9:07:02am
    Author:  Ellis Domenger-Boyce

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OtherLookAndFeelSlider : public juce::LookAndFeel_V4

{
public:
    OtherLookAndFeelSlider() {
        setColour (juce::Slider::thumbColourId, juce::Colours::red);
        
        auto comboBackground = juce::Colours::grey;
        auto comboArrow = juce::Colours::white;
        auto outline = juce::Colours::grey;
        
        setColour(ComboBox::backgroundColourId, comboBackground);
        setColour(PopupMenu::backgroundColourId, comboBackground);
        setColour(ComboBox::arrowColourId, comboArrow);
        setColour(ComboBox::outlineColourId, outline);
        setColour(TextButton::buttonColourId, juce::Colours::grey);
        setColour(TextButton::buttonOnColourId, juce::Colours::yellow);
        setColour(TextButton::textColourOnId, juce::Colours::grey);
        setColour(TooltipWindow::backgroundColourId, comboBackground);
        
    }
    
    juce::Font myFont {"Arial", 17, Font::plain};
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width,
                           int height, float sliderPos,
                           const float rotaryStartAngle,
                           const float rotaryEndAngle, juce::Slider& slider) override
    {
        auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
        auto centreX = (float) x + (float) width  * 0.5f;
        auto centreY = (float) y + (float) height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        g.setColour (juce::Colours::yellow);
        g.fillEllipse (rx, ry, rw, rw);

        // outline
        g.setColour (juce::Colours::purple);
        g.drawEllipse (rx, ry, rw, rw, 1.0f);
        g.setFont(myFont);

        juce::Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));

        // pointer
        g.setColour (juce::Colours::grey);
        g.fillPath (p);

    }

    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;

        buttonArea.removeFromLeft (edge);
        buttonArea.removeFromTop (edge);

        // shadow
        g.setColour (juce::Colours::darkgrey.withAlpha (0.5f));
        g.fillRect (buttonArea);

        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate (offset, offset);

        g.setColour (backgroundColour);
        g.fillRect (buttonArea);
    }

    void drawButtonText (juce::Graphics& g, juce::TextButton& button, bool, bool isButtonDown) override
    {
        auto font = getTextButtonFont (button, button.getHeight());
        g.setFont (font);
        g.setFont(myFont);
        g.setColour (button.findColour (button.getToggleState() ? juce::TextButton::textColourOnId
                                                                : juce::TextButton::textColourOffId)
                           .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

        auto yIndent = juce::jmin (4, button.proportionOfHeight (0.3f));
        auto cornerSize = juce::jmin (button.getHeight(), button.getWidth()) / 2;

        auto fontHeight = juce::roundToInt (font.getHeight() * 0.6f);
        auto leftIndent  = juce::jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft()  ? 4 : 2));
        auto rightIndent = juce::jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        auto textWidth = button.getWidth() - leftIndent - rightIndent;

        auto edge = 4;
        auto offset = isButtonDown ? edge / 2 : 0;

        if (textWidth > 0)
            g.drawFittedText (button.getButtonText(),
                              leftIndent + offset, yIndent + offset, textWidth, button.getHeight() - yIndent * 2 - edge,
                              juce::Justification::centred, 2);
    }
    
    
    
};
