#pragma once

#include "ofMain.h"
#include "ofApp.h"

#include "ofxGraph.h"

class PlotApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	shared_ptr<ofApp> mainApp;

	ofxGraph graph;
	ofxGraph graph2;
	ofxGraph graph3;
	ofxGraph graph4;

	PlotApp(shared_ptr<ofApp> mainApp);
};