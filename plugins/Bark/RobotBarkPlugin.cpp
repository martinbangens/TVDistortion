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
    : Plugin(8,1,0)
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
        case parameterWet:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Wet";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 0.0;
	     parameter.ranges.min   = 0.0;
	     parameter.ranges.max   = 100.0;
	     break;
	
        case parameterRed:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Red";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 0.0;
	     parameter.ranges.min   = 0.0;
	     parameter.ranges.max   = 100.0;
	     break;
	
        case parameterOrange:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Orange";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 0.0;
	     parameter.ranges.min   = 0.0;
	     parameter.ranges.max   = 100.0;
	     break;
        
	case parameterYellow:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Yellow";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 0.0;
	     parameter.ranges.min   = 0.0;
	     parameter.ranges.max   = 100.0;
	     break;
        
	case parameterGreen:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Green";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 0.0;
	     parameter.ranges.min   = 0.0;
	     parameter.ranges.max   = 100.0;
	     break;
	
        case parameterBlue:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Blue";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 0.0;
	     parameter.ranges.min   = 0.0;
	     parameter.ranges.max   = 100.0;
	     break;
	
        case parameterIndigo:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Indigo";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 0.0;
	     parameter.ranges.min   = 0.0;
	     parameter.ranges.max   = 100.0;
	     break;
	
        case parameterViolet:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Violet";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 0.0;
	     parameter.ranges.min   = 0.0;
	     parameter.ranges.max   = 100.0;
	     break;
	
	
    }
}

float Rainbow::getParameterValue(uint32_t index) const
{
    switch (index)
    {
        case parameterWet:
	    return fWet;

	case parameterRed:
	    return fRed;
	    
	case parameterOrange:
            return fOrange;
	
	case parameterYellow:
	    return fYellow;

	case parameterGreen:
	    return fGreen;
	
	case parameterBlue:
	    return fBlue;

	case parameterIndigo:
	    return fIndigo;

	case parameterViolet:
	    return fViolet;
	
	default:
	    return 0.0f;
    }
}

void Rainbow::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
        case parameterWet:
	    fWet = value;
	    break;
	
	case parameterRed:
	    fRed = value;
	    break;
	
	case parameterOrange:
	    fOrange = value;
	    break;
	
	case parameterYellow:
	    fYellow = value;
	    break;
	
	case parameterGreen:
	    fGreen = value;
	    break;
	
	case parameterBlue:
	    fBlue = value;
	    break;
	
	case parameterIndigo:
	    fIndigo = value;
	    break;
        
        case parameterViolet:
	    fViolet = value;
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
            fWet       = 0.0;
            fRed       = 0.0;
	    fOrange    = 0.0;
	    fYellow    = 0.0;
	    fBlue      = 0.0;
	    fIndigo    = 0.0;
	    fViolet    = 0.0;
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
    const float* input1_left   = inputs[0];
    const float* input2_right  = inputs[1];
    float*       output1_left  = outputs[0];
    float*       output2_right = outputs[1];

    for (uint32_t i = 0; i < frames; ++i)
    {
    




    output1_left[i]  = input1_left[i];
    output2_right[i] = input2_right[i];
    }
}


Plugin* createPlugin()
{
    return new Rainbow();
}


END_NAMESPACE_DISTRHO
