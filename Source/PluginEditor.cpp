/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

String ObliqueDelayV2AudioProcessorEditor::concreteToolTip ("The concrete mode provides you with a series of lessons aimed to teach you the basics of reverb usage in a variety of production and mix settings.");

String ObliqueDelayV2AudioProcessorEditor::obliqueToolTip ("The oblique mode provides you with a series of prompts that are aimed to stimulate creativity in the sound design and mixing process. These will not provide direct instructions; only abstract concepts to use as brain food.");

String ObliqueDelayV2AudioProcessorEditor::lessonsToolTip ("This selection box allows you to choose which lesson you'd like to undertake. Note that this will only appear for the Concrete Mode. To change the Oblique prompt, use the next and previous arrows at the bottom right of the User Interface");

String ObliqueDelayV2AudioProcessorEditor::nextToolTip ("Loads the next prompt.");

String ObliqueDelayV2AudioProcessorEditor::previousToolTip ("Re-loads the previous prompt");
String ObliqueDelayV2AudioProcessorEditor::mixToolTip ("Sets the relative amount of dry (non-delayed) versus wet (delayed) signal that is output by the plug-in");

String ObliqueDelayV2AudioProcessorEditor::timeToolTip ("Sets the delay time in milliseconds of the delay; that is, the time between each fedback echo. Selecting the bpm sync mode lets you set time as a proportion of the bpm of your track, allowing for your delay tails to be synced and in time with your track.");

String ObliqueDelayV2AudioProcessorEditor::feedbackToolTip ("Sets the feedback of the delay - higher values cause a longer delay tail.");
String ObliqueDelayV2AudioProcessorEditor::bypassToolTip ("Bypasses this effect.");

ObliqueDelayV2AudioProcessorEditor::ObliqueDelayV2AudioProcessorEditor (ObliqueDelayV2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setLookAndFeel(&otherLookAndFeelSlider);
    
    addAndMakeVisible(&mMixSlider);
    mMixSlider.setTooltip(mixToolTip);
    
    addAndMakeVisible(&mTimeSlider);
    mTimeSlider.setTooltip(timeToolTip);
    
    addAndMakeVisible(&mFeedbackSlider);
    mFeedbackSlider.setTooltip(feedbackToolTip);
       
    addAndMakeVisible(&mBypassButton);
    mBypassButton.setButtonText("Bypass");
    mBypassButton.setTooltip(bypassToolTip);
       
    addAndMakeVisible(oblique);
    oblique.setName("Oblique");
    oblique.setComponentID("oblique");
    oblique.setButtonText("Oblique");
    oblique.setRadioGroupId(1);
    oblique.addListener(this);
    oblique.setTooltip(obliqueToolTip);
       
    addAndMakeVisible(concrete);
    concrete.setName("Concrete");
    concrete.setComponentID("concrete");
    concrete.setButtonText("Concrete");
    concrete.setRadioGroupId(1);
    concrete.addListener(this);
    concrete.setTooltip(concreteToolTip);
          
    addAndMakeVisible(obliqueConcreteChoices);
    obliqueConcreteChoices.setName("Oblique Concrete");
    obliqueConcreteChoices.setComponentID("obConcrete");
    obliqueConcreteChoices.setTextWhenNothingSelected("Lessons");
    obliqueConcreteChoices.setTooltip(lessonsToolTip);
    obliqueConcreteChoices.setSelectedItemIndex(currentItemIndex);
    obliqueConcreteChoices.addListener(this);

    next.setComponentID("next");
    next.addListener(this);
    next.setTooltip(nextToolTip);
    addAndMakeVisible(next);
    
    previous.setComponentID("previous");
    previous.addListener(this);
    previous.setTooltip(previousToolTip);
    addAndMakeVisible(previous);
    
    concrete.triggerClick();
       
    addAndMakeVisible(text);
    addAndMakeVisible(tooltipWindow);
    
    addAndMakeVisible(mSyncModeButon);
    mSyncModeButon.setButtonText("Sync Time");
    addAndMakeVisible(mSyncedTimeSlider);
    //addAndMakeVisible(mSyncedTimeSliderRight);
    mSyncModeButon.addListener(this);
    //mSyncModeButon.triggerClick();
    mSyncedTimeSlider.setSkewFactorFromMidPoint(0.5);
       
    mSyncedTimeSlider.textFromValueFunction = [] (double val) {
           String toReturn;
           
           if(val < 0.124) toReturn = "1/32 T";
           else if(val == 0.125) toReturn = "1/32";
           else if (val < 0.1875 && val > 0.125) toReturn = "1/16 T";
           else if (val == 0.1875) toReturn = "1/32 D";
           else if (val == 0.25) toReturn = "1/16";
           else if (val > 0.25 && val < 0.375) toReturn = "1/8 T";
           else if (val == 0.375) toReturn = "1/16 D";
           else if (val == 0.5) toReturn = "1/8";
           else if (val > 0.5 && val < 0.75) toReturn = "1/4 T";
           else if (val == 0.75) toReturn = "1/8 D";
           else if (val == 1) toReturn = "1/4";
           else if (val > 1.0 && val < 1.5) toReturn = "1/2 T";
           else if (val == 1.5) toReturn = "1/4D";
           else toReturn = "";
           
           return toReturn;
      };
       
    addTextToOblique();
    addTextToConcrete();
    
    addAndMakeVisible(mFrequencySlider);
    mFilterChoice.setName("Filter Choice");
    mFilterChoice.addItem("Low Pass", 1);
    mFilterChoice.addItem("High Pass", 2);
    mFilterChoice.addItem("Band Pass", 3);
    mFilterChoice.addItem("Notch", 4);
    mFilterChoice.addItem("Peak", 5);
    mFilterChoice.addItem("Low Shelf", 6);
    mFilterChoice.addItem("High Shelf", 7);
    mFilterChoice.setSelectedId(static_cast<int>
                               (*processor.getValueTreeState()
                                .getRawParameterValue("biqchoice")));
    mFilterChoice.addListener(this);
    addAndMakeVisible(&mFilterChoice);
    
    int i = 1;
       
    for(String s : concreteLabels) {
        obliqueConcreteChoices.addItem(s, i);
        i++;
    }
       
    text.setName("lessons");
    text.setText(obliqueTexts.getReference(currentItemIndex), dontSendNotification);
    obliqueConcreteChoices.setSelectedId(currentItemIndex);
    mSyncModeButon.triggerClick();
       
    setSize (500, 500);
}

