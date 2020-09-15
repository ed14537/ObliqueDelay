/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "DelayLine.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class ObliqueDelayV2AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ObliqueDelayV2AudioProcessor();
    ~ObliqueDelayV2AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    AudioProcessorValueTreeState& getValueTreeState();

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioSampleBuffer delayBuffer;
    int delayBufferSamples;
    int delayBufferChannels;
    int delayWritePosition;
    
    static String paramBypass;
    static String paramDelayTime;
    static String paramFeedback;
    static String paramMix;
    static String paramSyncMode;
    static String paramSyncedTime;
    static String paramOblique;
    static String paramConcrete;
    static String paramObliqueConcrete;

    //======================================
    
    int biquadChoice;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObliqueDelayV2AudioProcessor)
    
    AudioProcessorValueTreeState parameters;
    
    std::atomic<float>* mBypass = nullptr;
    std::atomic<float>* mDelayTime = nullptr;
    std::atomic<float>* mFeedback = nullptr;
    std::atomic<float>* mMix = nullptr;
    std::atomic<float>* mTimeSynced = nullptr;
    std::atomic<float>* mSyncMode = nullptr;
    std::atomic<float>* mFrequency = nullptr;
    std::atomic<float>* mFilterChoice = nullptr;

    AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo currentPosition;
    
    DelayLine m_delayChannel0; ///<
    DelayLine m_delayChannel1;
    
    /*static const int kChannels = 2;
    MyFilter filter[kChannels];*/

};
