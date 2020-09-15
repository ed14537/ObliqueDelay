/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define FREQ_ID "freq"
#define FREQ_NAME "Frequency"
#define BIQCHOICE_ID "biqchoice"
#define BIQCHOICE_NAME "BiqChoice"

String ObliqueDelayV2AudioProcessor::paramMix ("Mix");
String ObliqueDelayV2AudioProcessor::paramBypass ("Balance");
String ObliqueDelayV2AudioProcessor::paramDelayTime ("Time");
String ObliqueDelayV2AudioProcessor::paramFeedback ("Feedback");
String ObliqueDelayV2AudioProcessor::paramSyncMode("timeSync");
String ObliqueDelayV2AudioProcessor::paramSyncedTime("syncedTime");
String ObliqueDelayV2AudioProcessor::paramOblique ("Oblique");
String ObliqueDelayV2AudioProcessor::paramConcrete ("Concrete");
String ObliqueDelayV2AudioProcessor::paramObliqueConcrete
 ("ObliqueConcrete");

//==============================================================================
ObliqueDelayV2AudioProcessor::ObliqueDelayV2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    parameters (*this, nullptr, "Delay", createParameterLayout()), m_delayChannel0(), m_delayChannel1()
{
    
    mMix = parameters.getRawParameterValue(paramMix);
    mBypass = parameters.getRawParameterValue(paramBypass);
    mDelayTime = parameters.getRawParameterValue(paramDelayTime);
    mFeedback = parameters.getRawParameterValue(paramFeedback);
    mSyncMode = parameters.getRawParameterValue(paramSyncMode);
    mTimeSynced = parameters.getRawParameterValue(paramSyncedTime);
    mFrequency = parameters.getRawParameterValue(FREQ_ID);
    mFilterChoice = parameters.getRawParameterValue(BIQCHOICE_ID);
}

ObliqueDelayV2AudioProcessor::~ObliqueDelayV2AudioProcessor()
{

}

//==============================================================================

AudioProcessorValueTreeState::ParameterLayout ObliqueDelayV2AudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    NormalisableRange<float> syncRange (0.082f,
    1.5f,
    [](auto rangeStart, auto rangeEnd, auto valueToRemap)  // maps real value to 0..1
    { return jmap (valueToRemap, rangeStart, rangeEnd); },
    [](auto rangeStart, auto rangeEnd, auto valueToRemap)  // maps 0..1 values to real world
    { return jmap (valueToRemap, rangeStart, rangeEnd, 0.0f, 1.0f); },
    [](auto rangeStart, auto rangeEnd, auto valueToRemap)  // maps real world to legal real world
    {
        if(valueToRemap >= 0.083f && valueToRemap <= 0.104f)
        {
            //1/32 T
            return jlimit(rangeStart, rangeEnd, 0.082f);
        } else if (valueToRemap > 0.104f && valueToRemap <= 0.146f)
        {
            // 1/32
            return jlimit(rangeStart, rangeEnd, 0.125f);
        } else if (valueToRemap > 0.146f && valueToRemap <= 0.1771f)
        {
            //1/16 T
            return jlimit(rangeStart, rangeEnd, 0.166f);
        } else if (valueToRemap > 0.1771f && valueToRemap <= 0.2188f)
        {
            // 1/32 D
            return jlimit(rangeStart, rangeEnd, 0.1875f);
        } else if (valueToRemap > 0.2188f && valueToRemap <= 0.2915f)
        {
            // 1/16
            return jlimit(rangeStart, rangeEnd, 0.25f);
        } else if (valueToRemap > 0.2915f && valueToRemap <= 0.354f)
        {
            // 1/8T
            return jlimit(rangeStart, rangeEnd, 0.32f);
        } else if (valueToRemap >= 0.355f && valueToRemap <= 0.4375f)
        {
            // 1/16 D
            return jlimit(rangeStart, rangeEnd, 0.375f);
        } else if (valueToRemap > 0.4375f && valueToRemap <= 0.5834f)
        {
            // 1/8
            return jlimit(rangeStart, rangeEnd, 0.5f);
        } else if (valueToRemap > 0.5834f && valueToRemap <= 0.7084f)
        {
            // 1/4T
            return jlimit(rangeStart, rangeEnd, 0.666f);
        } else if (valueToRemap > 0.7084f && valueToRemap <= 0.875f)
        {
            // 1/8 D
            return jlimit(rangeStart, rangeEnd, 0.75f);
        } else if (valueToRemap > 0.875f && valueToRemap <= 1.1665f)
        {
            // 1/4
            return jlimit(rangeStart, rangeEnd, 1.0f);
        } else if (valueToRemap > 1.1665f && valueToRemap <= 1.4165f)
        {
            // 1/2 T
            return jlimit(rangeStart, rangeEnd, 1.32f);
        } else {
            // 1/4 D
            return jlimit(rangeStart, rangeEnd, 1.5f);
        }
    });
    
    auto bypassParam = std::make_unique<AudioParameterFloat>(paramBypass, TRANS("Balance"), NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f);
    auto timeParam = std::make_unique<AudioParameterFloat>(paramDelayTime, TRANS("TIME"), NormalisableRange<float>(0.0f, 2000.0f, 1.0f), 100.0f);
    auto feedBackParam = std::make_unique<AudioParameterFloat>(paramFeedback, TRANS("Feedback"), NormalisableRange<float>(0.0f, 100.0f, 1.0f), 0.0f);
    auto mixParam = std::make_unique<AudioParameterFloat>(paramMix, TRANS("Mix"), NormalisableRange<float>(0.0f, 100.0f, 1.0f), 50.0f);
    auto obliqueParam = std::make_unique<AudioParameterFloat>
           (paramOblique, TRANS("Oblique"),
           NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f);
    auto concreteParam = std::make_unique<AudioParameterFloat>
           (paramConcrete, TRANS("Concrete"),
           NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f);
    auto obliqueConcreteParam =  std::make_unique<AudioParameterFloat>
           (paramObliqueConcrete, TRANS("Oblique Concrete"),
           NormalisableRange<float>(0.0f, 20.0f), 1.0f);
    auto timeSyncParam = std::make_unique<AudioParameterFloat>(paramSyncMode, TRANS("Time Sync"), NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f);
    auto timeParamSynced = std::make_unique<AudioParameterFloat>(paramSyncedTime, TRANS("Synced Time"), syncRange, 0.083f);
    auto freqParam = std::make_unique<AudioParameterFloat>(FREQ_ID, FREQ_NAME, NormalisableRange<float>(20.0f, 20000.0f, 25.0f, 0.5f, false), 200.0f);
    auto biquadChoiceParam = std::make_unique<AudioParameterFloat>(BIQCHOICE_ID, BIQCHOICE_NAME, NormalisableRange<float>(1, 7, 1), 1);
    
    params.push_back(std::move(bypassParam));
    params.push_back(std::move(timeParam));
    params.push_back(std::move(feedBackParam));
    params.push_back(std::move(mixParam));
    params.push_back(std::move(obliqueParam));
    params.push_back(std::move(concreteParam));
    params.push_back(std::move(obliqueConcreteParam));
    params.push_back(std::move(timeSyncParam));
    params.push_back(std::move(timeParamSynced));
    params.push_back(std::move(freqParam));
    params.push_back(std::move(biquadChoiceParam));
    params.push_back(std::move(freqParam));
    params.push_back(std::move(biquadChoiceParam));
    
    return { params.begin(), params.end() };
}