ObliqueDelayV2AudioProcessorEditor::~ObliqueDelayV2AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================

void ObliqueDelayV2AudioProcessorEditor::comboBoxChanged(ComboBox* c)
{
    if(c == &obliqueConcreteChoices)
    {
        text.setText(concreteTexts.getReference(c->getSelectedId()-1),
        dontSendNotification);
    } /*else if (c == &mFilterChoice) {
        processor.biquadChoice = mFilterChoice.getSelectedIdAsValue().getValue();
    }*/
}

void ObliqueDelayV2AudioProcessorEditor::buttonStateChanged(Button* b)
{
    /*if(b == &mSyncModeButon)
    {
        if(b->getToggleState())
        {
            mSyncedTimeSlider.setVisible(true);
            mSyncedTimeSlider.setEnabled(true);
            mSyncedTimeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
            mTimeSlider.setVisible(false);
            mTimeSlider.setEnabled(false);
            mTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 90, 60);
            //b->setToggleState(false, dontSendNotification);
        } else
        {
            mSyncedTimeSlider.setVisible(false);
            mSyncedTimeSlider.setEnabled(false);
            mSyncedTimeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
            mTimeSlider.setVisible(true);
            mTimeSlider.setEnabled(true);
            mTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 90, 60);
            //b->setToggleState(true, dontSendNotification);
        }
    }*/
    
    
}

