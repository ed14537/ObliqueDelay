/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OtherLookAndFeel.h"

//==============================================================================
/**
*/
class ObliqueDelayV2AudioProcessorEditor  : public AudioProcessorEditor, private Button::Listener, private ComboBox::Listener
{
public:
    ObliqueDelayV2AudioProcessorEditor (ObliqueDelayV2AudioProcessor&);
    ~ObliqueDelayV2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ObliqueDelayV2AudioProcessor& processor;
    
    void addTextToOblique()
    {
        obliqueTexts.add("Simulate infinity");
        obliqueTexts.add("Negative Space as foreground");
        obliqueTexts.add("Remove specifics and convert to ambiguities");
        obliqueTexts.add("Humanize something free of error");
        obliqueTexts.add("Randomize something free of error");
        obliqueTexts.add("Go to an extreme before moving back to a more comfortable space");
        obliqueTexts.add("Make the distance reveal the details.");
        obliqueTexts.add("Flatten your perception");
        obliqueTexts.add("Emphasize differences");
        obliqueTexts.add("Remove ambiguities and convert to specifics");
        obliqueTexts.add("Make repetition a form of change");
        obliqueTexts.add("Find difficulty in what should be a simple task");
        obliqueTexts.add("All of it but less");
        obliqueTexts.add("Do the bare minimum");
        obliqueTexts.add("Make audible your mistakes");
        obliqueTexts.add("Make your room");
        obliqueTexts.add("Remove the most important thing");
    }
    
    void addTextToConcrete()
    {
        concreteLabels.add("What is Delay?");
        concreteTexts.add("Delay is an audio effect which repeats an incoming sound signal at a fixed interval. The sound can repeat itself multiple times and be fed back through the delay effect creating a gradual, delaying echo.");
        
        concreteLabels.add("The time parameter");
        concreteTexts.add("The time parameter allows you to control the interval between each echo. This can be automated to create unusual pitching effects. At very low values, this parameter can have an unusual effect on the overall tone of the sound signal, while higher values (60ms+) create the more traditional echo effect");
        
        concreteLabels.add("The feedback parameter");
        concreteTexts.add("The feedback parameter allows you to control what proportion of the sound signal is fed back into the delay effect once it has passed through. Therefore, at 100%, infinite decays are possible as the sound signal self-propogates through the delay, echoing forever. It is mainly used to control the tone and length of the decay tail, with higher values giving rise to longer decay tails");
        
        concreteLabels.add("The input Gain Parameter");
        concreteTexts.add("The input gain parameter controls the volume of the sound signal before it reaches the delay processing. In this plug-in, it functions similar to a dry/wet parameter, controlling the relative proportion of dry (non-delayed) to wet (delayed) signal.");
        
        concreteLabels.add("Automating the time parameter");
        concreteTexts.add("Automating the time parameter of a delay is a common technique that was popularized by dub producers in the 1970s and 80s. In tape-style delays (such as this one), the automation of the delay time creates an unusual perception of a change in pitch of the decay tail, where speeding up the time (i.e. reducing its value) causes the perceived pitch of the tail to increase, while the inverse is true for increasing its value.");
        
        concreteLabels.add("Automating the feedback parameter");
        concreteTexts.add("As we have learnt, the feedback parameter essentially controls the length of the echo tail created by the delay, so automating it allows us to change the length of this tail over time. This can be used to abruptly stop the delay by quickly reducing the feedback to 0. It can also be increased gradually after an element has stopped playing to create a dub-style delay crescendo.");
        
        concreteLabels.add("Delay as a mixing tool: slapback delays");
        concreteTexts.add("A slapback delay is generally defined as a single echo (low feedback value) of 60-180ms that creates a sort of thickening effect on the sound signal that's put into it. Slapdack delay is often used to add a sense of space and stereo width to elements where applying reverb makes it sound too muddy - try it in place of a reverb to see if it achieves the effect you want.");
        
        concreteLabels.add("Delay instead of reverb?");
        concreteTexts.add("Delay is often used instead of reverb where the producer wants to retain space in their mix; that is, they want the effect of adding spatial depth to the sound without muddying the track, which can be especially helpful in busier tracks with complex layered arrangements, where space is at a premium.");
        
        concreteLabels.add("Delay as a send effect");
        concreteTexts.add("When adding delay as a send (if you don't know what a send is, refer to your DAW's manual), always ensure that you set the mix of your delay to 100%. Otherwise, you will have some of the dry signal outputting through the send as well as the through the original track. Only change the mix parameter from 100% if you are inserting it onto the sound signal's effect chain directly. You can change the amount of perceived delay in your track by instead changing the gain control of your send. ");
        
        concreteLabels.add("Delay as a send: More control");
        concreteTexts.add("Adding a delay to a send track can give you more control of the tonal and textural shaping of the delay without altering the original sound source. In some delays, filters and other tonal shaping effects come bundled with the delay, but here, this isn't the case. Try adding other effects to your delay send such as a filter to provide even more control over the delay's tone.");
        
        concreteLabels.add("Beyond this delay: separate l/r time controls");
        concreteTexts.add("Many delays offer you the ability to change the time of the delay being output to the left and right channel separately, allowing for more complex rhythmic interplay and stereo effects. While this adds a bit of complexity to the process of making your delay effect, the extra control will give you a lot of extra room to design sounds and interesting spatial effects in your music.");
        
        concreteLabels.add("Beyond this delay: cross-feedback");
        concreteTexts.add("When a signal coming out of a delay line is routed back into the input of another delay line, this is called cross-feedback. Cross-feedback is used specifically when using stereo delays and allows different delay times to be mixed together to create unique sonic scapes. Cross-feedback makes it easy to create much more complicated delay patterns, so when you move beyond this plugin to one that has controls such as this, you'll find it much easier to create more complex patterns.");
        
        concreteLabels.add("Advanced: Delay as a send: separate l/r delays");
        concreteTexts.add("Since this delay doesn't have controls for the left and right channel, we're going to have to get creative if we want to achieve a similar effect using this one. This can also be done even with a delay that has separate l/r controls, but is particularly useful when we only have one time control. Add an instance of this delay to two different send tracks, and hard pan one to the left and one to the right in your DAW. Send the input signal you'd like to delay to both of these sends, and voila! You now have independent time, feedback and gain controls for the left and right stereo channel of your delay. To take it a step further, you can then send the output of each delay send to the other delay send to simulate cross-feedback!");
        
        concreteLabels.add("Advanced: Simulating multi-tap delays");
        concreteTexts.add("A multi-tap delay is a delay effect where the delay time can be subdivided into multiple 'taps' allowing for the creation of incredible rhythmic delay effects. For example, you might set the delay for 350 milliseconds, then have taps at 1/2 that time and 1/3 of that time. At shorter delay times (5 to ~100ms), they can also be used to create textural sonic effects. We can simulate one using just a few instances of this delay by using multiple single delay plugins in series on a single channel, or in parallel by using multiple send channels (similar to the previous example, but without the panning). If we combine this with the lessons from Delay as a Send Efffect: More Control, we can give each echo its own distinct sound as well!");
        
    }
    
