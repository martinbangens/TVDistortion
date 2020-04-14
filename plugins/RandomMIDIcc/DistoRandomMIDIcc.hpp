/*
 * RandomMIDIcc
 * 
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
#include <cstdlib>


START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class RandomMIDIccPlugin : public Plugin
{
public:
    enum Parameters
    {
        paramMaxMs,
        paramMinMs,
        paramMaxValue,
        paramMinValue,
	paramControleNumber,
	paramMidiChannel
    };

    RandomMIDIccPlugin();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "RandomMIDIcc";
    }

    const char* getDescription() const override
    {
        return "Generate random Midi CC values for mad people";
    }

    const char* getMaker() const noexcept override
    {
        return "Martin Bangens";
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
        return d_cconst('R', 'a', 'N', 'z');
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
    void run(const float**, float**, uint32_t,
		    const MidiEvent* events, uint32_t eventCount) override;

    

    
// -------------------------------------------------------------------
private:
// this is only temporarily, have not decided what types to use 

    int fmax_ms, fmin_ms;
    int fmax_value, fmin_value;
    int fcontrol_number;
    int fmidi_channel;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RandomMIDIccPlugin)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