void ObliqueDelayV2AudioProcessorEditor::buttonClicked(Button* b)
{
    if(b == &next)
    {
        currentItemIndex++;
        if(concrete.getToggleState())
        {
            if(currentItemIndex >= obliqueConcreteChoices
            .getNumItems())
            {
                currentItemIndex = 1;
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);

            } else
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);
            }
        } else
        {
            
            text.setText(obliqueTexts.getReference
                         (rand.nextInt(obliqueTexts.size()-1)),
                         dontSendNotification);
        }
    } else if(b == &previous) {
         currentItemIndex--;
        if(concrete.getToggleState())
        {
            if(currentItemIndex >= 0)
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);
            } else
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(obliqueConcreteChoices
                                        .getNumItems()-1);
                currentItemIndex = obliqueConcreteChoices
                .getNumItems()-1;
            }
        } else {
            if(currentItemIndex >= 0)
            {
                text.setText(obliqueTexts
                             .getReference(currentItemIndex),
                             dontSendNotification);
            } else
            {
                currentItemIndex = obliqueTexts.size() - 1;
                       
                text.setText(obliqueTexts
                             .getReference(currentItemIndex),
                             dontSendNotification);
            }
        }
    } else if (b == &oblique)
    {
        obliqueConcreteChoices.setEnabled(false);
        obliqueConcreteChoices.setVisible(false);
        text.setText(obliqueTexts.getReference(0),
                     dontSendNotification);
        oblique.setToggleState(true, dontSendNotification);
        concrete.setToggleState(false, dontSendNotification);
        concrete.setAlpha(0.5);
        oblique.setAlpha(1.0);
    } else if (b == &concrete)
    {
        obliqueConcreteChoices.setEnabled(true);
        obliqueConcreteChoices.setVisible(true);
        oblique.setToggleState(false, dontSendNotification);
        concrete.setToggleState(true, dontSendNotification);
        text.setText(concreteTexts
                     .getReference(obliqueConcreteChoices
                                   .getSelectedId()-1),
                     dontSendNotification);
        oblique.setAlpha(0.5);
        concrete.setAlpha(1.0);
    } else if (b == &mSyncModeButon)
    {
        if(b->getToggleState())
        {
            mSyncModeButon.setToggleState(false, dontSendNotification);
            mSyncedTimeSlider.setEnabled(false);
            mSyncedTimeSlider.setVisible(false);
            mSyncedTimeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
            mTimeSlider.setEnabled(true);
            mTimeSlider.setVisible(true);
            mTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
            
            /*mSyncedTimeSliderRight.setEnabled(false);
            mSyncedTimeSliderRight.setVisible(false);
            mSyncedTimeSliderRight.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
            mTimeSliderRight.setEnabled(true);
            mTimeSliderRight.setVisible(true);
            mTimeSliderRight.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);*/
            //b->setToggleState(false, dontSendNotification);
        } else
        {
            mSyncModeButon.setToggleState(true, dontSendNotification);
            mSyncedTimeSlider.setEnabled(true);
            mSyncedTimeSlider.setVisible(true);
            mSyncedTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
            mTimeSlider.setEnabled(false);
            mTimeSlider.setVisible(false);
            mTimeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
            
            /*mSyncedTimeSliderRight.setEnabled(true);
            mSyncedTimeSliderRight.setVisible(true);
            mSyncedTimeSliderRight.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 20);
            mTimeSliderRight.setEnabled(false);
            mTimeSliderRight.setVisible(false);
            mTimeSliderRight.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);*/
        }
    }
    
}
void ObliqueDelayV2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::grey);

    g.setColour (Colours::white);
    g.setFont (17.0f);
    g.setFont(textFont);
             
    Rectangle<int> topBox (0,0, getWidth()-20, (getHeight()-10)/3);
    Rectangle<int> box (0, getHeight()/2, getWidth()-20,
                              getHeight()-10/3);
    Rectangle<int> bottomBox (0, getHeight()/3, getWidth()-20,
                                    getHeight()-10/3);
       
    box = box.withTop(10);
    topBox = topBox.withTop(160);
    text.setColour(Label::textColourId, juce::Colours::white);
    text.setFont(labelFont);
       
    const auto width = topBox.getWidth() / 4;
    g.drawFittedText(TRANS("Mix"), topBox.removeFromLeft (width), Justification::centred, 1);
    g.drawFittedText (TRANS ("Time"), topBox.removeFromLeft (width), Justification::centred, 1);
    //g.drawFittedText (TRANS ("Time Right"), topBox.removeFromLeft (width), Justification::centred, 1);
    g.drawFittedText (TRANS ("Feedback"), topBox.removeFromLeft (width), Justification::centred, 1);
    g.drawFittedText(TRANS(""), topBox.removeFromLeft(width), Justification::centred, 1);
}

void ObliqueDelayV2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Rectangle<int> topBox (0,0, getWidth()-20, (getHeight()-10)/3);
    Rectangle<int> box (0, getHeight()/2, getWidth()-20,
                           getHeight()-10/3);
    Rectangle<int> bottomBox (0, getHeight()/3-150, getWidth()-20,
                                 getHeight()-10/3);
       
    box = box.withTop(20);
    topBox = topBox.withTop(20);


    const auto width = topBox.getWidth() / 4;
    mMixSlider.setBounds (topBox.removeFromLeft (width).reduced (10));
    mTimeSlider.setBounds (mMixSlider.getWidth(), 0, width-10, topBox.getHeight() - 30);
    mTimeSlider.setBounds (topBox.removeFromLeft (width).reduced (10));
    //mTimeSliderRight.setBounds(topBox.removeFromLeft(width).reduced(10));
    mSyncModeButon.setBounds(mTimeSlider.getX()+12, topBox.getHeight()+30, 80, 30);
    mSyncedTimeSlider.setBounds(mTimeSlider.getBounds());
    //mSyncedTimeSliderRight.setBounds(mTimeSliderRight.getBounds());
    mFeedbackSlider.setBounds (topBox.removeFromLeft (width).reduced (10));
    mBypassButton.setBounds(topBox.removeFromLeft(width)
                               .reduced(10));
    //mFilterChoice.setBounds(mFrequencySlider.getX(), topBox.getHeight()+30, 100, 30);
       
    const auto midWidth = box.getWidth() / 3;
    obliqueConcreteChoices.setBounds(10, getHeight()/2-30,
                                           midWidth+50, 30);
    oblique.setBounds(midWidth*2 + 25,  getHeight()/2-30, 75, 30);
    concrete.setBounds(midWidth*2 + 100, getHeight()/2-30, 75, 30);
       
    previous.setBounds(getWidth()-100, getHeight()-40, 50, 30);
    next.setBounds(getWidth()-50, getHeight()-40, 50, 30);
    text.setBounds(bottomBox.reduced(10).removeFromBottom(250));
    text.toBack();
    next.setAlpha(0.5);
    text.setFont(textFont);
    previous.setAlpha(0.5);
}
