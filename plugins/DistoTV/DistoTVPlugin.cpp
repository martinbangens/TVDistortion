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

static const float kCUBS   = 1e-14f;
static const float kAMP_DB = 8.656170245f; 
static const float kDC_ADD = 1e-30f; 	   
static const float kPI     = 3.141592654f;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistoTVPlugin::DistoTVPlugin()
    : Plugin(paramCount, 1, 1) //  program, states
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
        parameter.unit       = "W";
        parameter.ranges.def = 50000.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100000.0f;
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
        parameter.unit       = "cp";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramTilt:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Tilt";
        parameter.symbol     = "tilt";
        parameter.unit       = "%";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 189.0f;
        break;

	
    case paramPre:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "PreAMP";
        parameter.symbol     = "pre";
        parameter.unit       = "p";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -14.0f;
        parameter.ranges.max = 14.0f;
        break;

    case paramMaster:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Master";
        parameter.symbol     = "master";
        parameter.unit       = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -48.0f;
        parameter.ranges.max = 6.0f;
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
    case paramTilt:
        return fTilt;
    case paramPre:
        return fPre;
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
        fCub = value;
        break;
    case paramTilt:
        fTilt = 190 - (int)value;
        break;
    case paramPre:
        fPre = value;
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
                tmp = strtok(tmpbuf, " ");
                while ((tmp != NULL) && (i < AREAHEIGHT)) {
                        wave_y[i] = ((float) atoi(tmp))/AREAHEIGHT - 0.5; // take float values of the strings and put in wave_y
                        
                        //printf("wave_y[%d]=%.2f \n", i, wave_y[i]);
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
    fWet = 50000.0f;
    fTVNoise = 0.0f;
    fBit = 0.0f;
    fDist = 0.0f;
    fLow = 0.0f;
    fMid = 0.0f;
    fHigh = 0.0f;
    fMaster = 0.0f;
    fCub = 0.0f;
    fTilt = 0.0f;
    fPre = 0.0f;

    // Internal stuff
    lowVol = midVol = highVol = outVol = 1.0f;
    freqLP = 200.0f;
    freqHP = 2000.0f;

    // reset filter values
    activate();

    }

}

// -----------------------------------------------------------------------
// Process

