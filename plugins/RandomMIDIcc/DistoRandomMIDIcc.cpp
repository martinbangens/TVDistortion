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

    // reset values (not sure if needed now)
    activate();

    }

}

// -----------------------------------------------------------------------
// Process


unsigned long RandomMIDIccPlugin::xorshf96(void) {          //period 2^96-1
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
	fSampleRate = getSampleRate();

	//test
	//std::cout << RandomMIDIccPlugin::xorshf96() << std::endl;
}

void RandomMIDIccPlugin::deactivate()
{
// this my not be needed, but this is used for NULL the data for saftey, and watever else you can think of when deactivatin the plugin
}

void RandomMIDIccPlugin::run(const float**, float**, uint32_t frames,
			     const MidiEvent* events, uint32_t eventCount)
{
   uint8_t chan;
   fFrameClock += frames;
   MidiEvent MyMidiEvent;

   //test     
   //std::cout << "frames:"  << frames << std::endl;

	for (uint32_t i=0; i<eventCount; ++i) {
	
	// need some fast but real random algo to generate infinit random new numbers
	//
	// then use NUMBER % 127 and send it out to midi cc
	// 
	// MIDI CC is 0xB0(1011xxxx, xxxx is chanel number) followd by 2 Data bytes
	// 2nd Byte Value is "CC number" 3rd Byte Value is final Value to be set
	//
	// https://www.midi.org/specifications-old/item/the-midi-1-0-specification
	//


	// Just send midi data from input right to output
	// this should be priority nr.1 cus its not good to "stay in the way" for midi in
	//
	//
	//
	// Here I can learn what the events data looks like
	//
	//
	//
		printf("-----------------------\n");
		printf("Midi:events.frame  %u\n", events[i].frame);
		printf("Midi:events.size   %u\n", events[i].size);
		printf("Midi:events.data[0]%X\n", events[i].data[0]);
		printf("Midi:events.data[1]%X\n", events[i].data[1]);
		printf("Midi:events.data[2]%X\n", events[i].data[2]);
		printf("Midi:events.data[3]%X\n", events[i].data[3]); // usually random junk
		printf("-----------------------\n");

		writeMidiEvent(events[i]);
	}
	
	//
	//
	//	TEST
	//
	//
	
	//	MyMidiEvent.frame = 100;
	//	MyMidiEvent.size = 3; // for midi cc
	//	MyMidiEvent.data[0] = 0xB0; // the ending 0 is chanel number
	//    	MyMidiEvent.data[1] = 0; // cc number
	//	MyMidiEvent.data[2] = xorshf96() % 127;
	//	MyMidiEvent.data[3] = 0xB

	//	writeMidiEvent(MyMidiEvent);

	

}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new RandomMIDIccPlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
