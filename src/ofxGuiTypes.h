/*
 *  ofxGuiTypes.h
 *  openFrameworks
 *
 *  Copyright 2008 alphakanal/Stefan Kirch.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

//--------------------------------------------------------------
#include "ofxXmlSettings.h"
#include "ofxVectorMath.h"
#include "ofxDirList.h"

#include "ofMain.h"

//--------------------------------------------------------------
#define OFXGUI_VERSION			"0.2" //tentative versioning; bilderbuchi
#define OFXGUI_XML				"ofxGui.xml"

#define OFXGUI_PANEL_BORDER		10
#define OFXGUI_PANEL_SPACING	10

#define OFXGUI_BUTTON_HEIGHT	10
#define OFXGUI_BUTTON_WIDTH		10
#define OFXGUI_FILES_HEIGHT		15	
#define OFXGUI_SLIDER_HEIGHT	10
#define OFXGUI_COLOR_HEIGHT		30
#define OFXGUI_MATRIX_SPACING	 6

#define OFXGUI_STEPS			256



//--------------------------------------------------------------
static const char* kofxGui_Tags[] =
{
	"UI",			// kofxGui_Object_Base
	"PANEL",		// kofxGui_Object_Panel
	"SLIDER",		// kofxGui_Object_Slider
	"XYPAD",		// kofxGui_Object_XYPad
	"POINTS",		// kofxGui_Object_Points
	"BUTTON",		// kofxGui_Object_Button
	"FILES",		// kofxGui_Object_Files
	"COLOR",		// kofxGui_Object_Color
	"MATRIX",		// kofxGui_Object_Matrix
	"SCOPE",		// kofxGui_Object_Scope
	"KNOB",			// kofxGui_Object_Knob
	"RADAR",		// kofxGui_Object_Radar
	"SWITCH",		// kofxGui_Object_Switch
	
	"GALLERY",		// kofxGui_Object_Gallery
	"GALLERY_ITEM",	// kofxGui_Object_Gallery_Item
	
};

enum
{
	kofxGui_Object_Base,
	kofxGui_Object_Panel,
	kofxGui_Object_Slider,
	kofxGui_Object_XYPad,
	kofxGui_Object_Points,
	kofxGui_Object_Button,
	kofxGui_Object_Files,
	kofxGui_Object_Color,
	kofxGui_Object_Matrix,
	kofxGui_Object_Scope,
	kofxGui_Object_Knob,
	kofxGui_Object_Radar,
	kofxGui_Object_Switch,
	
	kofxGui_Object_Gallery,
	kofxGui_Object_Gallery_Item,
	
};

enum
{
	kofxGui_Display_Hex,
	kofxGui_Display_Int,
	kofxGui_Display_Float2,
	kofxGui_Display_Float4,
	kofxGui_Display_String,
};

enum
{
	kofxGui_Button_Off,
	kofxGui_Button_On,
	kofxGui_Button_Switch,
	kofxGui_Button_Trigger,
};

enum
{
	kofxGui_Color_RGB,
	kofxGui_Color_RGBA,
};

enum
{
	kofxGui_Matrix_Clear,
	kofxGui_Matrix_Set,
	kofxGui_Matrix_Selected,
};

enum ofxGuiTask
{
	kofxGui_Get_Bool,
	kofxGui_Get_Int,
	kofxGui_Get_Float,
	kofxGui_Get_Cell,
	kofxGui_Get_Point,
	kofxGui_Get_Color,
	kofxGui_Get_IntArray,
	kofxGui_Get_FloatArray,
	kofxGui_Get_String,
	
	kofxGui_Set_Bool,
	kofxGui_Set_Int,
	kofxGui_Set_Float,
	kofxGui_Set_Cell,
	kofxGui_Set_Point,
	kofxGui_Set_Color,
	kofxGui_Set_IntArray,
	kofxGui_Set_FloatArray,
	kofxGui_Set_String,
	kofxGui_Set_PointArray,
};


//--------------------------------------------------------------
static inline int roundInt(float value)
{
	return (int)(value + 0.5f);
}

static inline float linear(float fract, float x0, float x1)
{
	return x0 + (x1 - x0) * fract;
}

// -----------------------------------------------------------------------------

//class ofxGuiObject;

class ofxGuiListener
{ 
public:
	
	void setupGui(ofEventArgs & args){
		setupGui();
	}
	
	virtual void setupGui(){}
	virtual void handleGui(int parameterId, int task, void* data, int length){}
	//virtual void handleGui(ofxGuiObject* obj){};
};

// -----------------------------------------------------------------------------

class ofCell
{
public:
	
	int id;
	int value;

	ofCell()
	{ 
		id		= 0;
		value	= 0;
	}
	
	ofCell(int _id, int _value)
	{ 
		id		= _id;
		value	= _value;
	}
};



// -----------------------------------------------------------------------------

class ofRGBA
{
public:
	
	float r;
	float g;
	float b;
	float a;
	
	ofRGBA()
	{ 
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 1.0f;
	}
	
	ofRGBA(int rgba)
	{
		r = ((rgba >> 24) & 0xFF) / 255.0f;
		g = ((rgba >> 16) & 0xFF) / 255.0f;
		b = ((rgba >>  8) & 0xFF) / 255.0f;
		a = ((rgba >>  0) & 0xFF) / 255.0f;
	}
	
	ofRGBA(string hex)
	{
		int rgba;
		sscanf(hex.c_str(), "%x", &rgba);
		
		r = ((rgba >> 24) & 0xFF) / 255.0f;
		g = ((rgba >> 16) & 0xFF) / 255.0f;
		b = ((rgba >>  8) & 0xFF) / 255.0f;
		a = ((rgba >>  0) & 0xFF) / 255.0f;
	}
	
	ofRGBA(int _r, int _g, int _b, int _a)
	{
		r = (float)_r / 255.0f; r = MAX(0.0f, MIN(r, 1.0f));
		g = (float)_g / 255.0f; g = MAX(0.0f, MIN(g, 1.0f));
		b = (float)_b / 255.0f; b = MAX(0.0f, MIN(b, 1.0f));
		a = (float)_a / 255.0f; a = MAX(0.0f, MIN(a, 1.0f));
	}

	ofRGBA(float _r, float _g, float _b, float _a)
	{
		r = _r; r = MAX(0.0f, MIN(r, 1.0f));
		g = _g; g = MAX(0.0f, MIN(g, 1.0f));
		b = _b; b = MAX(0.0f, MIN(b, 1.0f));
		a = _a; a = MAX(0.0f, MIN(a, 1.0f));
	}
	
	void setChanel(int chanel, float value)
	{
		switch (chanel)
		{
			case 0:
				r = value;
				break;
			case 1:
				g = value;
				break;
			case 2:
				b = value;
				break;
			case 3:
				a = value;
				break;
		}
	}

	int toInt(int mode)
	{		
		int red		= roundInt(r * 255.0f) & 0xFF;
		int green	= roundInt(g * 255.0f) & 0xFF;
		int blue	= roundInt(b * 255.0f) & 0xFF;
		int alpha	= roundInt(a * 255.0f) & 0xFF;
		
		int value	= 0;
		
		if(mode == kofxGui_Color_RGB)
			value = (red << 16) | (green << 8) | (blue << 0);
		else if(mode == kofxGui_Color_RGBA)
			value = (red << 24) | (green << 16) | (blue << 8) | (alpha << 0);
		
		return value;
	}

	string toString(int mode)
	{
		char hex[9];
		
		int red		= roundInt(r * 255.0f);
		int green	= roundInt(g * 255.0f);
		int blue	= roundInt(b * 255.0f);
		int alpha	= roundInt(a * 255.0f);
		
		if(mode == kofxGui_Color_RGB)
			sprintf(hex, "%.2X%.2X%.2X", red, green, blue);
		else if(mode == kofxGui_Color_RGBA)
			sprintf(hex, "%.2X%.2X%.2X%.2X", red, green, blue, alpha);
		
		return hex;
	}
}; 

// -----------------------------------------------------------------------------

class ofPointList
{		
public:
	
	int		activePoint;
	vector	<ofxPoint2f> points;
	
	ofPointList()
	{
		activePoint	= -1;
	}
		
	void addPointAtPosition(ofxPoint2f p)
	{
		for(int i = 1; i < points.size(); i++)
		{
			ofxPoint2f	prev	= points.at(i - 1);
			ofxPoint2f	next	= points.at(i);
			
			if(p.x >= prev.x && p.x <= next.x)
			{
				points.insert(points.begin() + i, p);
				break;
			}
		}
	}
	
	void deleteActivePoint()
	{
		if(activePoint > 0 && activePoint < points.size() - 1)
			points.erase(points.begin() + activePoint);
	}

	ofxPoint2f positionToValue(ofxPoint2f p)
	{
		ofxPoint2f value = p;
		
		for(int i = 1; i < points.size(); i++)
		{
			ofxPoint2f	prev	= points.at(i - 1);
			ofxPoint2f	next	= points.at(i);
			
			if(p.x >= prev.x && p.x <= next.x)
			{
				float fraction = (p.x - prev.x) / (next.x - prev.x);
				value.y = linear(fraction, prev.y, next.y);
				
				break;
			}
		}
		
		return value;
	}
};

//--------------------------------------------------------------