    void buttonStateChanged(Button*) override;
    void comboBoxChanged(ComboBox*) override;
    void buttonClicked(Button*) override;
    int currentItemIndex = 1;
    juce::Array<String> obliqueTexts;
    juce::Array<String> concreteTexts;
    juce::Array<String> concreteLabels;
    
    juce::Random rand;
    int maxNum;
    
    juce::Font textFont {"Arial", 17, Font::plain};
    juce::Font labelFont {"Arial", 14, Font::plain};
    
    static String concreteToolTip;
    static String obliqueToolTip;
    static String lessonsToolTip;
    static String nextToolTip;
    static String previousToolTip;
    static String mixToolTip;
    static String bypassToolTip;
    static String timeToolTip;
    static String feedbackToolTip;
    static String textToolTip;
    TooltipWindow tooltipWindow {this, 1000};
    
    OtherLookAndFeelSlider otherLookAndFeelSlider;
    
    juce::ComboBox obliqueConcreteChoices;
    juce::TextButton oblique;
    juce::TextButton concrete;
    juce::Label text;
    ArrowButton next {"next", 0.0, juce::Colours::white};
    ArrowButton previous {"previous", 0.5, juce::Colours::white};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObliqueDelayV2AudioProcessorEditor)
    
    Slider mMixSlider      { Slider::RotaryHorizontalVerticalDrag,  Slider::TextBoxBelow };
    Slider mTimeSlider      { Slider::RotaryHorizontalVerticalDrag,  Slider::TextBoxBelow };
    Slider mFeedbackSlider  { Slider::RotaryHorizontalVerticalDrag,  Slider::TextBoxBelow };
    TextButton mBypassButton;
    juce::Slider mSyncedTimeSlider {Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };
    juce::TextButton mSyncModeButon;
    Slider mFrequencySlider { Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };
    ComboBox mFilterChoice;
    
public:
    AudioProcessorValueTreeState::SliderAttachment mMixAttachment      { processor.getValueTreeState(), ObliqueDelayV2AudioProcessor::paramMix,     mMixSlider };
    AudioProcessorValueTreeState::SliderAttachment mTimeAttachment      { processor.getValueTreeState(), ObliqueDelayV2AudioProcessor::paramDelayTime,     mTimeSlider };
    AudioProcessorValueTreeState::SliderAttachment mFeedbackAttachment  { processor.getValueTreeState(), ObliqueDelayV2AudioProcessor::paramFeedback, mFeedbackSlider };
    AudioProcessorValueTreeState::ButtonAttachment mBypassAttachment  { processor.getValueTreeState(), ObliqueDelayV2AudioProcessor::paramBypass, mBypassButton };
    AudioProcessorValueTreeState::SliderAttachment mSyncedSliderAttachment {
           processor.getValueTreeState(), ObliqueDelayV2AudioProcessor::paramSyncedTime, mSyncedTimeSlider };
    AudioProcessorValueTreeState::ButtonAttachment mSyncButtonAttachment { processor.getValueTreeState(), ObliqueDelayV2AudioProcessor::paramSyncMode, mSyncModeButon};
    AudioProcessorValueTreeState::SliderAttachment mFrequencyAttachment { processor.getValueTreeState(), "freq", mFrequencySlider };
    AudioProcessorValueTreeState::ComboBoxAttachment mChoiceAttachment { processor.getValueTreeState(), "biqchoice", mFilterChoice};
};
