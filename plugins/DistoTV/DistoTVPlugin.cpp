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
#include <lo/lo_osc_types.h>
#include "DistoTV-DSP.hpp"

static const float kAMP_DB = 8.656170245f; 
static const float kDC_ADD = 1e-30f; 	   
static const float kPI     = 3.141592654f;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistoTVPlugin::DistoTVPlugin()
    : Plugin(paramCount, 2, 1) //  program, states
{
    // set default values
    loadProgram(0);

    // reset
    deactivate();
}

// -----------------------------------------------------------------------
// Init

void DistoTVPlugin::initParameter(uint32_t index, Parameter& parameter)
{
    switch (index)
    {
    case paramWet:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Wet";
        parameter.symbol     = "wet";
        parameter.unit       = "%";
        parameter.ranges.def = 50.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramTVNoise:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "TVNoise";
        parameter.symbol     = "tvnoise";
        parameter.unit       = "%";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramBit:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Bit";
        parameter.symbol     = "bit";
        parameter.unit       = "%";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramDist:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Dist";
        parameter.symbol     = "dist";
        parameter.unit       = "%";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

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
	
    case paramCub:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Cubz";
        parameter.symbol     = "cubz";
        parameter.unit       = "%";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 25.0f; // 100000000000.0
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



// -----------------------------------------------------------------------
// Internal data

float DistoTVPlugin::getParameterValue(uint32_t index) const
{
    switch (index)
    {
    case paramWet:
        return fWet;
    case paramTVNoise:
        return fTVNoise;
    case paramBit:
        return fBit;
    case paramDist:
        return fDist;
    case paramLow:
        return fLow;
    case paramMid:
        return fMid;
    case paramHigh:
        return fHigh;
    case paramCub:
        return fCub;
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
    case paramWet:
        fWet   = value;
        break;
    case paramTVNoise:
        fTVNoise   = value;
        break;
    case paramBit:
        fBit   = (int)value;
	bit = fBit;
        break;
    case paramDist:
        fDist = value;
        break;
    case paramCub:
        fCub = pow(10,value);
        break;	
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
    }
}

void DistoTVPlugin::setState(const char* key, const char* value)
{
        //printf("\nthis is setState string\n%s", value);
        if (strcmp(key, "waveform") == 0) {
                char* tmp;
                int i = 0;
                char tmpbuf[4*AREAHEIGHT+1] = {0};
                snprintf(tmpbuf, 4*AREAHEIGHT+1, "%s", value);
                //printf("\nthe value of tmpbuf\n%s", tmpbuf);
                tmp = strtok(tmpbuf, " "); // take me word for word baby
                while ((tmp != NULL) && (i < AREAHEIGHT)) {
                        wave_y[i] = ((float) atoi(tmp))/AREAHEIGHT - 0.5; // take float values of the strings and put in wave_y
                        //printf("dsp wave_y[%d]=%.2f \n", i, wave_y[i]);
                        tmp = strtok(NULL, " ");
                        i++;
                }
        
       }
}

String DistoTVPlugin::getState(const char * key)const {
  if (strcmp(key, "waveform") == 0) {
    char tmpbuf[4*AREAHEIGHT+1] = {0};
    int i = 0;
    int value;
    char word[5];   
    while(i < AREAHEIGHT) {
     value = (int)(wave_y[i]*(AREAHEIGHT+0.5))+95;
     snprintf(word,5,"%03d ", value);
     strcat(tmpbuf,word);     
     i++; 
   }
   //printf("\nthis is getState string\n%s",tmpbuf);
   return String(tmpbuf);
   }
   
  return String("false");
}

void DistoTVPlugin::initProgramName(uint32_t index, String& programName)
{
  
  switch (index) {
        case 0:
            programName = "DefaultName";
            break;
        case 1:
            programName = "First";
            break;
    }
}

void DistoTVPlugin::initState(unsigned int index, String& key, String& defvalue)
{
    if (index == 0) key = "waveform";
        defvalue = "";
}

void DistoTVPlugin::loadProgram(uint32_t index)
{
  
  
    if (index == 0){

    // Default values
    fWet = 50.0f;
    fTVNoise = 0.0f;
    fBit = 0.0f;
    fDist = 0.0f;
    fLow = 0.0f;
    fMid = 0.0f;
    fHigh = 0.0f;
    fMaster = 0.0f;
    fCub = 0.0f;
    fLowMidFreq = 220.0f;
    fMidHighFreq = 2000.0f;

    // Internal stuff
    lowVol = midVol = highVol = outVol = 1.0f;
    freqLP = 200.0f;
    freqHP = 2000.0f;

    // reset filter values
    activate();

    }
    switch (index) {
        case 1:
            setParameterValue(paramWet, 30.0f);
            break;
    }
}

// -----------------------------------------------------------------------
// Process

void DistoTVPlugin::activate()
{
    
    int rndnum;
    for (int i = 0; i <= 100; i++){
        rndnum =  rand() % 100 + 1;
	rnd[i] = rndnum * 0.00000000000000000000000000001f;
    }
  
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
        sigDryL1 = sigL1 = in1[i];
        sigDryR2 = sigR2 = in2[i];

	//Count the graph samples
	graph++;
	if (graph == 190)
	  graph = 0;

	
	//amplitude
	
	sigL1 = tube(sigL1, 0.14*fDist);
	sigR2 = tube(sigR2, 0.14*fDist);
	
	
	// The HairCutter
	// 
	// signal is sterio and the clipping can be done on 4 places separetly
	// left+ and left- and right+ and right-
	//
	// cubicSampels
	
	if (sigL1 >= 0.5+wave_y[graph]){
	  sigL1 = 0.5+wave_y[graph];
	  if(cubicSampels)
	     sigL1 = sigL1 + (0.000000000000000000000001 * fCub); // need new knob
	}
	if (sigL1 <=-0.5-wave_y[graph]){
	  sigL1 = -0.5-wave_y[graph];
	  if(cubicSampels==false)
	     sigL1 = sigL1 + (0.000000000000000000000001 * fCub);
	}
	if (sigR2 >= 0.5+wave_y[graph]){
	  sigR2 = 0.5+wave_y[graph];
	  if(cubicSampels)
	     sigR2 = sigR2 + (0.000000000000000000000001 * fCub);
	}
	if (sigR2 <=-0.5-wave_y[graph]){
	  sigR2 = -0.5-wave_y[graph];
	  if(cubicSampels==false)
	     sigL1 = sigL1 + (0.000000000000000000000001 * fCub);
	}
	cubicSampels++;

	if (fBit > 0){
	  if (bit == 0){bit = fBit; graph++;}
	  bit--;
	  graph--;
	}
	
	
	//sigL1 = sigL1  /2/(fDist* 0.15);
	//sigR2 = sigR2  /2/(fDist* 0.15);
	
	
	//extra tv noise, need work
	sigL1 = sigL1 + rnd[graph];
	sigR2 = sigR2 + rnd[graph];
	
	
	
	
	// Dist knob final blend in
	sigL1 = sigDryL1 - (sigDryL1 * 0.01 *fDist) + (sigL1 * 0.01 * fDist);
	sigR2 = sigDryR2 - (sigDryR2 * 0.01 *fDist) + (sigL1 * 0.01 * fDist);
	
	// Filter
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
