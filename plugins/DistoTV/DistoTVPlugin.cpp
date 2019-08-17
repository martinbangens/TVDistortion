/*
 * DistoTV Plugin, based on 3BandEQ by Filipe Coelho and
 * Michael Gruhn
 * Copyright (C) 2019 Martin Bångens <marbangens@gmail.com>
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
#include "DistoTVPlugin.hpp"

#include <cmath>

static const float kAMP_DB = 8.656170245f; // natural log of decibel?
static const float kDC_ADD = 1e-30f; 	   // 0.000000000000000000000000000001
static const float kPI     = 3.141592654f;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistoTVPlugin::DistoTVPlugin()
    : Plugin(paramCount, 1, 0) // 1 program, 0 states
{
    // set default values
    //loadProgram(0);

    // reset
    deactivate();
}

// -----------------------------------------------------------------------
// Init

void DistoTVPlugin::initParameter(uint32_t index, Parameter& parameter)
{
    switch (index)
    {
    case paramLow:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Low";
        parameter.symbol     = "low";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -24.0f;
        parameter.ranges.max = 24.0f;
        break;

    case paramMid:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Mid";
        parameter.symbol     = "mid";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -24.0f;
        parameter.ranges.max = 24.0f;
        break;

    case paramHigh:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "High";
        parameter.symbol     = "high";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -24.0f;
        parameter.ranges.max = 24.0f;
        break;

    case paramMaster:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Master";
        parameter.symbol     = "master";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -24.0f;
        parameter.ranges.max = 24.0f;
        break;
    }
}

/*void DistoTVPlugin::initProgramName(uint32_t index, String& programName)
{
    if (index != 0)
        return;

    programName = "Default";
}
*/
// -----------------------------------------------------------------------
// Internal data

float DistoTVPlugin::getParameterValue(uint32_t index) const
{
    switch (index)
    {
    case paramLow:
        return fLow;
    case paramMid:
        return fMid;
    case paramHigh:
        return fHigh;
    case paramMaster:
        return fMaster;
    default:
        return 0.0f;
    }
}

void DistoTVPlugin::setParameterValue(uint32_t index, float value)
{
    if (getSampleRate() <= 0.0)
        return;

    switch (index)
    {
    case paramLow:
        fLow   = value;
        lowVol = std::exp( (fLow/48.0f) * 48.0f / kAMP_DB);
        break;
    case paramMid:
        fMid   = value;
        midVol = std::exp( (fMid/48.0f) * 48.0f / kAMP_DB);
        break;
    case paramHigh:
        fHigh   = value;
        highVol = std::exp( (fHigh/48.0f) * 48.0f / kAMP_DB);
        break;
    case paramMaster:
        fMaster = value;
        outVol  = std::exp( (fMaster/48.0f) * 48.0f / kAMP_DB);
        break;
    case paramWet:
        fDist = value;
        break;
    }
}

void DistoTVPlugin::setState(const char* key, const char* value)
{
	if (strcmp(key, "waveform") == 0) {
		char* tmp;
		int i = 0;
		char tmpbuf[4*AREAHEIGHT+1] = {0};
		snprintf(tmpbuf, 4*AREAHEIGHT, "%s", value);
		tmp = strtok(tmpbuf, " ");
		while ((tmp != NULL) && (i < AREAHEIGHT)) {
			wave_y[i] = ((float) atoi(tmp))/AREAHEIGHT - 0.5;
			i++;
			printf("dsp wave_y[%d]=%.2f \n", i, wave_y[i]);
			tmp = strtok(NULL, " ");
		}
	
	}
}

void DistoTVPlugin::initState(unsigned int index, String& key, String& defvalue)
{
	if (index == 0) key = "waveform";
	defvalue = "";
}

/*void DistoTVPlugin::loadProgram(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    fLow = 0.0f;
    fMid = 0.0f;
    fHigh = 0.0f;
    fMaster = 0.0f;
    fDist = 0.0f;
    fLowMidFreq = 220.0f;
    fMidHighFreq = 2000.0f;

    // Internal stuff
    lowVol = midVol = highVol = outVol = 1.0f;
    freqLP = 200.0f;
    freqHP = 2000.0f;

    // reset filter values
    activate();
}
*/
// -----------------------------------------------------------------------
// Process

void DistoTVPlugin::activate()
{
    const float sr = (float)getSampleRate();

    xLP  = std::exp(-2.0f * kPI * freqLP / sr);
    
#ifdef DISTRHO_OS_WINDOWS
    // don't ask me why, but this fixes a crash/exception below on windows...
    printf("%f\n", -xLP);
#endif

    a0LP = 1.0f - xLP;
    b1LP = -xLP;

    xHP  = std::exp(-2.0f * kPI * freqHP / sr);
    a0HP = 1.0f - xHP;
    b1HP = -xHP;
    
}

void DistoTVPlugin::deactivate()
{
    out1LP = out2LP = out1HP = out2HP = 0.0f;
    tmp1LP = tmp2LP = tmp1HP = tmp2HP = 0.0f;
}

void DistoTVPlugin::run(const float** inputs, float** outputs, uint32_t frames)
{
    const float* in1  = inputs[0];
    const float* in2  = inputs[1];
    float*       out1 = outputs[0];
    float*       out2 = outputs[1];
    

    /*
      I borrowed code from 3BandEQ used it as a starting point
      */
    for (uint32_t i=0; i < frames; ++i)
    {
        sigL1 = in1[i];
        sigR2 = in2[i];
	
	
	
	// signal is sterio and the clipping can be done on 4 places separetly
	// left+ and left- and right+ and right-
	
	//gonna start make Left +
	//if (sigL1 >= 0.0002 *  
	
	
        tmp1LP = a0LP * sigL1 - b1LP * tmp1LP + kDC_ADD;
        tmp2LP = a0LP * sigR2 - b1LP * tmp2LP + kDC_ADD;
        out1LP = tmp1LP - kDC_ADD;
        out2LP = tmp2LP - kDC_ADD;

        tmp1HP = a0HP * sigL1 - b1HP * tmp1HP + kDC_ADD;
        tmp2HP = a0HP * sigR2 - b1HP * tmp2HP + kDC_ADD;
        out1HP = sigL1 - tmp1HP - kDC_ADD;
        out2HP = sigR2 - tmp2HP - kDC_ADD;

        sigL1 = (out1LP*lowVol + (sigL1 - out1LP - out1HP)*midVol + out1HP*highVol) * outVol;
        sigR2 = (out2LP*lowVol + (sigR2 - out2LP - out2HP)*midVol + out2HP*highVol) * outVol;
        
        out1[i] = sigL1;
        out2[i] = sigR2;
    }
}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new DistoTVPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
