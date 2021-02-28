/* Copyright (C) 2019 Martin Bångens <marbangens@gmail.com>
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
#include "RobotTVDistortionPlugin.hpp"


#include <cmath>
#include <lo/lo_osc_types.h>


static const float kAMP_DB = 8.656170245f; 
static const float kDC_ADD = 1e-30f; 	   
static const float kPI     = 3.141592654f;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistoTVPlugin::DistoTVPlugin()
    : Plugin(12, 1, 1) //  program, states
{
    // set default values
    loadProgram(0);

    // reset
    deactivate();
    
    // This is not pretty, but works for now... the values have to be the same in
    // string and in run() dsp-array. they cant start out of sync...
    //
    
    setState("waveform", "151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 151 ");
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

    case paramDist:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Dist";
        parameter.symbol     = "dist";
        parameter.unit       = "%";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramPre:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "PreAMP";
        parameter.symbol     = "pre";
        parameter.unit       = "p";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -14.0f;
        parameter.ranges.max = 48.0f;
        break;

    case paramAmpType:
        parameter.hints      = kParameterIsAutomable | kParameterIsInteger;
        parameter.name       = "AmpType";
        parameter.symbol     = "float";
        parameter.unit       = "f";
        parameter.ranges.def = 1.0f;
        parameter.ranges.min = 1.0f;
        parameter.ranges.max = 3.0f;
        break;
    
    case paramInterpolation:
        parameter.hints      = kParameterIsAutomable | kParameterIsInteger;
        parameter.name       = "Interpolation";
        parameter.symbol     = "float";
        parameter.unit       = "f";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 4.0f;
        break;
    
    case paramScale:
        parameter.hints      = kParameterIsAutomable | kParameterIsInteger;
        parameter.name       = "Scale";
        parameter.symbol     = "float";
        parameter.unit       = "f";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 9.0f;
        break;
    
    case paramCrossres:
        parameter.hints      = kParameterIsAutomable | kParameterIsBoolean;
        parameter.name       = "Crossres";
        parameter.symbol     = "bool";
        parameter.unit       = "1/0";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1.0f;
        break;
        
    case paramMouseSM:
        parameter.hints      = kParameterIsAutomable | kParameterIsBoolean;
        parameter.name       = "MouseSM";
        parameter.symbol     = "bool";
        parameter.unit       = "1/0";
        parameter.ranges.def = 1.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 1.0f;
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
    case paramDist:
        return fDist;
    case paramPre:
        return fPre;
    case paramAmpType:
        return fAmpType;
    case paramInterpolation:
        return fInterpolation;
    case paramScale:
        return fScale;
    case paramCrossres:
        return fCrossres;
    case paramMouseSM:
        return fMouseSM;
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
    case paramWet:
        fWet   = value;
        break;
    case paramDist:
        fDist = value;
        break;
    case paramPre:
        fPre = value;
        break;
    case paramAmpType:
        fAmpType = value;
        break;
    case paramInterpolation:
        fInterpolation = value;
	Ipsc = 0;
        break;
    case paramScale:
        fScale = value;
        fScaleDSP =  0.50 - (fScale*0.05);
        break;
    case paramCrossres:
        fCrossres = value;
        break;
    case paramMouseSM:
        fMouseSM = value;
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
       char tmpbuf[4*AREALENGTH+1] = {0};
       snprintf(tmpbuf, 4*AREALENGTH+1, "%s", value);
       //printf("\nthe value of tmpbuf\n%s", tmpbuf);
       tmp = strtok(tmpbuf, " ");
       while ((tmp != NULL) && (i < AREALENGTH)) {
               DSP_wave_y_Pixels[i] = atoi(tmp); // take string values put in DSP_wave_y_Pixels (host restore state of saved wave)
                        
               //printf("DSP_wave_y_Pixels[%d]=%d \n", i, DSP_wave_y_Pixels[i]);
               tmp = strtok(NULL, " ");
               i++;
               }
        
       }
}

String DistoTVPlugin::getState(const char * key)const {
   if (strcmp(key, "waveform") == 0) {
       char tmpbuf[4*AREALENGTH+1] = {0};
       int i = 0;
       int value;
       char word[7];
       tmpbuf[0] = ' ';
       while(i < AREALENGTH) {
             value = DSP_wave_y_Pixels[i];
             snprintf(word,7,"%03d ", value);
             strcat(tmpbuf,word);     
             i++; 
       }
   
   //printf("\nThis is getstate() stored string:\n%s\n",tmpbuf);
   
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
    fWet = 1.5f;
    fDist = 0.0f;
    fPre = 0.0f;
    fAmpType = 1.0f;
    fInterpolation = 1.0f;
    fScale = 0.0f;
    fCrossres = 0.0f;
    fMouseSM = 1.0f;
    fLow = 0.0f;
    fMid = 0.0f;
    fHigh = 0.0f;
    fMaster = 0.0f;

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
    for (int i = 0; i <= 190; i++){
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
    printf("\nhad_Inf=%d\n""had_NuN=%d\n",had_Inf,had_NuN);
}
float DistoTVPlugin::tube(float sig)
{
    
    // Inspiration
    // 
    // https://www.researchgate.net/publication/224642046_Wave_Digital_Simulation_of_a_Vacuum-Tube_Amplifier
    // 
    float amp = std::exp(fPre/8.656170245);
    float tubesig = std::tan(sig);
    
    
    return (amp * tubesig) + sig ;
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
	//this needs to be tested visually and analysed
	
	if (Ipsc == 0)graph++;
        if (graph == 1000) {graph = 0;}
        
	wave_y_DSP = ((((AREAHEIGHT-DSP_wave_y_Pixels[graph])/150)-1)*fScaleDSP)+0.5;        // scale here for now
	if (graph == 999) wave_y_DSPnext = ((((AREAHEIGHT-DSP_wave_y_Pixels[0])/150)-1)*fScaleDSP)+0.5;
	else 
	wave_y_DSPnext = ((((AREAHEIGHT-DSP_wave_y_Pixels[graph+1])/150)-1)*fScaleDSP)+0.5;       



	// noise wheel (gonna be removed or improved)
	NoiseSeq++; if(NoiseSeq == 5){NoiseSeq = 0;}
	
	// rms noise wheel
	rms++; if(rms == 190){rms = 0;}	
	
        //amplitude (simulate a real tube later)
        sigL1 = tube(sigL1);
        sigR2 = tube(sigR2);
        
	//soft distortion
	//softclipL = (2.f/ kPI) * atan(sigL1);
	//softclipR = (2.f/ kPI) * atan(sigR2);
        
    	
	// experamental clipping
	
	//sigL1 = sin(tan(sigL1));
	//sigR2 = sin(tan(sigR2));
	
	//sigL1 = sin(sigL1*sigL1*sigL1);
	//sigR2 = sin(sigR2*sigR2*sigR2);
	
	//cubic distortion
	//cubclipL = sigL1;
	//cubclipR = sigR2;
	
	  //if( cubclipL > 1){ cubclipL = 1; }
	  //if( cubclipL < -1){ cubclipL = -1; }
	
	  //if(cubclipR > 1){ cubclipR = 1; }
	  //if(cubclipR < -1){ cubclipR = -1;}	
	
	//cubclipL = (2.f/ kPI) * (1.5 * cubclipL - 0.5 * cubclipL * cubclipL * cubclipL);
	//cubclipR = (2.f/ kPI) * (1.5 * cubclipR - 0.5 * cubclipR * cubclipR * cubclipR);

	
	//Polarity switch resets the graph. Work for natural sounds
    if (fCrossres == 1.0) {
	    
	if( sigL1 < 0){
	   PolarityL = 0;
	   if (PrePolarityL==1) {graph=0;}
	   }
	    
	if( sigL1 > 0){
	   PolarityL = 1;
	   if (PrePolarityL==0) {graph=0;}
	   }
	      
	    //separet reset for sterio sounds needed
         if (sigR2 < 0){
	    PolarityR = 0;
	    if (PrePolarityR==1) {graph=0;}
	    }
	    
	 if (sigR2 > 0){
	    PolarityR = 1;
	    if (PrePolarityR==0) {graph=0;}
	    }
        
        //previous polarit 
        PrePolarityL = PolarityL;
        PrePolarityR = PolarityR;
}
 	
        // Hard clipping from graph
        // 
        // signal is sterio and the clipping can be done on 4 places separetly
        // left+ and left- and right+ and right-
        //
	// Later this gonna be changed to a threshold for more processing, 
	//
       	int interpol = (int)fInterpolation;

    switch (interpol) {
    
	    // Later this will be changed
	    // The logic is (IF Ipsc = 0 THEN wave_y_DSP = next value)


    default:

        if (sigL1 >= wave_y_DSP){
            sigL1  = wave_y_DSP;
	}
	if (sigL1 <= -wave_y_DSP){
	    sigL1  = -wave_y_DSP;
	}
	if (sigR2 >= wave_y_DSP){
	    sigR2 =  wave_y_DSP;
	}
	if (sigR2 <= -wave_y_DSP){
	    sigR2  = -wave_y_DSP;
	}
        
    break;

    case 1:
    {		
	// for Ispc 1 2 3, make new value
	//
	
	float k = wave_y_DSPnext - wave_y_DSP;

	float Interpolation_y_DSP = wave_y_DSP + (k*Ipsc)/3;

        if (sigL1 >= Interpolation_y_DSP){
            sigL1  = Interpolation_y_DSP;
	}
	if (sigL1 <= -Interpolation_y_DSP){
	    sigL1  = -Interpolation_y_DSP;
	}
	if (sigR2 >= Interpolation_y_DSP){
	    sigR2  = Interpolation_y_DSP;
	}
	if (sigR2 <= -Interpolation_y_DSP){
	    sigR2  = -Interpolation_y_DSP;
	}
       
       if (Ipsc == 3) Ipsc = 0;
       else Ipsc++;
    }	
    break;
/*
           void hermite_quadratic(float *p, float x0, float y0, float k0, float x1, float k1)
            {
                // y = p[0]*x^2 + p[1]*x + p[2]
                p[0]    = (k0 - k1)*0.5f / (x0 - x1);
                p[1]    = k0 - 2.0f*p[0]*x0;
                p[2]    = y0 - p[0]*x0*x0 - p[1]*x0;
            }

            void hermite_cubic(float *p, float x0, float y0, float k0, float x1, float y1, float k1)
            {
                // y = p[0]*x^3 + p[1]*x^2 + p[2]*x + p[3]
                // dy/dx = 3*p[0]*x^2 + 2*p[1]*x + p[2]
                double dx    = x1 - x0;
                double dy    = y1 - y0;
                double kx    = dy / dx;
                double xx1   = x1*x1;
                double xx2   = x0 + x1;

                double a     = ((k0 + k1)*dx - 2.0f*dy) / (dx*dx*dx);
                double b     = ((kx - k0) + a*((2.0f*x0-x1)*x0 - xx1))/dx;
                double c     = kx - a*(xx1+xx2*x0) - b*xx2;
                double d     = y0 - x0*(c+x0*(b+x0*a));

                p[0]    = a;
                p[1]    = b;
                p[2]    = c;
                p[3]    = d;
            }

            void exponent(float *p, float x0, float y0, float x1, float y1, float k)
            {
                double e        = exp(k*(x0 - x1));
                p[0]            = (y0 - e*y1) / (1.0 - e);
                p[1]            = (y0 - p[0]) / exp(k*x0);
                p[2]            = k;
            }

            void linear(float *p, float x0, float y0, float x1, float y1)
            {
                p[0]            = (y1 - y0) / (x1 - x0);
                p[1]            = y0 - p[0]*x0;
            }
*/
   // need to modify exp interpolation to fitt this manny samples and be less step
    case 2: 
    {	
	float k = wave_y_DSPnext - wave_y_DSP;
    	float ex = exp(k);
	float Interpolation_y_DSP = 0;

        if (Ipsc == 1){
	       	Interpolation_y_DSP = (wave_y_DSP - ex*wave_y_DSP)/ex;
		fInterpolationTmp = Interpolation_y_DSP;
	}
        if (Ipsc == 2) Interpolation_y_DSP = (wave_y_DSP - fInterpolationTmp)/ex;

        if (sigL1 >= Interpolation_y_DSP){
            sigL1  = Interpolation_y_DSP;
	}
	if (sigL1 <= -Interpolation_y_DSP){
	    sigL1  = -Interpolation_y_DSP;
	}
	if (sigR2 >= Interpolation_y_DSP){
	    sigR2  = Interpolation_y_DSP;
	}
	if (sigR2 <= -Interpolation_y_DSP){
	    sigR2  = -Interpolation_y_DSP;
	}
       
	if(Interpolation_y_DSP < -1.){Interpolation_y_DSP   = -1.; } if(Interpolation_y_DSP  > 1.){Interpolation_y_DSP   = 1.; }

	
       if (Ipsc == 2) Ipsc = 0;
       else Ipsc++;
    }
        break;

    case 3:
     

        if (sigL1 >= wave_y_DSP){
            sigL1  = wave_y_DSP;
	}
	if (sigL1 <= -wave_y_DSP){
	    sigL1  = -wave_y_DSP;
	}
	if (sigR2 >= wave_y_DSP){
	    sigR2  = wave_y_DSP;
	}
	if (sigR2 <= -wave_y_DSP){
	    sigR2  = -wave_y_DSP;
	}
        
	//Ipsc=0;

        break;

    case 4:
     

        if (sigL1 >= wave_y_DSP){
            sigL1  = wave_y_DSP;
	}
	if (sigL1 <= -wave_y_DSP){
	    sigL1  = -wave_y_DSP;
	}
	if (sigR2 >= wave_y_DSP){
	    sigR2  = wave_y_DSP;
	}
	if (sigR2 <= -wave_y_DSP){
	    sigR2  = -wave_y_DSP;
	}
        
	//Ipsc=0;

        break;


    }
	
	//bit
	// this was supposed to be bit dist but it became graph length manipulator
	// now Finaly its gonna be Interpolation
	
	//if (fBit > 0){
	//  if (bit == 0){
	//    bit = fBit;
	//    if (fTilt > 0){bit = bit + graph;}
	//      if (graph<fTilt){bit= bit -graph;}
	//    graph++;
	//  }
	//  bit--;
	//  graph--;
	//}
	// add tv-noise
	//sigL1 = sigL1 + tvnoise(sigL1,fTVNoise,NoiseSample[NoiseSeq]);
	//sigR2 = sigR2 + tvnoise(sigR2,fTVNoise,NoiseSample[NoiseSeq]);
	
	// blend in the distortions need to work on the balance better with exponential fuctions
	sigL1 = sigDryL1 - exp(sigDryL1 * 0.01 * fDist)  + exp(sigL1 * 0.01 * fDist); /*+ (softclipL * 0.01 * fTVNoise) + (cubclipL * 0.01 * fCub);*/
	sigR2 = sigDryR2 - exp(sigDryR2 * 0.01 * fDist)  + exp(sigR2 * 0.01 * fDist); /*+ (softclipR * 0.01 * fTVNoise) + (cubclipR * 0.01 * fCub);*/

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
	
        // Wet knob final blend in (I may need a value between sig and log)
        outFinalL = (sigL1*log(fWet)) + sigDryL1 - (sigDryL1*log(fWet));
        outFinalR = (sigR2*log(fWet)) + sigDryR2 - (sigDryR2*log(fWet));
        
	
	// extra tv noise, need work
	// rms
	sigL1 = sigL1 + rnd[rms];
	sigR2 = sigR2 + rnd[rms];

	// Limit
	if(outFinalL < -1.){ outFinalL = -1.; } if(outFinalL > 1.){ outFinalL = 1.; }
	if(outFinalR < -1.){ outFinalR = -1.; } if(outFinalR > 1.){ outFinalR = 1.; }
	
	
	out1[i] = CheckForBadEggs(sigL1);
	out2[i] = CheckForBadEggs(sigR2);
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
