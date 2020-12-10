/*
* Copyright (C) 2020 Martin Bångens <marbangens@gmail.com>
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
#include <algorithm>

//Parameter ID's

#define parameterWet 0
#define parameterThreshold 1

START_NAMESPACE_DISTRHO

// ---------------------------------------------------------------------------

class CreamWhipper : public Plugin
{
public:

    CreamWhipper();


    // -----------------------------------------------------------------------

protected:

    // Info
    
    const char* getLabel() const noexcept override
    {
        return "CreamWhipper";
    }

    const char* getDescription() const override
    {
        return "Saturation";
    }
    
    const char* getMaker() const noexcept override
    {
        return "Martin Bangens";
    }
    
    const char* getHomePage() const override
    {
        return "CreamWhipper";
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
        return d_cconst('C', 'r', 'e', 'M');
    }



    // -----------------------------------------------------------------------

    //Int

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    //Data
    
    float getParameterValue(uint32_t index) const override;
    void  setParameterValue(uint32_t index, float value) override;
    void  loadProgram(uint32_t index) override;

    //Process
    
    void activate() override;
    void deactivate() override;
    void run(const float** inputs, float** outputs, uint32_t frames) override;
    
    // DSP
    
    float saturateA(float x, float t);
    float saturateB(float x, float t);
    float saturateC(float x, float t);
    float sigmoidA(float x);
    float sigmoidB(float x);

    float waveshaper1(float x, float a);

    // -------------------------------------------------------------------

private:
    
    // Parameters
    
    float fWet, fThreshold;
    
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CreamWhipper)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
