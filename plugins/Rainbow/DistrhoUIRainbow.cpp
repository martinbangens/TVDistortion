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

#include "DistrhoPluginRainbow.hpp"
#include "DistrhoUIRainbow.hpp"

namespace Art = DistrhoArtworkRainbow;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

RainbowUI::RainbowUI()
    : UI(Art::backgroundWidth, Art::backgroundHeight),
      fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, GL_BGR)
{
    
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight);

    fKnobGain = new ImageKnob(this, knobImage);
    fKnobGain->setId(parameterGain);
    fKnobGain->setAbsolutePos(40, 150);
    fKnobGain->setRange(-48.0,48.0);
    fKnobGain->setDefault(0.0f);
    fKnobGain->setRotationAngle(330);
    fKnobGain->setCallback(this);

    fKnobTone = new ImageKnob(this, knobImage);
    fKnobTone->setId(parameterTone);
    fKnobTone->setAbsolutePos(315,150);
    fKnobTone->setRange(-100.0, 100.0);
    fKnobTone->setDefault(0.0);
    fKnobTone->setRotationAngle(330);
    fKnobTone->setCallback(this);

    programLoaded(0);
}

void RainbowUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
        case parameterGain:
	    fKnobGain->setValue(value);
	    break;
	case parameterTone:
	    fKnobTone->setValue(value);
	    break;
    }
}

void RainbowUI::programLoaded(uint32_t index)
{
    switch (index)
    {
        case 0:
	    fKnobGain->setValue(0.0f);
	    fKnobTone->setValue(1000.0);
	    break;
    }
}

void RainbowUI::imageKnobDragStarted(ImageKnob* knob)
{
    editParameter(knob->getId(), true);
}

void RainbowUI::imageKnobDragFinished(ImageKnob* knob)
{
    editParameter(knob->getId(), false);
}

void RainbowUI::imageKnobValueChanged(ImageKnob* knob, float value)
{
    setParameterValue(knob->getId(), value);
}

void RainbowUI::onDisplay()
{
   fImgBackground.draw(); 
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new RainbowUI();
}

END_NAMESPACE_DISTRHO

