/*
 * DistoTV Plugin, based on 3BandEQ by Filipe Coelho
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

#include "DistrhoUI.hpp"
#include "DistoTVArtwork.hpp"
#include <NanoVG.hpp>
#include "ImageWidgets.hpp"
#include "Widget.hpp"



START_NAMESPACE_DISTRHO
using DGL::Image;
using DGL::ImageKnob;
using DGL::NanoVG;



// -----------------------------------------------------------------------

class DistoTVUI : public UI,
                         public ImageKnob::Callback,
                         public ImageSlider::Callback
{
public:
    DistoTVUI();
    //~DistoTVUI() override;
   

protected:
    // -------------------------------------------------------------------
    // DSP Callbacks

    void parameterChanged(uint32_t index, float value) override;
    void programLoaded(uint32_t index) override;

    // -------------------------------------------------------------------
    // Widget Callbacks

    //void imageButtonClicked(ImageButton* button, int) override;
    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;
    void imageSliderDragStarted(ImageSlider* slider) override;
    void imageSliderDragFinished(ImageSlider* slider) override;
    void imageSliderValueChanged(ImageSlider* slider, float value) override;
    
    // Mouse
    bool onMouse(const MouseEvent & ) override;
    bool onMotion (const MotionEvent & ) override;
    
   // void onDisplay() override;
    void onNanoDisplay()  override;

private:
    
    Image fImgBackground;
    //ImageAboutWindow fAboutWindow;
    
    
    //ScopedPointer<ImageButton> fButtonAbout;
    ScopedPointer<ImageKnob> fKnobLow, fKnobMid, fKnobHigh, fKnobMaster, fKnobDist, fKnobBit, fKnobTVNoise;
    ScopedPointer<ImageSlider> fSliderWet;
    
    
    //NanoVG fPixmap;
    //std::vector<fPixmap*> vPixmap;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistoTVUI)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

