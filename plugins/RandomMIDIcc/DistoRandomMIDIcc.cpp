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

#include "DistoRandomMIDIcc.hpp"
#include <cstdlib>

#include <iostream> //for debuging, see whats going on

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

RandomMIDIccPlugin::RandomMIDIccPlugin()
    : Plugin(6, 0, 0) //parameters,  programs(patches), states(data save)
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
        parameter.ranges.def = 20;
        parameter.ranges.min = 20;
        parameter.ranges.max = 2000;
        break;

    case paramMinMs:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Min ms";
        parameter.symbol     = "ms";
        parameter.unit       = "ms";
        parameter.ranges.def = 20;
        parameter.ranges.min = 20;
        parameter.ranges.max = 2000;
        break;

    case paramMaxValue:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Max Value";
        parameter.symbol     = "";
        parameter.unit       = "";
        parameter.ranges.def = 127;
        parameter.ranges.min = 0;
        parameter.ranges.max = 127;
        break;

    case paramMinValue:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Min Value";
        parameter.symbol     = "";
        parameter.unit       = "";
        parameter.ranges.def = 0;
        parameter.ranges.min = 0;
        parameter.ranges.max = 127;
        break;

    case paramControleNumber:
	parameter.hints      = kParameterIsAutomable;
	parameter.name       = "ControleNumber";
	parameter.symbol     = "";
	parameter.unit       = "cn";
	parameter.ranges.def = 0;	
        parameter.ranges.min = 0;
        parameter.ranges.max = 127;
	break;

    case paramMidiChannel:
	parameter.hints      = kParameterIsAutomable;
        parameter.name       = "MidiChannel";
	parameter.symbol     = "";
	parameter.unit       = "";
	parameter.ranges.def = 0;
	parameter.ranges.min = 0;
	parameter.ranges.max = 16;
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
    case paramMaxValue:
        return fmax_value;
    case paramMinValue:
        return fmin_value;
    case paramControleNumber:
	return fcontrol_number;
    case paramMidiChannel:
	return fmidi_channel;

    default:
        return 0.0f;
    }
}

void RandomMIDIccPlugin::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
    case paramMaxMs:
        fmax_ms         = value;
        break;
    case paramMinMs:
        fmin_ms         = value;
        break;
    case paramMaxValue:
        fmax_value      = value;
        break;
    case paramMinValue:
        fmin_value      = value;
        break;
    case paramControleNumber:
	fcontrol_number = value;
	break;
    case paramMidiChannel:
	fmidi_channel   = value;
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
    fmax_ms = 2000;
    fmin_ms = 20;
    fmax_value = 127;
    fmin_value = 0;
    fcontrol_number = 0;
    fmidi_channel = 0;

    // reset values (not sure if need now)
    activate();

    }

}

// -----------------------------------------------------------------------
// Process

void RandomMIDIccPlugin::activate()
{
// Generate a set of tru random numbers here. could bee an array like int random[10]
}

void RandomMIDIccPlugin::deactivate()
{
// this my not be needed, but this is used for NULL the data for saftey, and watever else you can think of when deactivatin the plugin
}

void RandomMIDIccPlugin::run(const float**, float**, uint32_t,
			     const MidiEvent* events, uint32_t eventCount)
{
   uint8_t chan;
   struct MidiEvent cc_event;

	for (uint32_t i=0; i<eventCount; ++i) {
	
	// writeMidiEvent(cc_event);
	//
	// need some fast but real random algo to generate infinit random new numbers
	//
	// then use NUMBER % 127 and send it out to midi cc
	// 
	// MIDI CC is 0xB0 followd by 2 Data bytes
	//


	// Just send midi data from input right to output
	// 
	
	writeMidiEvent(events[i]);
	}

}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new RandomMIDIccPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
