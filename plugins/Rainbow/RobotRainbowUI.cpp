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

#include "RobotRainbowPlugin.hpp"
#include "RobotRainbowUI.hpp"

namespace Art = RobotRainbowArtwork;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

RainbowUI::RainbowUI()
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

    fKnobRed = new ImageKnob(this, knobImage);
    fKnobRed->setId(parameterRed);
    fKnobRed->setAbsolutePos(241,210);
    fKnobRed->setRange(0.0, 100.0);
    fKnobRed->setDefault(0.0);
    fKnobRed->setRotationAngle(330);
    fKnobRed->setCallback(this);

    fKnobOrange = new ImageKnob(this, knobImage);
    fKnobOrange->setId(parameterOrange);
    fKnobOrange->setAbsolutePos(266,210);
    fKnobOrange->setRange(0.0, 100.0);
    fKnobOrange->setDefault(0.0);
    fKnobOrange->setRotationAngle(330);
    fKnobOrange->setCallback(this);

    fKnobYellow = new ImageKnob(this, knobImage);
    fKnobYellow->setId(parameterOrange);
    fKnobYellow->setAbsolutePos(291,210);
    fKnobYellow->setRange(0.0, 100.0);
    fKnobYellow->setDefault(0.0);
    fKnobYellow->setRotationAngle(330);
    fKnobYellow->setCallback(this);

    fKnobGreen = new ImageKnob(this, knobImage);
    fKnobGreen->setId(parameterOrange);
    fKnobGreen->setAbsolutePos(316,210);
    fKnobGreen->setRange(0.0, 100.0);
    fKnobGreen->setDefault(0.0);
    fKnobGreen->setRotationAngle(330);
    fKnobGreen->setCallback(this);

    fKnobBlue = new ImageKnob(this, knobImage);
    fKnobBlue->setId(parameterOrange);
    fKnobBlue->setAbsolutePos(341,210);
    fKnobBlue->setRange(0.0, 100.0);
    fKnobBlue->setDefault(0.0);
    fKnobBlue->setRotationAngle(330);
    fKnobBlue->setCallback(this);

    fKnobIndigo = new ImageKnob(this, knobImage);
    fKnobIndigo->setId(parameterOrange);
    fKnobIndigo->setAbsolutePos(366,210);
    fKnobIndigo->setRange(0.0, 100.0);
    fKnobIndigo->setDefault(0.0);
    fKnobIndigo->setRotationAngle(330);
    fKnobIndigo->setCallback(this);

    fKnobViolet = new ImageKnob(this, knobImage);
    fKnobViolet->setId(parameterOrange);
    fKnobViolet->setAbsolutePos(391,210);
    fKnobViolet->setRange(0.0, 100.0);
    fKnobViolet->setDefault(0.0);
    fKnobViolet->setRotationAngle(330);
    fKnobViolet->setCallback(this);


    programLoaded(0);

    //repaint();
}

void RainbowUI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
        case parameterWet:
	    fKnobWet->setValue(value);
	    break;
	case parameterRed:
	    fKnobRed->setValue(value);
	    break;
	case parameterOrange:
	    fKnobOrange->setValue(value);
	    break;
	case parameterYellow:
	    fKnobYellow->setValue(value);
	    break;
	case parameterGreen:
	    fKnobGreen->setValue(value);
	    break;
	case parameterBlue:
	    fKnobBlue->setValue(value);
	    break;
	case parameterIndigo:
	    fKnobIndigo->setValue(value);
	    break;
	case parameterViolet:
	    fKnobViolet->setValue(value);
	    break;
    }
}

