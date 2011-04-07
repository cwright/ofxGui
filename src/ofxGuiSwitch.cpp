/*
 *  ofxGuiSwitch.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiSwitch.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiSwitch::ofxGuiSwitch()
{
	mParamType = kofxGui_Object_Switch;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiSwitch::init(/*int id,*/ string name, int x, int y, int width, int height, int min, int max, int value, const string* paramStrings)
{
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;
	
	//mParamId		= id;
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mObjWidth		= width;
	mObjHeight		= textHeight + height;
	
	mSteps			= (max - min) + 1;
	
	if (paramStrings != NULL)
	{
		for (int i = 0; i < mSteps; i++)
			mParamStrings.push_back(paramStrings[i]);
	}
	
	setRange(min, max);
	setValue(value);
	setControlRegion(0, textHeight, width, height);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiSwitch::setValue(int value)
{

		if (mDisplay == kofxGui_Display_String && value != mValue)
		{
			int id = (int)value;
			//mGlobals->mListener->handleGui(mParamId, kofxGui_Get_String, &id, sizeof(int));
		}
	mValue = value;	
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiSwitch::setRange(int min, int max) 
{
	mMinVal	= min;
	mMaxVal	= max;
	mValDlt	= mMaxVal - mMinVal;
}

//	----------------------------------------------------------------------------------------------------

/*
bool ofxGuiSwitch::update(int id, int task, void* data, int length)
{
	bool handled = false;
	
	if(id == mParamId)
	{
		if(task == kofxGui_Set_Int)
			setValue(*(int*)data);
		else if(task == kofxGui_Set_String)
			mDisplaySting = *(string*)data;		
		handled = true;
	}
	
	return handled;
}
 */

//	----------------------------------------------------------------------------------------------------

void ofxGuiSwitch::draw()
{
	glPushMatrix();
	
	glTranslatef(mObjX, mObjY, 0.0);
	
	if(mParamName != "")
	{
		if (mDisplay == kofxGui_Display_String && mSteps > 1){
			drawParamString(0.0, 0.0, mParamName + ": " + mDisplaySting, false);
		}
		    
		else{
		if(mParamStrings.size() > 0)
			drawParamString(0.0, 0.0, mParamName + ": " + mParamStrings.at(mValue - mMinVal), false);
		else
			drawParamString(0.0, 0.0, mParamName + ": " + ofToString(mValue), false);
		}
	}
	
//	Original version
//	if(mParamName != "")
//	{
//		if(mParamStrings.size() > 0)
//			drawParamString(0.0, 0.0, mParamName + ": " + mParamStrings.at(mValue - mMinVal), false);
//		else
//			drawParamString(0.0, 0.0, mParamName + ": " + ofToString(mValue), false);
//	}
	
	float	w = mCtrWidth / (mValDlt + 1);
	float	x = mValue * w;
	
	ofFill();
	
	//	background
	glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	//	handle
	glColor4f(mGlobals->mSliderColor.r, mGlobals->mSliderColor.g, mGlobals->mSliderColor.b, mGlobals->mSliderColor.a);
	ofRect(x, mCtrY, w, mCtrHeight);
	
	ofNoFill();

	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	ofRect(x, mCtrY, w, mCtrHeight);
	
	//	frame
	glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
}
//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiFiles::mouseMoved(int x, int y)
{
	return NULL;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiSwitch::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown)
	{
		int value = fractionToValue(mouseToFraction(mouseToLocal(x, y)).x);
		
		if(value != mValue)
		{
			setValue(value);
			//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Int, &mValue, sizeof(int));
		}
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiSwitch::mousePressed(int x, int y, int button)
{
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));
	
	if (mMouseIsDown)
		mouseDragged(x, y, button);
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiSwitch::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
		mMouseIsDown = false;
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiSwitch::keyPressed(int key){ cout << "Keypress unimplemented." << endl; }

//	----------------------------------------------------------------------------------------------------

bool ofxGuiSwitch::keyReleased(int key){ cout << "Keypress unimplemented." << endl; }

//	----------------------------------------------------------------------------------------------------

void ofxGuiSwitch::buildFromXml()
{
	int numberOfTags = mGlobals->mXml.getNumTags("STRING");
	
	if(numberOfTags > 0)
	{		
		mParamStrings.clear();
		
		for(int i = 0; i < numberOfTags; i++)
		{
			mGlobals->mXml.pushTag("STRING", i);

			int		value	= mGlobals->mXml.getValue("VALUE", 0);
			string	text	= mGlobals->mXml.getValue("TEXT", ofToString(value));
			
			mParamStrings.push_back(text); 

			mGlobals->mXml.popTag();
		}
	}
	
	//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Int, &mValue, sizeof(int));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiSwitch::saveToXml()
{
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:MIN", mMinVal, id);
	mGlobals->mXml.setValue("OBJECT:MAX", mMaxVal, id);
	mGlobals->mXml.setValue("OBJECT:VALUE", mValue, id);
	
	mGlobals->mXml.pushTag("OBJECT", id);

	for(int i = 0; i < mParamStrings.size(); i++)
	{
		string s = mParamStrings.at(i);				

		id = mGlobals->mXml.addTag("STRING");
		
		mGlobals->mXml.setValue("STRING:VALUE", mMinVal + i, id);
		mGlobals->mXml.setValue("STRING:TEXT", s, id);
	}

	mGlobals->mXml.popTag();
}

//	----------------------------------------------------------------------------------------------------

int ofxGuiSwitch::fractionToValue(float fraction)
{
	return roundInt((mValDlt * fraction) + mMinVal);
}
//	----------------------------------------------------------------------------------------------------
