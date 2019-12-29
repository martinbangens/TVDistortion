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
#include "ImageWidgets.hpp"

#include "DistoTVArtwork.hpp"

#define AREAHEIGHT 1000

START_NAMESPACE_DISTRHO
using DGL::Image;
using DGL::ImageSwitch;
using DGL::ImageKnob;
using DGL::ImageSlider;



// -----------------------------------------------------------------------

class DistoTVUI : public UI,
                         public ImageKnob::Callback,
                         public ImageSlider::Callback,
                         public ImageSwitch::Callback
{
public:
    DistoTVUI();
    //~DistoTVUI() override;
   

protected:
    // -------------------------------------------------------------------
    // DSP Callbacks

    void parameterChanged(uint32_t index, float value) override;
    void programLoaded(uint32_t index);
    void stateChanged(const char* key, const char* value);
    
    
  

    // -------------------------------------------------------------------
    // Widget Callbacks

    
    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;
    void imageSliderDragStarted(ImageSlider* slider) override;
    void imageSliderDragFinished(ImageSlider* slider) override;
    void imageSliderValueChanged(ImageSlider* slider, float value) override;
    void imageSwitchClicked(ImageSwitch* tog, bool down) override;
    
    // Display
    void onNanoDisplay();
    void uiIdle() override;
    
    // Mouse
    bool onMouse(const MouseEvent & ) override;
    bool onMotion (const MotionEvent & ) override;

private:
    
    Image fImgBackground;
    
    float wave_y[AREAHEIGHT+1] = {0}; //Reflect DSP Data
    

    bool fDragging;
    bool fDragValid;
    DGL::Rectangle<int> fCanvasArea; //OpenGL image data for the wave + size and position 

    bool fWaveUpdated;
    char fWaveState[4*AREAHEIGHT+1]; // 4 char(3 values and 1 space for every pixel) +1 extra for "NULL" terminator = The State Wave String :D

    bool fBoolCrossres;
    
    
    ScopedPointer<ImageKnob> fKnobLow, fKnobMid, fKnobHigh, fKnobMaster, fKnobDist, fKnobPreAMP, fKnobBit, fKnobBitTilt, fKnobTVNoise, fKnobCubic;
    ScopedPointer<ImageSlider> fSliderWet;
    ScopedPointer<ImageSwitch> fSwitchCrossres;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistoTVUI)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

