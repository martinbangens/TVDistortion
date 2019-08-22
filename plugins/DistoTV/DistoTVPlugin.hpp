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

#define AREAHEIGHT 190
START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class DistoTVPlugin : public Plugin
{
public:
    enum Parameters
    {
        paramWet= 0,
        paramTVNoise,
        paramBit,
        paramDist,
        paramLow, 
        paramMid,
        paramHigh,
        paramMaster,
        paramCount
    };

    DistoTVPlugin();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "DistoTV";
    }

    const char* getDescription() const override
    {
        return "Distortion, stereo version.";
    }

    const char* getMaker() const noexcept override
    {
        return "DistoTV";
    }

    const char* getHomePage() const override
    {
        return "https://github.com/martinbangens/DistoTV";
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
    
     
    
// -------------------------------------------------------------------


private:
    
    int graph = 0;
    bool cubicSampels = false;
    
    float rnd[191];
    
    float wave_y[AREAHEIGHT+1] = {0};
    
    float sigL1, sigR2, sigDryL1, sigDryR2, outVol;
    
    float fWet, fTVNoise, fBit, fDist;
    
    float fLow, fMid, fHigh, fMaster, fLowMidFreq, fMidHighFreq;

    float lowVol, midVol, highVol;
    float freqLP, freqHP;

    float xLP, a0LP, b1LP;
    float xHP, a0HP, b1HP;

    float out1LP, out2LP, out1HP, out2HP;
    float tmp1LP, tmp2LP, tmp1HP, tmp2HP;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistoTVPlugin)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

