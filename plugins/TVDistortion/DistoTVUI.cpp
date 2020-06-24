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
    
    // Image data
    Image sliderImage(Art::sliderData, Art::sliderWidth, Art::sliderHeight);
    Image knobImage(Art::knobData, Art::knobWidth, Art::knobHeight);
    Image knobSmallImage(Art::knobSmallData, Art::knobSmallWidth, Art::knobSmallHeight);
    Image scaleImage(DistoTVArtwork::scaleData, DistoTVArtwork::scaleWidth, DistoTVArtwork::scaleHeight);
    Image interpolationImage(DistoTVArtwork::interpolationData, DistoTVArtwork::interpolationWidth, DistoTVArtwork::interpolationHeight);
    Image amp_typeImage(DistoTVArtwork::amp_typeData, DistoTVArtwork::amp_typeWidth, DistoTVArtwork::amp_typeHeight);
    Image Button_offImageSmall(Art::button_offSmallData, Art::button_offSmallWidth, Art::button_offSmallHeight);
    Image Button_onImageSmall(Art::button_onSmallData, Art::button_onSmallWidth, Art::button_onSmallHeight);
    

    
    // Wet slider
    fSliderWet = new ImageSlider(this, sliderImage);
    fSliderWet->setId(DistoTVPlugin::paramWet);
    fSliderWet->setInverted(false); //not sure
    fSliderWet->setStartPos(7,1);
    fSliderWet->setEndPos(1000,1);
    fSliderWet->setRange(1.0f, 2.0f);
    fSliderWet->setDefault(1.5f);
    fSliderWet->setCallback(this);

    
    // knob Dist
    fKnobDist = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobDist->setId(DistoTVPlugin::paramDist);
    fKnobDist->setAbsolutePos(720, 335);
    fKnobDist->setRange(0.0f, 100.0f);
    fKnobDist->setDefault(0.0f);
    fKnobDist->setRotationAngle(270);
    fKnobDist->setCallback(this);

    //knob PreAMP
    fKnobPreAMP = new ImageKnob(this, knobSmallImage);
    fKnobPreAMP->setId(DistoTVPlugin::paramPre);
    fKnobPreAMP->setAbsolutePos(680, 330);
    fKnobPreAMP->setRange(-14.0f, 48.0f);
    fKnobPreAMP->setDefault(0.0f);
    fKnobPreAMP->setRotationAngle(270);
    fKnobPreAMP->setCallback(this);
    
    //knob Low filter
    fKnobLow = new ImageKnob(this, knobSmallImage);
    fKnobLow->setId(DistoTVPlugin::paramLow);
    fKnobLow->setAbsolutePos(840, 330);
    fKnobLow->setRange(-24.0f, 24.0f);
    fKnobLow->setDefault(0.0f);
    fKnobLow->setRotationAngle(270);
    fKnobLow->setCallback(this);
   
    // Switch sliders
    
    fSliderAmpType = new ImageSlider(this, amp_typeImage);
    fSliderAmpType->setId(DistoTVPlugin::paramAmpType);
    fSliderAmpType->setStartPos(400,330);
    fSliderAmpType->setEndPos(400,385);
    fSliderAmpType->setRange(1.0f, 3.0f);
    fSliderAmpType->setStep(1.0f);
    fSliderAmpType->setDefault(1.0f);
    fSliderAmpType->setCallback(this);
    

    fSliderInterpolation = new ImageSlider(this, interpolationImage);
    fSliderInterpolation->setId(DistoTVPlugin::paramInterpolation);
    fSliderInterpolation->setStartPos(300,330);
    fSliderInterpolation->setEndPos(300,385);
    fSliderInterpolation->setRange(1.0f, 3.0f);
    fSliderInterpolation->setStep(1.0f);
    fSliderInterpolation->setDefault(1.0f);
    fSliderInterpolation->setCallback(this);
    
    fSliderScale = new ImageSlider(this, scaleImage);
    fSliderScale->setId(DistoTVPlugin::paramScale);
    fSliderScale->setStartPos(200,330);
    fSliderScale->setEndPos(200,385);
    fSliderScale->setRange(0.0f, 9.0f);
    fSliderScale->setStep(1.0f);
    fSliderScale->setDefault(0.0f);
    fSliderScale->setCallback(this);

    
    fSwitchCrossres = new ImageSwitch(this, Button_offImageSmall, Button_onImageSmall);
    fSwitchCrossres->setId(DistoTVPlugin::paramCrossres);
    fSwitchCrossres->setAbsolutePos(100, 350);
    fSwitchCrossres->setCallback(this);
    fSwitchCrossres->setDown(false); 
    
    fSwitchMouseSM = new ImageSwitch(this, Button_offImageSmall, Button_onImageSmall);
    fSwitchMouseSM->setId(DistoTVPlugin::paramMouseSM);
    fSwitchMouseSM->setAbsolutePos(150, 350);
    fSwitchMouseSM->setCallback(this);
    fSwitchMouseSM->setDown(false); 

    //knob Mid filter
    fKnobMid = new ImageKnob(this, knobSmallImage);
    fKnobMid->setAbsolutePos(860, 350);
    fKnobMid->setId(DistoTVPlugin::paramMid);
    fKnobMid->setRange(-24.0f, 24.0f);
    fKnobMid->setDefault(0.0f);
    fKnobMid->setRotationAngle(270);
    fKnobMid->setCallback(this);
    
    //knob High filter
    fKnobHigh = new ImageKnob(this, knobSmallImage);
    fKnobHigh->setId(DistoTVPlugin::paramHigh);
    fKnobHigh->setAbsolutePos(880, 370);
    fKnobHigh->setRange(-24.0f, 24.0f);
    fKnobHigh->setDefault(0.0f);
    fKnobHigh->setRotationAngle(270);
    fKnobHigh->setCallback(this);
    
    // knob Master Volume
    fKnobMaster = new ImageKnob(this, knobImage, ImageKnob::Vertical);
    fKnobMaster->setId(DistoTVPlugin::paramMaster);
    fKnobMaster->setAbsolutePos(775, 335);
    fKnobMaster->setRange(-48.0f, 6.0f);
    fKnobMaster->setDefault(0.0f);
    fKnobMaster->setRotationAngle(270);
    fKnobMaster->setCallback(this);
    
    
    // drawing area
    fCanvasArea.setPos(12,30);
    fCanvasArea.setSize(AREALENGTH,AREAHEIGHT);
    for (int i = 0; i < AREALENGTH; i++
    ) {
        UI_wave_y_Pixels[i] = 151;
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
	        char tmpbuf[4*AREALENGTH+1] = {0};
	        snprintf(tmpbuf, 4*AREALENGTH, "%s", value);
	        tmp = strtok(tmpbuf, " ");
	        while ((tmp != NULL) && (i < AREALENGTH)) {
	                UI_wave_y_Pixels[i] = 301-((float)atoi(tmp));
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
    case DistoTVPlugin::paramDist:
        fKnobDist->setValue(value);
        break;
    case DistoTVPlugin::paramPre:
        fKnobPreAMP->setValue(value);
        break;
    case DistoTVPlugin::paramAmpType:
        fSliderAmpType->setValue(value);
        break;
    case DistoTVPlugin::paramInterpolation:
        fSliderInterpolation->setValue(value);
        break;
    case DistoTVPlugin::paramScale:
        fSliderScale->setValue(value);
        break;
    case DistoTVPlugin::paramCrossres:
        fSwitchCrossres->setDown(value);
        break;
    case DistoTVPlugin::paramMouseSM:
        fSwitchMouseSM->setDown(value);
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
    case DistoTVPlugin::paramMaster:
        fKnobMaster->setValue(value);
        break;
    }
}