const String ObliqueDelayV2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ObliqueDelayV2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ObliqueDelayV2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ObliqueDelayV2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ObliqueDelayV2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ObliqueDelayV2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ObliqueDelayV2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void ObliqueDelayV2AudioProcessor::setCurrentProgram (int index)
{
}

const String ObliqueDelayV2AudioProcessor::getProgramName (int index)
{
    return {};
}

void ObliqueDelayV2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ObliqueDelayV2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    delayBufferSamples = (int)(2000 * (float)sampleRate) + 1;
    
    if (delayBufferSamples < 1) delayBufferSamples = 1;

    delayBufferChannels = getTotalNumInputChannels();
    delayBuffer.setSize (delayBufferChannels, delayBufferSamples);
    delayBuffer.clear();

    delayWritePosition = 0;
        
    m_delayChannel0.getFilter().prepareToPlay(sampleRate, samplesPerBlock);
    m_delayChannel1.getFilter().prepareToPlay(sampleRate, samplesPerBlock);
    m_delayChannel0.reset();
    m_delayChannel1.reset();
    
    /*for (int channel = 0; channel < kChannels; channel++)
    {
        filter[channel].prepareToPlay(sampleRate, samplesPerBlock);
    }*/
}

void ObliqueDelayV2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ObliqueDelayV2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void ObliqueDelayV2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    auto channel0 = buffer.getWritePointer(0);
    auto channel1 = buffer.getWritePointer(1);
    playHead = getPlayHead();
    
    if(*mSyncMode)
    {
        if(playHead != nullptr)
        {
            playHead->getCurrentPosition(currentPosition);
            float noteDuration = *mTimeSynced;
            float bps = currentPosition.bpm/60;
            float syncedTime = (noteDuration * 1000) / bps;
            m_delayChannel0.setDelay(syncedTime);
            m_delayChannel1.setDelay(syncedTime);
        } else {
            m_delayChannel0.setDelay(0);
            m_delayChannel1.setDelay(0);
        }

    } else
    {
        m_delayChannel0.setDelay(*mDelayTime);
        m_delayChannel1.setDelay(*mDelayTime);
    }
    
    m_delayChannel0.setFeedback(*mFeedback);
    m_delayChannel1.setFeedback(*mFeedback);
    
    m_delayChannel0.setMix(*mMix);
    m_delayChannel1.setMix(*mMix);
    
    m_delayChannel0.setBypass(*mBypass);
    m_delayChannel1.setBypass(*mBypass);
    
    m_delayChannel0.setFilterChoice((int)*mFilterChoice);
    m_delayChannel1.setFilterChoice((int)*mFilterChoice);
    
    m_delayChannel0.setFrequencyValue(*mFrequency);
    m_delayChannel1.setFrequencyValue(*mFrequency);


    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        // Process the first channel.
        channel0[i] = m_delayChannel0.processSample(channel0[i]);
        
        // Process the second channel. Just copy the first channel for mono output.
        if (getTotalNumInputChannels() == 1 && getTotalNumOutputChannels() == 2) { channel1[i] = channel0[i]; }
        else if (getTotalNumInputChannels() == 2 && getTotalNumOutputChannels() == 2) { channel1[i] = m_delayChannel1.processSample(channel1[i]); }
    }

    // Clear any additional output channels.
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i) { buffer.clear (i, 0, buffer.getNumSamples()); }
}

//==============================================================================
bool ObliqueDelayV2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorValueTreeState& ObliqueDelayV2AudioProcessor::getValueTreeState()
{
    return parameters;
}

AudioProcessorEditor* ObliqueDelayV2AudioProcessor::createEditor()
{
    return new ObliqueDelayV2AudioProcessorEditor (*this);
}

//==============================================================================
void ObliqueDelayV2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    MemoryOutputStream stream(destData, false);
    parameters.state.writeToStream (stream);
}

void ObliqueDelayV2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ValueTree tree = ValueTree::readFromData (data, sizeInBytes);
    if (tree.isValid()) {
        parameters.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ObliqueDelayV2AudioProcessor();
}
