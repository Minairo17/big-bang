#include "ofApp.h"

ofApp::ofApp(shared_ptr<GuiApp> gui){
	inputManager = make_shared<InputManager>(gui);
	inputManager->setup();

	universeManager = make_shared<UniverseManager>(inputManager);
	universeManager->setup();

	ofLog()<<"ofApp Constructor";
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle(inputManager->dataManager->settings["OF"]["title"]);
  	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(inputManager->dataManager->settings["OF"]["frameRate"]);
	ofSetVerticalSync(true);

   	ofBackgroundHex(ofHexToInt(inputManager->dataManager->settings["OF"]["backgroundColor"]));
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);

	ofDisableArbTex();
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo_bloom.allocate(ofGetWidth(), ofGetHeight());
	fbo_bloom_gamma.allocate(ofGetWidth(), ofGetHeight());
	ofEnableArbTex();

	bloom.setup(ofGetWidth(), ofGetHeight(), fbo_bloom);
	bloom.setBrightness(inputManager->dataManager->settings["bloom"]["charged"]["brightness"]);
	bloom.setScale(inputManager->dataManager->settings["bloom"]["charged"]["scale"]);
	bloom.setThreshold(inputManager->dataManager->settings["bloom"]["charged"]["threshold"]);
	bloom_gamma.setup(ofGetWidth(), ofGetHeight(), fbo_bloom_gamma);

	ofLog()<<"Ready from ofApp";
}

//--------------------------------------------------------------
void ofApp::update(){

	inputManager->update();

	universeManager->update();

 	fbo_bloom.begin();
	ofClear(0);
	universeManager->particleManager->draw_charged();
	fbo_bloom.end();
	bloom.process();

	fbo_bloom_gamma.begin();
	ofClear(0);
	universeManager->particleManager->draw_gamma();
	fbo_bloom_gamma.end();

	bloom_gamma.setBrightness(inputManager->gui->brightness);
	bloom_gamma.setScale(inputManager->gui->scale);
	bloom_gamma.setThreshold(inputManager->gui->thresh);
	bloom_gamma.process();

	fbo.begin();
	ofClear(0);
	bloom.draw();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	bloom_gamma.draw();
	ofDisableBlendMode();
	universeManager->particleManager->draw_neutral();
	fbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){

	//ofEnableBlendMode( OF_BLENDMODE_ADD );
	
	fbo.draw(0,0);

	//
	//universeManager->draw();
	//ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------


