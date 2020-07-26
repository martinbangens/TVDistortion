/* Copyright (C) 2020 Martin Bångens <marbangens@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * For a full copy of the license see the LICENSE file.
 */

#include "DistrhoPluginRainbow.hpp"

//#include <cmath>
//#include <algorithm>

START_NAMESPACE_DISTRHO


Rainbow::Rainbow()
    : Plugin(2,1,0)
{
    // load in deafualt values
    //
    loadProgram(0);

    // reset
    deactivate();

}

void Rainbow::initParameter(uint32_t index, Parameter& parameter)
{
    switch (index)
    {
        case parameterGain:
	    parameter.hints        = kParameterIsAutomable;
	    parameter.name         = "Gain";
	    parameter.symbol       = "";
	    parameter.unit         = "dB";
	    parameter.ranges.def   = 0.0;
	    parameter.ranges.min   = -48.0;
	    parameter.ranges.max   = 48.0;
	    break;
	
	case parameterTone:
	    parameter.hints        = kParameterIsAutomable;
	    parameter.name         = "Tone";
	    parameter.symbol       = "";
	    parameter.unit         = "pct";
	    parameter.ranges.def   = 0.0;
	    parameter.ranges.min   = -100.0;
	    parameter.ranges.max   = 100.0;
	    break;
    }
}

float Rainbow::getParameterValue(uint32_t index) const
{
    switch (index)
    {
        case parameterGain:
	    return fGain;
	    
	case parameterTone:
            return fTone;
	    
	default:
	    return 0.0f;
    }
}

void Rainbow::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
        case parameterGain:
	    fGain = value;
	    break;
	
	case parameterTone:
	    fTone = value;
	    break;
    }

}

void Rainbow::initProgramName(uint32_t index, String& programName)
{
    switch (index)
    {
        case 0:
	    programName = "Default";
	    break;
    }
}

void Rainbow::loadProgram(uint32_t index)
{
    switch (index)
    {
        case 0:
            fGain = 0.0;
	    fTone = 0.0;
    }
}

void Rainbow::activate()
{
    // Drink a red bull
}

void Rainbow::deactivate()
{
    // Drink Milk
}

void Rainbow::run(const float** inputs, float** outputs, uint32_t frames)
{
    const float* input1_left   = inputs[0]; // clear name for jack use
    const float* input2_right  = inputs[1];
    float*       output1_left  = outputs[0];
    float*       output2_right = outputs[1];

    for (uint32_t i = 0; i < frames; ++i)
    {
    
    //float n;
    
    // program for a minumum of 16 frames

    //float wet = tanh(n*sin(input1_left[i]))




    output1_left[i]  = input1_left[i];
    output2_right[i] = input2_right[i];
    }
}


Plugin* createPlugin()
{
    return new Rainbow();
}


END_NAMESPACE_DISTRHO
