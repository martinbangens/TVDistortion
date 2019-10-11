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


START_NAMESPACE_DISTRHO

namespace Art = DistoTVArtwork;

// -----------------------------------------------------------------------

DistoTVUI::DistoTVUI() // constructor definition.
    : UI(Art::backgroundWidth, Art::backgroundHeight),// initializer list
      fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, GL_BGR),
      fWaveUpdated(false)
      
{
    fDragging = false;
    fDragValid = false;
    
    // sliders
    Image sliderImage(Art::sliderData, Art::sliderWidth, Art::sliderHeight);

    // Wet slider
    fSliderWet = new ImageSlider(this, sliderImage);
    fSliderWet->setId(DistoTVPlugin::paramWet);
    fSliderWet->setInverted(false); //not sure
    fSliderWet->setStartPos(20,1);
    fSliderWet->setEndPos(402,1);
    fSliderWet->setRange(0.0f, 100000.0f);
    fSliderWet->setDefault(50000.0f);
    fSliderWet->setCallback(this);

    // knobs Gett Imgage data
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight);
    Image knobSmallImage(Art::knobSmallData, Art::knobSmallWidth, Art::knobSmallHeight);
    
    // knob TV-Noise
    fKnobTVNoise = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobTVNoise->setId(DistoTVPlugin::paramTVNoise);
    fKnobTVNoise->setAbsolutePos(20, 120);
    fKnobTVNoise->setRange(0.0f, 100.0f);
    fKnobTVNoise->setDefault(0.0f);
    fKnobTVNoise->setRotationAngle(270);
    fKnobTVNoise->setCallback(this);
    
    //knob Cubics
    fKnobCubic = new ImageKnob(this, knobSmallImage);
    fKnobCubic->setId(DistoTVPlugin::paramCub);
    fKnobCubic->setAbsolutePos(3, 104);
    fKnobCubic->setRange(0.0f, 100.0f);
    fKnobCubic->setDefault(0.0f);
    fKnobCubic->setRotationAngle(270);
    fKnobCubic->setCallback(this);
    
    // knob Bit
    fKnobBit = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobBit->setId(DistoTVPlugin::paramBit);
    fKnobBit->setAbsolutePos(20, 220);
    fKnobBit->setRange(0.0f, 100.0f);
    fKnobBit->setDefault(0.0f);
    fKnobBit->setRotationAngle(270);
    fKnobBit->setCallback(this);

    //knob Tilt bits
    fKnobBitTilt = new ImageKnob(this, knobSmallImage);
    fKnobBitTilt->setId(DistoTVPlugin::paramTilt);
    fKnobBitTilt->setAbsolutePos(3, 204);
    fKnobBitTilt->setRange(0.0f, 190.0f);
    fKnobBitTilt->setDefault(0.0f);
    fKnobBitTilt->setRotationAngle(270);
    fKnobBitTilt->setCallback(this);
    
    // knob Dist
    fKnobDist = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobDist->setId(DistoTVPlugin::paramDist);
    fKnobDist->setAbsolutePos(20, 312);
    fKnobDist->setRange(0.0f, 100.0f);
    fKnobDist->setDefault(0.0f);
    fKnobDist->setRotationAngle(270);
    fKnobDist->setCallback(this);

    //knob PreAMP
    fKnobPreAMP = new ImageKnob(this, knobSmallImage);
    fKnobPreAMP->setId(DistoTVPlugin::paramPre);
    fKnobPreAMP->setAbsolutePos(3, 298);
    fKnobPreAMP->setRange(-14.0f, 14.0f);
    fKnobPreAMP->setDefault(0.0f);
    fKnobPreAMP->setRotationAngle(270);
    fKnobPreAMP->setCallback(this);
    
    // knob Master Volume
    fKnobMaster = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobMaster->setId(DistoTVPlugin::paramMaster);
    fKnobMaster->setAbsolutePos(20, 408);
    fKnobMaster->setRange(-48.0f, 6.0f);
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
    

    // drawing area
    fCanvasArea.setPos(130,195);
    fCanvasArea.setSize(AREAHEIGHT,AREAHEIGHT);
    for (int i = 0; i < AREAHEIGHT; i++
    ) {
        wave_y[i] = -(AREAHEIGHT*(atan(4.*i*M_PI/AREAHEIGHT)-2.0))/4.; // 95;
    }
    
    
    // set default values
    programLoaded(0);
}
//DistoTVUI::~DistoTVUI(){}

