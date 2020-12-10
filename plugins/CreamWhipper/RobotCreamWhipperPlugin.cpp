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

#include "RobotCreamWhipperPlugin.hpp"

//#include <cmath>
//#include <algorithm>

START_NAMESPACE_DISTRHO


CreamWhipper::CreamWhipper()
    : Plugin(2,1,0)
{
    // load in deafualt values
    //
    // loadProgram(0);

    // reset
    // deactivate();

}

void CreamWhipper::initParameter(uint32_t index, Parameter& parameter)
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
	
        case parameterThreshold:
	     parameter.hints        = kParameterIsAutomable;
	     parameter.name         = "Threshold";
	     parameter.symbol       = "";
	     parameter.unit         = "";
	     parameter.ranges.def   = 1.0;
	     parameter.ranges.min   = 0.00000001;
	     parameter.ranges.max   = 1.0;
	     break;
	
    }
}

float CreamWhipper::getParameterValue(uint32_t index) const
{
    switch (index)
    {
        case parameterWet:
	    return fWet;

	case parameterThreshold:
	    return fThreshold;
	    
	default:
	    return 0.0f;
    }
}

void CreamWhipper::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
        case parameterWet:
	    fWet = value;
	    break;
	
	case parameterThreshold:
	    fThreshold = value;
	    break;
    }

}

void CreamWhipper::initProgramName(uint32_t index, String& programName)
{
    switch (index)
    {
        case 0:
	    programName = "Default";
	    break;
    }
}

void CreamWhipper::loadProgram(uint32_t index)
{
    switch (index)
    {
        case 0:
            fWet       = 0.f;
            fThreshold = 0.f;
    }
}

void CreamWhipper::activate()
{
    // Drink a red bull
}

void CreamWhipper::deactivate()
{
    // Drink Milk
}
float CreamWhipper::saturateA(float x, float t)
{
    if(fabs(x)<t) return x;
    else
    {
        if(x > 0.f) return t + (1.f-t)*tanh((x-t)/(1-t));
	else return -(t + (1.f-t)*tanh((-x-t)/(1-t)));
	// https://www.musicdsp.org/en/latest/Other/120-saturation.html
    }
}

float CreamWhipper::sigmoidA(float x)
{
    if(fabs(x)<1) return x*(1.5f - 0.5f*x*x);
    else return x > 0.f ? 1.f : -1.f;
}

float CreamWhipper::saturateB(float x, float t)
{
    if(abs(x)<t) return x;
    else
    {
        if(x > 0.f) return t + (1.f-t)*sigmoidA((x-t)/((1-t)*1.5f));
	else return -(t + (1.f-t)*sigmoidA((-x-t)/((1-t)*1.5f)));
    }
}

float CreamWhipper::sigmoidB(float x)
{
    if(fabs(x)<1) return 1/(1+exp(-x));   // the original sigmoid funtion
    else return x > 0.f ? 1.f : -1.f;      
}

float CreamWhipper::saturateC(float x, float t)
{
    if(abs(x)<t) return x;
    else
    {
        if(x > 0.f) return t + (1.f-t)*sigmoidB((x-t)/((1-t)*1.5f));
	else return -(t + (1.f-t)*sigmoidB((-x-t)/((1-t)*1.5f)));
    }
}

float CreamWhipper::waveshaper1(float x, float a)
{
    if (x < a) return x;
    if (x > a) return a + (x-a)/(1.f+pow(((x-a)/(1.f-a)),3.14f));
    if (x > 1.f) return (a+1.f)/2.f;
    return x;
}

void CreamWhipper::run(const float** inputs, float** outputs, uint32_t frames)
{
    //const float* input1_left   = inputs[0];
    //const float* input2_right  = inputs[1];
    //float*       output1_left  = outputs[0];
    //float*       output2_right = outputs[1];
    float sig0, sig1;

    for (uint32_t i = 0; i < frames; ++i)
    {
    sig0 = inputs[0][i];
    sig1 = inputs[1][i];

    sig0 = saturateA(sig0, 0.00000000001);
    sig1 = saturateA(sig1, 0.00000000001);

    sig0 = saturateB(sig0, 0.00000000001);
    sig1 = saturateB(sig1, 0.00000000001);

    sig0 = saturateC(sig0, 0.00000000000000000000000000001);
    sig1 = saturateC(sig1, 0.00000000000000000000000000001);

    sig0 = saturateA(sig0, 0.00000000000000000000001);
    sig1 = saturateA(sig1, 0.00000000000000000000001);

    sig0 = saturateB(sig0, 0.000000000000000000000000001);
    sig1 = saturateB(sig1, 0.000000000000000000000000001);

    sig0 = saturateC(sig0, 0.00000000000000000000000000001);
    sig1 = saturateC(sig1, 0.00000000000000000000000000001);

    sig0 = waveshaper1(sig0, 0.000000001) ;
    sig1 = waveshaper1(sig1, 0.000000001) ;
    
    if(sig0 < -sigmoidB(sig0)){ sig0 = -sigmoidB(sig0); } if(sig0 > sigmoidB(sig0)){ sig0 = sigmoidB(sig0); }
    if(sig1 < -sigmoidB(sig1)){ sig1 = -sigmoidB(sig1); } if(sig1 > sigmoidB(sig1)){ sig1 = sigmoidB(sig1); }


    if(sig0 < -1.){ sig0 = -1.; } if(sig0 > 1.){ sig0 = 1.; }
    if(sig1 < -1.){ sig1 = -1.; } if(sig1 > 1.){ sig1 = 1.; }
	    
    outputs[0][i]= sig0;
    outputs[1][i]= sig1;

    }
}


Plugin* createPlugin()
{
    return new CreamWhipper();
}


END_NAMESPACE_DISTRHO
