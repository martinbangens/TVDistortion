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

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"


#include "RobotCreamWhipperArtwork.hpp"

START_NAMESPACE_DISTRHO

using DGL::Image;
using DGL::ImageKnob;

// -----------------------------------------------------------------------

class CreamWhipperUI : public UI,
                       public ImageKnob::Callback
{
    public:
        CreamWhipperUI();


    protected:
    
	void parameterChanged(uint32_t index, float value) override;
        void programLoaded(uint32_t index);


	void imageKnobDragStarted(ImageKnob* knob) override;
	void imageKnobDragFinished(ImageKnob* knob) override;
	void imageKnobValueChanged(ImageKnob* knob, float value) override;

	void onDisplay();



    private:

        Image fImgBackground;
 
        

        ScopedPointer<ImageKnob> fKnobWet, fKnobThreshold;

	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CreamWhipperUI)
};

END_NAMESPACE_DISTRHO