void DistoTVUI::stateChanged(const char* key, const char* value)
{
  //printf("Im here at StateChanged\n");
  
        if (strcmp(key, "waveform") == 0) {
	        char* tmp;
	        int i = 0;
	        char tmpbuf[4*AREAHEIGHT+1] = {0};
	        snprintf(tmpbuf, 4*AREAHEIGHT, "%s", value);
	        tmp = strtok(tmpbuf, " ");
	        while ((tmp != NULL) && (i < AREAHEIGHT)) {
	                wave_y[i] = AREAHEIGHT-((float)atoi(tmp));
	                i++;
	                //printf("%03d ", (int)wave_y[i]);
	                tmp = strtok(NULL, " ");
	        }
	} 
	repaint();
}


// -----------------------------------------------------------------------
// DSP Callbacks

void DistoTVUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case DistoTVPlugin::paramWet:
        fSliderWet->setValue(value);
        break;
    case DistoTVPlugin::paramTVNoise:
        fKnobTVNoise->setValue(value);
        break;   
    case DistoTVPlugin::paramBit:
        fKnobBit->setValue(value);
        break;  
    case DistoTVPlugin::paramDist:
        fKnobDist->setValue(value);
        break;
    case DistoTVPlugin::paramLow:
        fKnobLow->setValue(value);
        break;
    case DistoTVPlugin::paramMid:
        fKnobMid->setValue(value);
        break;
    case DistoTVPlugin::paramHigh:
        fKnobHigh->setValue(value);
        break;
    case DistoTVPlugin::paramCub:
        fKnobCubic->setValue(value);
        break;
    case DistoTVPlugin::paramTilt:
        fKnobBitTilt->setValue(value);
        break;
    case DistoTVPlugin::paramPre:
        fKnobPreAMP->setValue(value);
        break;
    case DistoTVPlugin::paramMaster:
        fKnobMaster->setValue(value);
        break;
    }
}

void DistoTVUI::programLoaded(uint32_t index)
{
    if (index == 0){

    // Default values
    fSliderWet->setValue(50000.0f);
    fKnobTVNoise->setValue(0.0f);
    fKnobBit->setValue(0.0f);
    fKnobDist->setValue(0.0f);
    fKnobLow->setValue(0.0f);
    fKnobMid->setValue(0.0f);
    fKnobHigh->setValue(0.0f);
    fKnobCubic->setValue(0.0f);
    fKnobBitTilt->setValue(0.0f);
    fKnobPreAMP->setValue(0.0f);
    fKnobMaster->setValue(0.0f);
    }

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
  {
    if (ev.button != 1)
        return false;

    if (ev.press)
    {
      //need to do if graph tab true
        if (! fCanvasArea.contains(ev.pos)) {
            //fDragValid = false;
            return false;
	}

        fDragging = true;
        fDragValid = true;
        return true;
    }
    else if (fDragging)
    {
        fDragging = false;
        return true;
    }

  return true;
  }
}
bool DistoTVUI::onMotion (const MotionEvent & ev) // this gets called when mouse is moving over the UI
{
  if (! fDragging)
        return false;
    if (! fDragValid)
    {
        fDragValid = true;
    }

    int x = ev.pos.getX();
    int y = ev.pos.getY();
 
    if (x > 320) x = 320;// outside right
    if (x < 130) x = 130;// outside left
    if (y > 385) y = 385;// outside bottom
    if (y < 195) y = 195;// outside top
  

    if (wave_y[x-130] != (y-195)) { // if wave_y is not the same as getY(), then update
        
        memset(fWaveState, 0, sizeof(fWaveState));// fill fWaveState whit 0
        

        for(int i = 0; i < AREAHEIGHT; i++) {
            char wavestr[5] = {0};
            snprintf(wavestr, sizeof(wavestr), "%03d ", (int) (fCanvasArea.getHeight()-wave_y[i]));
            strcat(fWaveState, wavestr);
        }

        wave_y[x-130] = y-195; // give wave_y the new value  <--- this one look a bit guilty

        fWaveUpdated = true; // then uiIdle() will setState()

        repaint();
    }


  return true;
}

void DistoTVUI::onNanoDisplay()
{
  fImgBackground.draw();
  
  
  //Line eye sugar
  glEnable(GL_BLEND);// blend the color with current pixel buffer
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);// draw lines whit filtering
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glLineWidth(2);
  

    
    
  //line loop
  int i;
      glColor4f(0.235f, 1.f, 0.235f, 1.0f);
      for (i = 1; i < AREAHEIGHT; ++i) {
          glBegin(GL_LINES);
                  glVertex2i(i-1+fCanvasArea.getX(), wave_y[i-1]+fCanvasArea.getY());
                  glVertex2i(i+fCanvasArea.getX(), wave_y[i]+fCanvasArea.getY());
          glEnd();
      }
      
  // reset color
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

}

void DistoTVUI::uiIdle()
{
    if (fWaveUpdated)
    {
        fWaveUpdated = false;
        setState("waveform", fWaveState);
    }

}
// -----------------------------------------------------------------------

UI* createUI()
{
    return new DistoTVUI();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
