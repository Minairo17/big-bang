#pragma once

#include "ofMain.h"
#include "ofApp.h"


#include "ofxHistoryPlot.h"

class PlotApp_ex: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void setupPlots();

	shared_ptr<ofApp> mainApp;

	map<std::string, ofxHistoryPlot *> plotsMap;

    map<std::string, int> numParticles;
	ofJson plotParticles;

	PlotApp_ex(shared_ptr<ofApp> mainApp);
};