void DistoTVPlugin::activate()
{
    
    int rndnum;
    for (int i = 0; i <= 100; i++){
        rndnum =  rand() % 100 + 1;
    	rnd[i] = rndnum * 0.0000000000000000000000000000001f;
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
    //printf("\nhad_Inf=%d\n""had_NuN=%d\n",had_Inf,had_NuN);
}
float DistoTVPlugin::tube(float sig, float gain, float pregain)
{
  float endgain = gain+(pregain*3);
  
  if (endgain < 0) { endgain = 0; }
  
  sig = sig * (2*endgain); 
  
  if (sig < 0.00000000001f and sig > 0.0000000000000000000000000001f){
   sig = sin(sig);
  }
  
  if (sig > -0.00000000001f and sig < -0.0000000000000000000000000001f){
   sig = sin(sig);
  }
  
  sig = sig + sin(0.000000000000000000000000001f);
  
  return sig;
}

float DistoTVPlugin::tvnoise(float sig, float knob, float NoiseSample)
{ // need work
  sig = sig +(knob*0.01*NoiseSample);
   
  sig = sig +(knob*0.01*sin(sig));
  sig = sig +(knob*0.01*sin(0.1*sig));
  sig = sig +(knob*0.01*sin(0.01*sig));
  sig = sig +(knob*0.01*sin(0.001*sig));
  
  return sig;
}

void DistoTVPlugin::run(const float** inputs, float** outputs, uint32_t frames)
{
    const float* in1  = inputs[0];
    const float* in2  = inputs[1];
    float*       out1 = outputs[0];
    float*       out2 = outputs[1];
    
    
    for (uint32_t i=0; i < frames; ++i)
    {
        sigDryL1 = sigL1 = in1[i];
        sigDryR2 = sigR2 = in2[i];
        
        //graph wheel
	//
	//scaling is done only posetive frome one point and up, later mirrored to negative
	
        if (graph == 190) {graph = 0; /*memcpy(wave_y_DSP,  wave_y, 4*(AREAHEIGHT+1));*/}
        graph++;
	wave_y_DSP[graph] = sin(wave_y[graph]/2 + 0.25);// scale here now better then memcpy
        // need a funktion for Interpolation methods to wave_y_DSP, right now its a sine.
	
	// noise wheel
	if(NoiseSeq == 5){NoiseSeq = 0;}
	NoiseSeq++;
	
	
        //amplitude
        sigL1 = tube(sigL1,0.14 * fDist, fPre);
        sigR2 = tube(sigR2, 0.14 * fDist, fPre);
        
	softclipL = (2.f/ kPI) * atan(sigL1);
	softclipR = (2.f/ kPI) * atan(sigR2);
        

	// experamental clipping
	
	//sigL1 = sin(tan(sigL1));
	//sigR2 = sin(tan(sigR2));
	
	//sigL1 = sin(sigL1*sigL1*sigL1);
	//sigR2 = sin(sigR2*sigR2*sigR2);
	
	cubclipL = sigL1;
	cubclipR = sigR2;
	
	  if( cubclipL > 1){ cubclipL = 1; }
	  if( cubclipL < -1){ cubclipL = -1; }
	
	  if(cubclipR > 1){ cubclipR = 1; }
	  if(cubclipR < -1){ cubclipR = -1;}	
	
	cubclipL = (2.f/ kPI) * (1.5 * cubclipL - 0.5 * cubclipL * cubclipL * cubclipL);
	cubclipR = (2.f/ kPI) * (1.5 * cubclipR - 0.5 * cubclipR * cubclipR * cubclipR);

	
	//Polarity switch resets the graph. Work for natural sounds 
/*	    
	if( sigL1 < 0){
	   PolarityL = 0;
	   if (PrePolarityL==1) {graph=0;}
	   }
	    
	if( sigL1 > 0){
	   PolarityL = 1;
	   if (PrePolarityL==0) {graph=0;}
	   }
	      
	    
         if (sigR2 < 0){
	    PolarityR = 0;
	    if (PrePolarityR==1) {graph=0;}
	    }
	    
	 if (sigR2 > 0){
	    PolarityR = 1;
	    if (PrePolarityR==0) {graph=0;}
	    }
        
        PrePolarityL = PolarityL;
	PrePolarityR = PolarityR;
*/	
 	
        // Hard clipping from graph
        // 
        // signal is sterio and the clipping can be done on 4 places separetly
        // left+ and left- and right+ and right-
        //
       


       

        if (sigL1 >= 0.5+wave_y_DSP[graph]){
          sigL1 =  0.5+wave_y_DSP[graph];
	}
	if (sigL1 <= -0.5-wave_y_DSP[graph]){
	  sigL1 = -0.5-wave_y_DSP[graph];
	}
	if (sigR2 >= 0.5+wave_y_DSP[graph]){
	  sigR2 = 0.5+wave_y_DSP[graph];
	}
	if (sigR2 <= -0.5-wave_y_DSP[graph]){
	  sigR2 = -0.5-wave_y_DSP[graph];
	}
        

	
	//bit
	// this was supposed to be bit dist but it became graph length manipulator
	if (fBit > 0){
	  if (bit == 0){
	    bit = fBit;
	    if (fTilt > 0){bit = bit + graph;}
	      if (graph<fTilt){bit= bit -graph;}
	    graph++;
	  }
	  bit--;
	  graph--;
	}
	
	sigL1 = sigL1 + tvnoise(sigL1,fTVNoise,NoiseSample[NoiseSeq]);
	sigR2 = sigR2 + tvnoise(sigR2,fTVNoise,NoiseSample[NoiseSeq]);
	
	
	sigL1 = sigDryL1 - (sigDryL1 * 0.01 *fDist)  + (sigL1 * 0.01 * fDist) + (softclipL * 0.01 * fTVNoise) + (cubclipL * 0.01 * fCub);
	sigR2 = sigDryR2 - (sigDryR2 * 0.01 *fDist)  + (sigR2 * 0.01 * fDist) + (softclipR * 0.01 * fTVNoise) + (cubclipR * 0.01 * fCub);

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
        
	sigDryL1 = sigDryL1 * outVol;
	sigDryR2 = sigDryR2 * outVol;
	
        // Wet knob final blend in
        outFinalL = (sigL1*0.00001*fWet) + sigDryL1 - (sigDryL1*0.00001*fWet);
        outFinalR = (sigR2*0.00001*fWet) + sigDryR2 - (sigDryR2*0.00001*fWet);
        
	
	//extra tv noise, need work
	// need work
	// rms
	sigL1 = sigL1 + rnd[graph];
	sigR2 = sigR2 + rnd[graph];

	// Limit
	if(outFinalL < -1.){ outFinalL = -1.; } if(outFinalL > 1.){ outFinalL = 1.; }
	if(outFinalR < -1.){ outFinalR = -1.; } if(outFinalR > 1.){ outFinalR = 1.; }
	
	
	
	//out1[i] = CheckForBadEggs(sigL1);
	//out2[i] = CheckForBadEggs(sigR2);
	out1[i] = outFinalL;
	out2[i] = outFinalR;
    }
}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new DistoTVPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
