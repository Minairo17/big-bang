#include "GuiApp.h"

void GuiApp::setup(){
	ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);

	//load settings
    ofFile file_settings("settings_2.json");
    if(file_settings.exists()){
		file_settings >> settings;  
	}
	parameters.setName(settings["gui"]["title"]);
	parameters.add(energy.set("Energy (MeV)",settings["gui"]["initialEnergy"],settings["gui"]["energyMin"],settings["gui"]["energyMax"]));
	parameters.add(sigma.set("Random Energy Sigma",settings["gui"]["sigma"],0.0,1.0));
	parameters.add(interactions.set("Interactions", false));
	parameters.add(gravity.set("Gravity", false));

	gui.setup(parameters);
	gui.add(reset.setup("Reset"));

	gui.add(scale.setup("Scale", settings["gui"]["scale"], 0.1f, 16.f));
	gui.add(brightness.setup("Brightness", settings["gui"]["brightness"], 0.f, 30.f));
	gui.add(thresh.setup("Threshold", settings["gui"]["threshold"], 0.1f, 2.f));
	ofBackground(0);
	ofSetVerticalSync(false);
	
	mappedradius = ofMap(energy, settings["gui"]["energyMin"], settings["gui"]["energyMax"], settings["gui"]["radiusMax"], settings["gui"]["radiusMin"]);

	ofLog()<<"Ready from GuiApp";
}

void GuiApp::update(){
	mappedradius = ofMap(energy, settings["gui"]["energyMin"], settings["gui"]["energyMax"], settings["gui"]["radiusMax"], settings["gui"]["radiusMin"]);
}

void GuiApp::draw(){
	gui.draw();
}