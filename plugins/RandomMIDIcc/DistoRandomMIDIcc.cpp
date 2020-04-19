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

#include <stdio.h>

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
        parameter.symbol     = "";
        parameter.unit       = "ms";
        parameter.ranges.def = 20;
        parameter.ranges.min = 20;
        parameter.ranges.max = 2000;
        break;

    case paramMinMs:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Min ms";
        parameter.symbol     = "";
        parameter.unit       = "ms";
        parameter.ranges.def = 20;
        parameter.ranges.min = 20;
        parameter.ranges.max = 2000;
        break;

    case paramMaxValue:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Max Value";
        parameter.symbol     = "";
        parameter.unit       = "v";
        parameter.ranges.def = 127;
        parameter.ranges.min = 0;
        parameter.ranges.max = 127;
        break;

    case paramMinValue:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Min Value";
        parameter.symbol     = "";
        parameter.unit       = "v";
        parameter.ranges.def = 0;
        parameter.ranges.min = 0;
        parameter.ranges.max = 127;
        break;

    case paramControleNumber:
	parameter.hints      = kParameterIsAutomable;
	parameter.name       = "ControleNumber";
	parameter.symbol     = "";
	parameter.unit       = "cc";
	parameter.ranges.def = 0;	
        parameter.ranges.min = 0;
        parameter.ranges.max = 127;
	break;

    case paramMidiChannel:
	parameter.hints      = kParameterIsAutomable;
        parameter.name       = "MidiChannel";
	parameter.symbol     = "";
	parameter.unit       = "ch";
	parameter.ranges.def = 1;
	parameter.ranges.min = 1;
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
	return fmidi_channel + 1;

    default:
        return 0.0f;
    }
}

void RandomMIDIccPlugin::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
    case paramMaxMs:
        fmax_ms = value;
        break;
    case paramMinMs:
        fmin_ms = value;
        break;
    case paramMaxValue:
        fmax_value = value;
        break;
    case paramMinValue:
        fmin_value = value;
        break;
    case paramControleNumber:
	fcontrol_number = value;
	break;
    case paramMidiChannel:
	fmidi_channel = value -1; // in binary midi channel 0 is practically channel 1
	break;
    }
}



void RandomMIDIccPlugin::initProgramName(uint32_t index, String& programName)
{
  
  switch (index) {
        case 0:
            programName = "Default";
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

    // reset values (not sure if needed now)
    activate();

    }

}

// -----------------------------------------------------------------------
// Process


unsigned long RandomMIDIccPlugin::xorshf96(void){          //period 2^96-1
	unsigned long t;
	    fx ^= fx << 16;
	    fx ^= fx >> 5;
	    fx ^= fx << 1;

	    t = fx;
            fx = fy;
	    fy = fz;
	    fz = t ^ fx ^ fy;

	return fz;
}


void RandomMIDIccPlugin::activate()
{
	fFramesToMs = getSampleRate();
	fFramesToMs = fFramesToMs/1000;

	//printf("Frames per milisecond %f\n", fFramesToMs);
	
	//printf("Frames for 20 milliseconds %f\n", fFramesToMs*20);
	
	fFrameClock = (uint32_t ) (fmin_ms * fFramesToMs)
			+ (uint32_t) xorshf96() % (uint32_t) (fmax_ms * fFramesToMs);
	
	//printf("fFrameClock = %u", fFrameClock);
}

void RandomMIDIccPlugin::deactivate()
{
	// reset plugin to original state
	fx=123456789, fy=362436069, fz=521288629;
	fFrameClock = (uint32_t ) (fmin_ms * fFramesToMs)
			+ (uint32_t) xorshf96() % (uint32_t) (fmax_ms * fFramesToMs);

}

void RandomMIDIccPlugin::run(const float**, float**, uint32_t frames,
			     const MidiEvent* events, uint32_t eventCount)
{

	for (uint32_t i=0; i<eventCount; ++i) {
	
	// Generate infinit random new numbers
	//
	// NUMBER % 127 and send it out to midi cc
	// 
	// MIDI CC is 0xB0(1011xxxx, xxxx is chanel number) followd by 2 Data bytes
	// 2nd Byte Value is "CC number" 3rd Byte Value is final Value to be set
	//
	// https://www.midi.org/specifications-old/item/the-midi-1-0-specification
	//


	// Send midi data from input right to output first
	//
	// Here you can learn what the events data looks like
	//
	//
	//
	/*	printf("-----------------------\n");
		printf("Midi:events.frame  %u\n", events[i].frame);
		printf("Midi:events.size   %u\n", events[i].size);
		printf("Midi:events.data[0]%X\n", events[i].data[0]);
		printf("Midi:events.data[1]%X\n", events[i].data[1]);
		printf("Midi:events.data[2]%X\n", events[i].data[2]);
		//printf("Midi:events.data[3]%X\n", events[i].data[3]); // usually random junk
		printf("-----------------------\n");

	*/	writeMidiEvent(events[i]);
	}


	if (fFrameClock > frames){
		fFrameClock = fFrameClock - frames;
		return;
	}
	else{	
again:
   		MidiEvent MyMidiEvent;
		uint8_t max_value_overload = 0;

		if (fmin_value + fmax_value > 127) max_value_overload = (fmin_value + fmax_value) % 127;

		MyMidiEvent.frame = fFrameClock;
		MyMidiEvent.size = 3;
		MyMidiEvent.data[0] = 0xB0 | (uint8_t)fmidi_channel;
		MyMidiEvent.data[1] = (uint8_t) fcontrol_number;
		MyMidiEvent.data[2] = (uint8_t) fmin_value + (xorshf96() % (fmax_value-max_value_overload));

		writeMidiEvent(MyMidiEvent);

		// genrate new time
		//
		
		if (fmin_ms > fmax_ms) fFrameClock = (uint32_t) (fmin_ms * fFramesToMs);
		else{
		fFrameClock = (uint32_t ) (fmin_ms * fFramesToMs)
			+ (uint32_t) xorshf96() % (uint32_t) (fmax_ms * fFramesToMs);
		}
		
	if (fFrameClock <= frames) goto again;
	
	}
	
        // the frame clock's gonna count the samples util the next midi
	// event. the frame clock's value ganna be set randomly.
	// every call to this run function redeuce the clocks value.
	// IF there is one or more Midi event to be send out,
	// the plugin enters a special code in the loop to genrate
	// and send out those values.
}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new RandomMIDIccPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
