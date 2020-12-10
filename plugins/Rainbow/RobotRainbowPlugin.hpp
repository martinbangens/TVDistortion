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
#define parameterRed 1
#define parameterOrange 2
#define parameterYellow 3
#define parameterGreen 4
#define parameterBlue 5
#define parameterIndigo 6
#define parameterViolet 7

START_NAMESPACE_DISTRHO

// ---------------------------------------------------------------------------

class Rainbow : public Plugin
{
public:

    Rainbow();


    // -----------------------------------------------------------------------

protected:

    // Info
    
    const char* getLabel() const noexcept override
    {
        return "Rainbow";
    }

    const char* getDescription() const override
    {
        return "Amplifer";
    }
    
    const char* getMaker() const noexcept override
    {
        return "Martin Bangens";
    }
    
    const char* getHomePage() const override
    {
        return "Rainbow";
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
        return d_cconst('R', 'a', 'B', 'w');
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
    
    // -------------------------------------------------------------------

private:
    
    // Parameters
    
    float fWet    = 0;
    float fRed    = 0;
    float fOrange = 0;
    float fYellow = 0;
    float fGreen  = 0;
    float fBlue   = 0;
    float fIndigo = 0;
    float fViolet = 0;
    
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Rainbow)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
