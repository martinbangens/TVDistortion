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

#include "RobotCreamWhipperPlugin.hpp"
#include "RobotCreamWhipperUI.hpp"

namespace Art = RobotCreamWhipperArtwork;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

CreamWhipperUI::CreamWhipperUI()
    : UI(Art::backgroundWidth, Art::backgroundHeight),
      fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, GL_BGR)
{
    
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight);

    fKnobWet = new ImageKnob(this, knobImage);
    fKnobWet->setId(parameterWet);
    fKnobWet->setAbsolutePos(1, 210);
    fKnobWet->setRange(0.0,100.0);
    fKnobWet->setDefault(0.0f);
    fKnobWet->setRotationAngle(330);
    fKnobWet->setCallback(this);

    fKnobThreshold = new ImageKnob(this, knobImage);
    fKnobThreshold->setId(parameterThreshold);
    fKnobThreshold->setAbsolutePos(241,210);
    fKnobThreshold->setRange(0.0, 100.0);
    fKnobThreshold->setDefault(0.0);
    fKnobThreshold->setRotationAngle(330);
    fKnobThreshold->setCallback(this);

}

void CreamWhipperUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
        case parameterWet:
	    fKnobWet->setValue(value);
	    break;
	case parameterThreshold:
	    fKnobThreshold->setValue(value);
	    break;
    }
}

void CreamWhipperUI::programLoaded(uint32_t index)
{
    switch (index)
    {
        case 0:
	    fKnobWet->setValue(0.0f);
	    fKnobThreshold->setValue(0.0f);
	    break;
    }
}

void CreamWhipperUI::imageKnobDragStarted(ImageKnob* knob)
{
    editParameter(knob->getId(), true);
}

void CreamWhipperUI::imageKnobDragFinished(ImageKnob* knob)
{
    editParameter(knob->getId(), false);
}

void CreamWhipperUI::imageKnobValueChanged(ImageKnob* knob, float value)
{
    setParameterValue(knob->getId(), value);
}

void CreamWhipperUI::onDisplay()
{
    fImgBackground.draw(); 
  

}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new CreamWhipperUI();
}

END_NAMESPACE_DISTRHO