void DistoTVUI::programLoaded(uint32_t index)
{
    if (index == 0){

    // Default values
    fSliderWet->setValue(1.5f);
    fKnobDist->setValue(0.0f);
    fKnobPreAMP->setValue(0.0f);
    fSliderAmpType->setValue(1.0f);
    fSliderInterpolation->setValue(1.0f);
    fSliderScale->setValue(0.0f);
    fSwitchCrossres->setDown(false);
    fSwitchMouseSM->setDown(false);
    fKnobLow->setValue(0.0f);
    fKnobMid->setValue(0.0f);
    fKnobHigh->setValue(0.0f);
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
    //if( slider == fSliderAmpType)
    //setParameterValue(slider->getId()+3, value);
    //if( slider == fSliderInterpolation)
    //setParameterValue(slider->getId()+4, value);
    //if( slider == fSliderScale)
    //setParameterValue(slider->getId()+5, value);
    //if( slider == fSliderWet)
    //setParameterValue(slider->getId(), value);
    setParameterValue(slider->getId(), value);
}

void DistoTVUI::imageSwitchClicked(ImageSwitch* tog, bool down)
{
   //if( tog == fSwitchCrossres )
   //setParameterValue(tog->getId()+6, down ? 1.f : 0.f); //heres is a bug (+6 fix)
   //if( tog == fSwitchMouseSM ) 
   setParameterValue(tog->getId(), down ? 1.f : 0.f);
   //if (tog == fSwitchMouseSM)
   //fBoolMouseSM = down;

}

bool DistoTVUI::onMouse(const MouseEvent & ev) // this gets called when the mouse is presse, released.
{
    if (ev.button != 1)
    return false;

    if (ev.press)
    {
        if (! fCanvasArea.contains(ev.pos)) { return false;}

        fDragging = true;
        
	int x = ev.pos.getX();
        int y = ev.pos.getY();

        if (UI_wave_y_Pixels[x-12] != (y-30)) { // if UI_wave_y_Pixels[x] is not the same as getY(), then update 
            
	    UI_wave_y_Pixels[x-12] = y-30;
	
            memset(fWaveState, 0, sizeof(fWaveState));// fill fWaveState whit 0
        
            for(int i = 0; i < AREALENGTH; i++) {
                char wavestr[5] = {0};
                snprintf(wavestr, sizeof(wavestr), "%03d ", (int) (fCanvasArea.getHeight()-UI_wave_y_Pixels[i]));
                strcat(fWaveState, wavestr);
            }


        fWaveUpdated = true; // then uiIdle() will setState()

        repaint();
	tmpX = x-12;
	tmpY = y-30;

    }
    }
    if (ev.press == false)
    {
         fDragging = false;
	 return true;
    }
    return true;
}
bool DistoTVUI::onMotion(const MotionEvent & ev) // this gets called when mouse is moving over the UI
{
    if (fDragging)
    {
    
    int x = ev.pos.getX();
    int y = ev.pos.getY();
 
    if (x > 1012) x = 1012;// outside right
    if (x < 12) x = 12;// outside left
    if (y > 331) y = 331;// outside bottom
    if (y < 30) y = 30;// outside top
  

    if (UI_wave_y_Pixels[x-12] != (y-30)) { // if UI_wave_y_Pixels[x] is not the same as getY(), then update
        
        memset(fWaveState, 0, sizeof(fWaveState));// fill fWaveState whit 0
        
        
	if (fSwitchMouseSM->isDown() == true){
	    //code for MouseSM
	    //printf("Im here MouseSM\n");
            
	    float numbers = abs(tmpX-(x-12));

            float divider = 1.0/numbers;
            float printnum;
    
            for (int i = 1; i < numbers+1; i++){
                 printnum = ((y-30)-tmpY)*divider*i;
                 if (tmpX < (x-12)){
                    UI_wave_y_Pixels[/*får inte gå över*/i-1+tmpX] = tmpY + (int)nearbyint(printnum);
                 }
                 else{
                    UI_wave_y_Pixels[/*får inte gå över*/tmpX-i] = tmpY + (int)nearbyint(printnum); 
                 }
             }
	    
	     
            
	} else UI_wave_y_Pixels[x-12] = y-30; // dot painting
	  
	tmpX = x-12;
	tmpY = y-30;


        for(int i = 0; i < AREALENGTH; i++) {
            char wavestr[5] = {0};
            snprintf(wavestr, sizeof(wavestr), "%03d ", (int) (fCanvasArea.getHeight()-UI_wave_y_Pixels[i]));
            strcat(fWaveState, wavestr);
        }


        fWaveUpdated = true; // then uiIdle() will setState()

        repaint();
        }
    }

  return true;
}

void DistoTVUI::onDisplay()
{
    fImgBackground.draw();
  
    //OpenGL
    glEnable(GL_BLEND);    // blend the color with current pixel buffer
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);    // draw lines whit filtering
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2);
    
    int i;
    glColor4f(0.235f, 1.f, 0.235f, 1.0f);
    for (i = 1; i < AREALENGTH; ++i) {
        glBegin(GL_LINES);
        glVertex2i(i-1+fCanvasArea.getX(), UI_wave_y_Pixels[i-1]+fCanvasArea.getY());
        glVertex2i(i+fCanvasArea.getX(), UI_wave_y_Pixels[i]+fCanvasArea.getY());
        glEnd();
    }   
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
