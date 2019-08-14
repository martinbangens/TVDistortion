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

#include "DistoTVPlugin.hpp"
#include "DistoTVUI.hpp"
#include <Widget.hpp>

START_NAMESPACE_DISTRHO

namespace Art = DistoTVArtwork;

// -----------------------------------------------------------------------

DistoTVUI::DistoTVUI() // constructor definition.
    : UI(Art::backgroundWidth, Art::backgroundHeight),// initializer list
      fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, GL_BGR)
{

    
    // sliders
    Image sliderImage(Art::sliderData, Art::sliderWidth, Art::sliderHeight);

    
    fSliderWet = new ImageSlider(this, sliderImage);
    fSliderWet->setId(DistoTVPlugin::paramWet);
    fSliderWet->setInverted(false); //not sure
    fSliderWet->setStartPos(20,1);
    fSliderWet->setEndPos(402,1);
    fSliderWet->setRange(0.0f, 100.0f);
    fSliderWet->setDefault(0.0f);
    fSliderWet->setCallback(this);

    // knobs Gett Imgage data
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight);
    Image knobSmallImage(Art::knobSmallData, Art::knobSmallWidth, Art::knobSmallHeight);
    
    // knob TV-Noise
    fKnobTVNoise = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobTVNoise->setId(DistoTVPlugin::paramBit);
    fKnobTVNoise->setAbsolutePos(20, 120);
    fKnobTVNoise->setRange(0.0f, 100.0f);
    fKnobTVNoise->setDefault(0.0f);
    fKnobTVNoise->setRotationAngle(270);
    fKnobTVNoise->setCallback(this);
    
    // knob Bit
    fKnobBit = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobBit->setId(DistoTVPlugin::paramBit);
    fKnobBit->setAbsolutePos(20, 220);
    fKnobBit->setRange(0.0f, 100.0f);
    fKnobBit->setDefault(0.0f);
    fKnobBit->setRotationAngle(270);
    fKnobBit->setCallback(this);

    // knob Dist
    fKnobDist = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobDist->setId(DistoTVPlugin::paramDist);
    fKnobDist->setAbsolutePos(20, 312);
    fKnobDist->setRange(0.0f, 100.0f);
    fKnobDist->setDefault(0.0f);
    fKnobDist->setRotationAngle(270);
    fKnobDist->setCallback(this);

    // knob Master
    fKnobMaster = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobMaster->setId(DistoTVPlugin::paramMaster);
    fKnobMaster->setAbsolutePos(20, 408);
    fKnobMaster->setRange(-24.0f, 24.0f);
    fKnobMaster->setDefault(0.0f);
    fKnobMaster->setRotationAngle(270);
    fKnobMaster->setCallback(this);
    
    //knob Low filter
    fKnobLow = new ImageKnob(this, knobSmallImage);
    fKnobLow->setId(DistoTVPlugin::paramLow);
    fKnobLow->setAbsolutePos(130, 530);
    fKnobLow->setRange(-24.0f, 24.0f);
    fKnobLow->setDefault(0.0f);
    fKnobLow->setRotationAngle(270);
    fKnobLow->setCallback(this);
    
    //knob Mid filter
    fKnobMid = new ImageKnob(this, knobSmallImage);
    fKnobMid->setAbsolutePos(208, 530);
    fKnobMid->setId(DistoTVPlugin::paramMid);
    fKnobMid->setRange(-24.0f, 24.0f);
    fKnobMid->setDefault(0.0f);
    fKnobMid->setRotationAngle(270);
    fKnobMid->setCallback(this);
    
    //knob High filter
    fKnobHigh = new ImageKnob(this, knobSmallImage);
    fKnobHigh->setId(DistoTVPlugin::paramHigh);
    fKnobHigh->setAbsolutePos(292, 530);
    fKnobHigh->setRange(-24.0f, 24.0f);
    fKnobHigh->setDefault(0.0f);
    fKnobHigh->setRotationAngle(270);
    fKnobHigh->setCallback(this);

  
  
    // set default values
    programLoaded(0);
}
//DistoTVUI::~DistoTVUI(){}


// -----------------------------------------------------------------------
// DSP Callbacks

void DistoTVUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case DistoTVPlugin::paramLow:
        fKnobLow->setValue(value);
        break;
    case DistoTVPlugin::paramMid:
        fKnobMid->setValue(value);
        break;
    case DistoTVPlugin::paramHigh:
        fKnobHigh->setValue(value);
        break;
    case DistoTVPlugin::paramMaster:
        fKnobMaster->setValue(value);
        break;
    }
}

void DistoTVUI::programLoaded(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    fKnobLow->setValue(0.0f);
    fKnobMid->setValue(0.0f);
    fKnobHigh->setValue(0.0f);
    fKnobMaster->setValue(0.0f);
    //fKnobLowMid->setValue(220.0f);
    //fKnobMidHigh->setValue(2000.0f);
}

// -----------------------------------------------------------------------
// Widget Callbacks

void DistoTVUI::imageKnobDragStarted(ImageKnob* knob)
{
    editParameter(knob->getId(), true);
}

void DistoTVUI::imageKnobDragFinished(ImageKnob* knob)
{
    editParameter(knob->getId(), false);
}

void DistoTVUI::imageKnobValueChanged(ImageKnob* knob, float value)
{
    setParameterValue(knob->getId(), value);
}

void DistoTVUI::imageSliderDragStarted(ImageSlider* slider)
{
    editParameter(slider->getId(), true);
}

void DistoTVUI::imageSliderDragFinished(ImageSlider* slider)
{
    editParameter(slider->getId(), false);
}

void DistoTVUI::imageSliderValueChanged(ImageSlider* slider, float value)
{
    setParameterValue(slider->getId(), value);
}

bool DistoTVUI::onMouse(const MouseEvent & ev) // this gets called when the mouse is presse, released.
{
  if (ev.press)// if pressed not released and if left mouse button
    if (ev.button == 1)
    {
    //last condition is, if inside TV-Screen
      if(ev.pos.getY() >= 195 and ev.pos.getY() <= 385 and ev.pos.getX() >= 130 and ev.pos.getX() <= 320){
	printf("Im inside tv\n");
	printDots = true;
	return true;
      }
    }
  printDots = false;
  printf("printDots is false\n");
  return true;
}

bool DistoTVUI::onMotion (const MotionEvent & po) // this gets called when mouse is moving over the UI
{
  if(po.pos.getY() >= 195 and po.pos.getY() <= 385 and po.pos.getX() > 130 and po.pos.getX() < 320){
      
    
      

      
  if (printDots){
    line[po.pos.getX()-130]= po.pos.getY() - 300;  
    repaint();  
  }
    
}  
  
  
  
  printf("the mouse was moved");
  printf("	X=%i	", po.pos.getX());
  printf("Y=%i\n", po.pos.getY());
  
  return true;
}

void DistoTVUI::onNanoDisplay()
{
  fImgBackground.draw();
     //background
    
    // here is the pixel dotts from nano that is supposed to be the line in the tv
    
    for (int i = 0; i <= 190; i++){
    
    beginPath();
    circle(130+ i, line[i] + 300 , 1.5);
    fillColor(70,33,5);
    fill();
    closePath();
    
  }


}
// -----------------------------------------------------------------------

UI* createUI()
{
    return new DistoTVUI();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
