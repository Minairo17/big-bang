#include "PlotApp.h"

PlotApp::PlotApp(shared_ptr<ofApp> _mainApp){
	mainApp= _mainApp;
	ofLog()<<"PlotApp Constructor";
}

void PlotApp::setup(){

	// ofxGraph uses ofxGui as a internal setting UI
    ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);

	// multiplotting ofxGraph
    graph.setup(20,20, 800, 150);
	graph.setAutoScale(true,1.0);
	graph.setName("Particles");
    graph.setDx(1.0);
    graph.setColor(ofColor::azure);
    graph.setLabel({"e-","e+","p-","p+","n","n_bar","gamma"});
    graph.setGraphType(OFXGRAPH_TYPE_PLOT);

 	graph2.setup(20,200, 800, 150);
	graph2.setAutoScale(true,1.0);
	graph2.setName("Light elements");
    graph2.setDx(1.0);
    graph2.setColor(ofColor::azure);
    graph2.setLabel({ "D", "3He", "4He", "7Be", "8B", "8Li", "12C", "13N", "14O", "15O", "15N" });
    graph2.setGraphType(OFXGRAPH_TYPE_PLOT);

 	graph3.setup(20,400, 800, 150);
	graph3.setAutoScale(true,1.0);
	graph3.setName("Heavy elements");
    graph3.setDx(1.0);
    graph3.setColor(ofColor::azure);
    graph3.setLabel({ "16O", "20Ne", "24Mg", "28Si", "32S", "36Ar", "40Ca", "44Ti", "48Cr", "52Fe", "56Ni"});
    graph3.setGraphType(OFXGRAPH_TYPE_PLOT);

	graph4.setup(20,600, 800, 150);
	graph4.setAutoScale(true,1.0);
	graph4.setName("Neutrinos");
    graph4.setDx(1.0);
    graph4.setColor(ofColor::azure);
    graph4.setLabel({"nu_e","nu_e_bar"});
    graph4.setGraphType(OFXGRAPH_TYPE_PLOT);

	ofLog()<<"Ready from PlotApp";
}


void PlotApp::update(){
   
    graph.add(mainApp->universeManager->statisticsManager->numParts);
	graph2.add(mainApp->universeManager->statisticsManager->numAtoms);
	graph3.add(mainApp->universeManager->statisticsManager->numNuclei);
	graph4.add(mainApp->universeManager->statisticsManager->numNeutrinos);
}

void PlotApp::draw(){
    ofBackground(50,50,50);
    graph.draw();
 	graph2.draw();
	graph3.draw();
	graph4.draw();
}