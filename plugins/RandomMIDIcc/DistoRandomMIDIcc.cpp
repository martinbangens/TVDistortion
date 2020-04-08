/*
 * RandomMIDIcc
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
#include "DistoRandomMIDIcc.hpp"
#include <cstdlib>

#include <iostream> //for debuging, see whats going on

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

RandomMIDIccPlugin::RandomMIDIccPlugin()
    : Plugin(4, 0, 0) //parameters,  programs(patches), states(data save)
{
    // set default values
    loadProgram(0);

    // reset
    deactivate();
}

// -----------------------------------------------------------------------
// Init

void RandomMIDIccPlugin::initParameter(uint32_t index, Parameter& parameter)
{
    switch (index)
    {
    case paramMaxMs:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Max ms";
        parameter.symbol     = "ms";
        parameter.unit       = "ms";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramMinMs:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Min ms";
        parameter.symbol     = "ms";
        parameter.unit       = "ms";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramMaxNum:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Max number";
        parameter.symbol     = "nr.";
        parameter.unit       = "nr.";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;

    case paramMinNum:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Min number";
        parameter.symbol     = "nr.";
        parameter.unit       = "nr.";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 100.0f;
        break;


     
    }
}



// -----------------------------------------------------------------------
// Internal data

float RandomMIDIccPlugin::getParameterValue(uint32_t index) const
{
    switch (index)
    {
    case paramMaxMs:
        return fmax_ms;
    case paramMinMs:
        return fmin_ms;
    case paramMaxNum:
        return fmax_num;
    case paramMinNum:
        return fmin_num;

    default:
        return 0.0f;
    }
}

void RandomMIDIccPlugin::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
    case paramMaxMs:
        fmax_ms   = value;
        break;
    case paramMinMs:
        fmin_ms   = value;
        break;
    case paramMaxNum:
        fmax_num   = value;
        break;
    case paramMinNum:
        fmin_num = value;
        break;
    }
}



void RandomMIDIccPlugin::initProgramName(uint32_t index, String& programName)
{
  
  switch (index) {
        case 0:
            programName = "DefaultName";
            break;
    }
}


// this is used for loding a default "patch" in the daw/plugin host. Some daws then let you create you own patches, but we dont need to have this internaly 
void RandomMIDIccPlugin::loadProgram(uint32_t index)
{
  
  
    if (index == 0){

    // Default values
    fmax_ms = 0.0f;
    fmin_ms = 0.0f;
    fmax_num = 0.0f;
    fmin_num = 0.0f;


    // reset values (not sure if need now)
    activate();

    }

}

// -----------------------------------------------------------------------
// Process

void RandomMIDIccPlugin::activate()
{
// here we can execute code that take time, that we dont want to do when the plugin is runing in realtime
}

void RandomMIDIccPlugin::deactivate()
{
// this my not be needed, but this is used for NULL the data for saftey, and watever else you can think of when deactivatin the plugin
}

// need to add midi out here only for now
void RandomMIDIccPlugin::run(const float**, float**, uint32_t, const MidiEvent * events, uint32_t eventCount)
{
    struct MidiEvent cc_event;
    writeMidiEvent(cc_event);

}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new RandomMIDIccPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
