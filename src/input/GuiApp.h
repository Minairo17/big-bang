#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp: public ofBaseApp {
public:

	void setup();
	void update();
	void draw();

	ofParameterGroup parameters;
	ofParameter<double> energy;
	ofParameter<bool> interactions;
	ofParameter<bool> gravity;
	ofParameter<double> sigma;
	ofxButton reset;
	ofxPanel gui;

	ofxFloatSlider scale;
	ofxFloatSlider thresh;
	ofxFloatSlider brightness;

	double mappedradius;


	ofJson settings;
};