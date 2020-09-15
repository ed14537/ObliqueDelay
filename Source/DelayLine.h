/*
  ==============================================================================

    DelayLine.h
    Created: 13 Sep 2020 11:16:28am
    Author:  Ellis Domenger-Boyce

  ==============================================================================
*/

#pragma once

#include "MyFilter.h"
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstdlib>

/**
 * \class
 */
class DelayLine
{
public:

    /**
     * Class constructor.
     *
     * \param[in]  int  Sample frequency
     * \param[in]  float  Delay time (msecs)
     * \param[in]  float  Feedback (%)
     * \param[in]  float  Mix (%)
     */
    DelayLine (const int fs = 44100, const float delay = 0, const float feedback = 0, const float mix = 0.5);

    /**
     * Class destructor.
     */
    ~DelayLine();

    /**
     * Resets the delay line by flushing the buffer and initializing the delay parameters.
     */
    void reset();

    /**
     * Calculates the delayed value of the input signal.
     *
     * \param[in]  float  Input data sample
     *
     * \return  float  Output amplitude of the delayed signal
     */
    float processSample (const float input);

    void setReadPos(); ///< Sets the buffer read position based on the delay and size of the buffer.
    void setDelay (float delay) { m_delay = delay; setReadPos(); }; ///< Sets the delay parameter and updates the buffer read position.
    void setFeedback (float feedback) { m_feedback = feedback/100; }; ///< Sets the feedback parameter (0-1).
    void setMix (float mix) { m_mix = mix/100; }; ///< Sets the mix parameter (0-1).
    void setBypass (bool bypass) { m_bypass = bypass; }; ///< Sets the bypass parameter (true = bypass).
    void setFrequencyValue (float freqValue) { m_freqValue = freqValue; };
    void setQValue (float qValue) { m_qValue = qValue; };
    void setFilterChoice (int filterChoice) { m_filterChoice = filterChoice; };
    float processFilterSample (float input);
    
    void setSampleRate(double sampleRate) { m_sampleRate = sampleRate; };
    
    void setSamplesPerBlock(int samplesPerBlock) { m_samplesPerBlock = samplesPerBlock; };
    
    MyFilter getFilter() { return m_filter; };

private:

    double m_sampleFreq; ///< Audio sample rate.
    float m_delay; ///< Delay time parameter (msecs).
    float m_feedback; ///< Feedback parameter (%).
    float m_mix; ///< Mix parameter (%).
    bool m_bypass; ///< Bypass parameter (true = bypass).

    int m_readPos; ///< Input buffer read position.
    int m_writePos; ///< Output buffer write position.

    int m_delaySamples; ///< Number of samples corresponding to m_delay.
    int m_maxDelaySamples; ///< Maximum number of delayed samples.
    float m_maxDelay; ///< Maximum delay time (currently set to 2 secs).
    float m_delayFraction; ///< Fractional delay time (msecs).
    float m_freqValue;
    float m_qValue;
    int m_filterChoice;
    double m_sampleRate;
    int m_samplesPerBlock;

    float* m_buffer; ///< Delayed signal buffer.
    
    MyFilter m_filter;
};
