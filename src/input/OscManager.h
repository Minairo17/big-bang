#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class OscManager {

private:
	ofxOscReceiver receiver;
    int portIn;

public:
    void setup();
    void update ();

    OscManager(ofJson &settings);
};