void RainbowUI::programLoaded(uint32_t index)
{
    switch (index)
    {
        case 0:
	    fKnobWet->setValue(0.0f);
	    fKnobRed->setValue(0.0f);
	    fKnobOrange->setValue(0.0f);
	    fKnobYellow->setValue(0.0f);
	    fKnobGreen->setValue(0.0f);
	    fKnobBlue->setValue(0.0f);
	    fKnobIndigo->setValue(0.0f);
	    fKnobViolet->setValue(0.0f);
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
  

    //Rainbow
    //
    // I think I have to write 1 pixel lines in a horizontal way that 
    // will fad out at the rims of each rainbow color. the amount of
    // each parameter will effect how strong the color display
    //

    // Default
    //glShadeModel(GL_FLAT);
   
    //glDisable(GL_DITHER);
    //glDisable(GL_LINE_SMOOTH);
    //glHint(GL_LINE_SMOOTH, GL_DONT_CARE);
    //#define GL_MULTISAMPLE_ARB 0x809D
    //printf("%s\n", glGetString(GL_VERSION));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);    // draw lines with filtering
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.0f);
    //glDisable( GL_MULTISAMPLE_ARB) ;
   
   
    int i;
    int cokeLines = 0;

    for (i = 0; i < fKnobRed->getValue(); ++i) {
       glColor4f(1.0f, 0.0f, 0.0f, 0.14285714f);
       glBegin(GL_LINES);
	   if (i==0||i==11||i ==23||i==39||i==53||i==68||i==84){
               glEnd();
	       cokeLines = 0;
	       glBegin(GL_TRIANGLES);
               glVertex2i(0, 10);
               glVertex2i(416, 10);
               glVertex2i(416, 18);
               glVertex2i(0, 10);
               glVertex2i(0, 18);
               glVertex2i(416, 18);
	       glEnd();
	       glBegin(GL_LINES);
	   }
	   glVertex2i(0, 10-cokeLines); // grow line above first line
	   glVertex2i(416, 10-cokeLines);
	   glVertex2i(0, 19+cokeLines); // grow line below
	   glVertex2i(416, 19+cokeLines);
	   cokeLines++; 
           glEnd();
    }
    
    for (i = 0; i < fKnobOrange->getValue(); ++i) {
       glColor4f(1.0f, 0.65f, 0.0f, 0.14285714f);
       glBegin(GL_LINES);
	   if (i==0||i==11||i ==23||i==39||i==53||i==68||i==84){
               glEnd();
	       cokeLines = 0;
	       glBegin(GL_TRIANGLES);
               glVertex2i(0, 10+30);
               glVertex2i(416, 10+30);
               glVertex2i(416, 18+30);
               glVertex2i(0, 10+30);
               glVertex2i(0, 18+30);
               glVertex2i(416, 18+30);
	       glEnd();
	       glBegin(GL_LINES);
	   }
	   glVertex2i(0, 10+30-cokeLines); // grow line above first line
	   glVertex2i(416, 10+30-cokeLines);
	   glVertex2i(0, 19+30+cokeLines); // grow line below
	   glVertex2i(416, 19+30+cokeLines);
	   cokeLines++; 
           glEnd();
    }

    for (i = 0; i < fKnobYellow->getValue(); ++i) {
       glColor4f(1.0f, 1.0f, 0.0f, 0.14285714f);
       glBegin(GL_LINES);
	   if (i==0||i==11||i ==23||i==39||i==53||i==68||i==84){
               glEnd();
	       cokeLines = 0;
	       glBegin(GL_TRIANGLES);
               glVertex2i(0, 10+60);
               glVertex2i(416, 10+60);
               glVertex2i(416, 18+60);
               glVertex2i(0, 10+60);
               glVertex2i(0, 18+60);
               glVertex2i(416, 18+60);
	       glEnd();
	       glBegin(GL_LINES);
	   }
	   glVertex2i(0, 10+60-cokeLines); // grow line above first line
	   glVertex2i(416, 10+60-cokeLines);
	   glVertex2i(0, 19+60+cokeLines); // grow line below
	   glVertex2i(416, 19+60+cokeLines);
	   cokeLines++; 
           glEnd();
    }

    for (i = 0; i < fKnobGreen->getValue(); ++i) {
       glColor4f(0.33f, 1.0f, 0.0f, 0.14285714f);
       glBegin(GL_LINES);
	   if (i==0||i==11||i ==23||i==39||i==53||i==68||i==84){
               glEnd();
	       cokeLines = 0;
	       glBegin(GL_TRIANGLES);
               glVertex2i(0, 10+90);
               glVertex2i(416, 10+90);
               glVertex2i(416, 18+90);
               glVertex2i(0, 10+90);
               glVertex2i(0, 18+90);
               glVertex2i(416, 18+90);
	       glEnd();
	       glBegin(GL_LINES);
	   }
	   glVertex2i(0, 10+90-cokeLines); // grow line above first line
	   glVertex2i(416, 10+90-cokeLines);
	   glVertex2i(0, 19+90+cokeLines); // grow line below
	   glVertex2i(416, 19+90+cokeLines);
	   cokeLines++; 
           glEnd();
    }

    for (i = 0; i < fKnobBlue->getValue(); ++i) {
       glColor4f(0.0f, 0.0f, 1.0f, 0.14285714f);
       glBegin(GL_LINES);
	   if (i==0||i==11||i ==23||i==39||i==53||i==68||i==84){
               glEnd();
	       cokeLines = 0;
	       glBegin(GL_TRIANGLES);
               glVertex2i(0, 10+120);
               glVertex2i(416, 10+120);
               glVertex2i(416, 18+120);
               glVertex2i(0, 10+120);
               glVertex2i(0, 18+120);
               glVertex2i(416, 18+120);
	       glEnd();
	       glBegin(GL_LINES);
	   }
	   glVertex2i(0, 10+120-cokeLines); // grow line above first line
	   glVertex2i(416, 10+120-cokeLines);
	   glVertex2i(0, 19+120+cokeLines); // grow line below
	   glVertex2i(416, 19+120+cokeLines);
	   cokeLines++; 
           glEnd();
    }

    for (i = 0; i < fKnobIndigo->getValue(); ++i) {
       glColor4f(0.44f, 0.0f, 1.0f, 0.14285714f);
       glBegin(GL_LINES);
	   if (i==0||i==11||i ==23||i==39||i==53||i==68||i==84){
               glEnd();
	       cokeLines = 0;
	       glBegin(GL_TRIANGLES);
               glVertex2i(0, 10+150);
               glVertex2i(416, 10+150);
               glVertex2i(416, 18+150);
               glVertex2i(0, 10+150);
               glVertex2i(0, 18+150);
               glVertex2i(416, 18+150);
	       glEnd();
	       glBegin(GL_LINES);
	   }
	   glVertex2i(0, 10+150-cokeLines); // grow line above first line
	   glVertex2i(416, 10+150-cokeLines);
	   glVertex2i(0, 19+150+cokeLines); // grow line below
	   glVertex2i(416, 19+150+cokeLines);
	   cokeLines++; 
           glEnd();
    }

    for (i = 0; i < fKnobViolet->getValue(); ++i) {
       glColor4f(0.56f, 0.0f, 1.0f, 0.14285714f);
       glBegin(GL_LINES);
	   if (i==0||i==11||i ==23||i==39||i==53||i==68||i==84){
               glEnd();
	       cokeLines = 0;
	       glBegin(GL_TRIANGLES);
               glVertex2i(0, 10+180);
               glVertex2i(416, 10+180);
               glVertex2i(416, 18+180);
               glVertex2i(0, 10+180);
               glVertex2i(0, 18+180);
               glVertex2i(416, 18+180);
	       glEnd();
	       glBegin(GL_LINES);
	   }
	   glVertex2i(0, 10+180-cokeLines); // grow line above first line
	   glVertex2i(416, 10+180-cokeLines);
	   glVertex2i(0, 19+180+cokeLines); // grow line below
	   glVertex2i(416, 19+180+cokeLines);
	   cokeLines++; 
           glEnd();
    }

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    //glEnable(GL_MULTISAMPLE_ARB);
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new RainbowUI();
}

END_NAMESPACE_DISTRHO

