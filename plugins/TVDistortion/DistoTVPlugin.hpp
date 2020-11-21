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

#pragma once

#include "DistrhoPlugin.hpp"
#include <cmath>


#define AREAHEIGHT 301
#define AREALENGTH 1000
START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class DistoTVPlugin : public Plugin
{
public:
    enum Parameters
    {
        paramWet,
        paramDist,
        paramPre,
	paramAmpType,
 	paramInterpolation,
        paramScale,
        paramCrossres,
	paramMouseSM,
        paramLow, 
        paramMid,
        paramHigh,
        paramMaster
    };

    DistoTVPlugin();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "TVDistortion";
    }

    const char* getDescription() const override
    {
        return "Dynamic Distortion";
    }

    const char* getMaker() const noexcept override
    {
        return "Martin Bangens";
    }

    const char* getHomePage() const override
    {
        return "TVDistortion";
    }

    const char* getLicense() const noexcept override
    {
        return "LGPL";
    }

    uint32_t getVersion() const noexcept override
    {
        return d_version(0, 0, 1);
    }

    int64_t getUniqueId() const noexcept override
    {
        return d_cconst('D', 'i', 'T', 'v');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data
      
    float getParameterValue(uint32_t index) const override;
    void  setParameterValue(uint32_t index, float value) override;
    void  loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;
    void deactivate() override;
    void run(const float** inputs, float** outputs, uint32_t frames) override;
    void setState(const char* key, const char* value) override;
    void initState(unsigned int index, String& key, String& defval) override;
    String getState(const char* key) const override;
    
    //DSP
    
    float tvnoise(float sig, float knob, float NoiseSample);
    float tube(float sig, float dbamp);
    float CheckForBadEggs(float input);
    
// -------------------------------------------------------------------
    /*float CheckForBadEggs(float input){
    switch(std::fpclassify(input)){
        case FP_INFINITE:
	  had_Inf = true;
	  return 0.0;
        case FP_NAN:
	  had_NuN = true;
	  return 0.0;

        default:
	  return input;
   }
}
*/
private:

    // need to get a vacuum cleaner here...
   
    uint8_t Ipsc = 0;  // Interpolation Sampel clock
    float wave_y_DSP_next = 0;

    float fCrossres = false, fMouseSM = false;
    float fScale = 0, fScaleDSP = 0.5;
  
    bool had_NuN = false;
    bool had_Inf = false;
  
    int graph = 0, NoiseSeq = 0, rms = 0;
    bool updatebuff = false;
    //bool cubicSampels = false;
    
    bool PrePolarityL, PolarityL, PrePolarityR, PolarityR;
    
    float rnd[191];
    float bit; 
    //float wave_y[AREAHEIGHT+1] = {0};
    float wave_y_DSP = 0;
    float NoiseSample[6] = {0.00000001,0.000000000002,0.0000000002,0.00000000001,0.0000000001,0};

    // this one is a new way to store the wave information
    uint16_t DSP_wave_y_Pixels[1000] = {0};      // (0-999)+1
    
    float softclipL, softclipR, cubclipL, cubclipR;
    
    float sigL1, sigR2, sigDryL1, sigDryR2, outFinalL, outFinalR;
    
    float fWet, fDist, fPre, fAmpType, fInterpolation;
    
    float fLow, fMid, fHigh, fMaster;

    float lowVol, midVol, highVol;
    float freqLP, freqHP, outVol;

    float xLP, a0LP, b1LP;
    float xHP, a0HP, b1HP;

    float out1LP, out2LP, out1HP, out2HP;
    float tmp1LP, tmp2LP, tmp1HP, tmp2HP;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistoTVPlugin)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

