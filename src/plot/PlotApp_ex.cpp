#include "PlotApp_ex.h"

PlotApp_ex::PlotApp_ex(shared_ptr<ofApp> _mainApp){
	mainApp= _mainApp;
	plotParticles = mainApp->inputManager->dataManager->settings["plotParticles"];

	ofLog()<<"PlotApp Constructor";
}

void PlotApp_ex::setup(){

    ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(22, 22, 22, 255);

   	setupPlots();
	ofLog()<<"Ready from PlotApp_ex";
}


void PlotApp_ex::update(){

	for (auto plot : plotsMap) {
		plot.second->update(mainApp->universeManager->statisticsManager->numParticles[plot.first]);
	}
}

void PlotApp_ex::draw(){
	int counter = 0;
	for (auto plot : plotsMap) {
		plot.second->draw(10, 10+counter*100, 800, 100);
		counter++;
	}
}

void PlotApp_ex::setupPlots(){
	int numSamples = 350;

	for(const string &particle_name : plotParticles){
		//auto color = ofHexToInt(bigbang->constants["particles"][particle_name]["settings"]["color"]);

		ofxHistoryPlot *plot = new ofxHistoryPlot( NULL, particle_name, numSamples, false); //NULL cos we don't want it to auto-update. confirmed by "true"
		//plot->setLowerRange(0); //set only the lowest part of the range upper is adaptative to curve
		plot->setAutoRangeShrinksBack(true); //plot scale can shrink back after growing if plot curves requires it
		plot->setColor( ofColor(255,0,255) );
		plot->setShowNumericalInfo(true);
		plot->setRespectBorders(true);
		plot->setLineWidth(1);
		plot->setDrawFromRight(true);

		plot->setShowSmoothedCurve(true); //plot a smoothed version of the values, but alos the original in lesser alpha
		plot->setSmoothFilter(0.1); //smooth filter strength
		plot->setCropToRect(true);
		plot->update(0);

		plotsMap[particle_name]=plot;
	}
}